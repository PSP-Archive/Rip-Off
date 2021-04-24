#include "StdGameAI.h"

// Always place as last include and only in cpp files!!
#include "foundation/Debug.h"

#include <iostream>

#define DegToRad 0.0174528f
#define RadToDeg 57.297469f

const float shootingRange = 6.0f; // distance at which ships start to shoot
const float cHYST = 1.2f;  // hysteresis value for target switching

//--------------------------------------

StdGameAI::StdGameAI() :
	m_taggedEnt(NULL),
	m_stateFuncPtr(&StdGameAI::stateNoTask)
{
	//Debug::get()->output("Start in state no Task");
}

//--------------------------------------

StdGameAI::~StdGameAI() {
	unmarkTagged();
}

//--------------------------------------

void StdGameAI::Update(Ship* pShip) {
	m_myShip = pShip;

	if (pShip->queryAlive())
		(*this.*m_stateFuncPtr)();
}

//--------------------------------------

void StdGameAI::markAsTagged(GameEntity* ent, int tagID) {
	unmarkTagged();
	ent->setTag(tagID);
	m_tagID = tagID;
	m_taggedEnt = ent;
}

//--------------------------------------

void StdGameAI::unmarkTagged() {
	if (m_taggedEnt) {
		m_taggedEnt->removeTag(m_tagID);
		m_taggedEnt = NULL;
	}
}

//--------------------------------------
// calc squared distance between two vectors
float StdGameAI::distSqr(const Vector2f& v1, const Vector2f& v2) {
	Vector2f dist;
	dist.Subtract(v1, v2);
	return dist.LengthSqr();
}

//--------------------------------------

Cargo* StdGameAI::selectNearest(Game::CargoList cList) {
	CargoIter carg = cList.begin();

	if (cList.size() > 1) {
		float minLen = distSqr(m_myShip->getPosition(), (*carg)->getPosition());

		for (CargoIter cIter = carg++; cIter != cList.end(); cIter++) {
			float tmp = distSqr(m_myShip->getPosition(), (*cIter)->getPosition());
			if (tmp < minLen) {
				carg = cIter;
				minLen = tmp;
			}
		}
	}

	return (*carg);
}

//--------------------------------------

Ship* StdGameAI::selectNearest(Game::ShipList sList) {
	ShipIter pShip = sList.begin();

	if (sList.size() > 1) {
		float minLen = distSqr(m_myShip->getPosition(), (*pShip)->getPosition());

		for (ShipIter sIter = pShip++; sIter != sList.end(); sIter++) {
			float tmp = distSqr(m_myShip->getPosition(), (*sIter)->getPosition());
			if (tmp < minLen) {
				pShip = sIter;
				minLen = tmp;
			}
		}
	}

	return (*pShip);
}

//--------------------------------------

Vector2f StdGameAI::Separate() {
	Vector2f result(0.0f, 0.0f);

	Game::ShipList thieves = GameEngine::get()->getThiefList();

	for (ShipIter sIter = thieves.begin(); sIter != thieves.end(); sIter++) {
		if ((*sIter)->getID() == m_myShip->getID())
			continue; // ignore yourself

		Vector2f toNeighbour = (*sIter)->getPosition() - m_myShip->getPosition();
		float dist = toNeighbour.Length();

		// generate steering force away from neighbour proportional 
		// to the distance to him
		if (dist <= 1.1f * m_myShip->getRadius()) {
			toNeighbour.Normalise();
			toNeighbour *= -1.0f/(max(dist, 0.0001f));
			result += toNeighbour;
		}
	}

	return result;
}

//--------------------------------------
// seek to target position

void StdGameAI::seekPos(const Vector2f& tPos)
{
	Vector2f target = tPos + Separate();
	Angle angle = Angle::getVectorAngle(target - m_myShip->getPosition());
	m_myShip->pilot(1.0f, angle.getDegrees());
}

//--------------------------------------

void StdGameAI::stateNoTask() {

	// fetch list of cargo from game engine
	Game::CargoList allCargo = GameEngine::get()->getCargoList();
	Game::CargoList untaggedCargo;
	// gather all unclaimed cargo into a list
	for (CargoIter cIter = allCargo.begin(); cIter != allCargo.end(); cIter++) {
		if ((*cIter)->queryTag(claimTagID) == 0)
			untaggedCargo.push_back((*cIter));
	}

	// get player list
	Game::ShipList Players = GameEngine::get()->getPlayerList();
	Game::ShipList alivePlayers;

	for (ShipIter sIter = Players.begin(); sIter != Players.end(); sIter++) {
		if ((*sIter)->queryAlive())
			alivePlayers.push_back((*sIter));
	}

	// check for nearest item, out of untagged cargo and player
	if ((untaggedCargo.size() > 0) && (alivePlayers.size() > 0)) {
		Cargo* carg = selectNearest(untaggedCargo);
		Ship* plShip = selectNearest(alivePlayers);
	
		if (distSqr(m_myShip->getPosition(), plShip->getPosition()) <
			distSqr(m_myShip->getPosition(), carg->getPosition())) { // ship is close enough, attack

			markAsTagged(plShip, attackTagID);	// tag player ship
			m_stateFuncPtr = &StdGameAI::stateAttackPS;	// set state to attacking
			
			//Debug::get()->output("NoTask -> State attack");
		}
		else {	// cargo is closer, go fetch
			markAsTagged(carg, claimTagID);	// tag cargo as claimed
			m_stateFuncPtr = &StdGameAI::stateFetchCargo;	// set state to fetching

			//Debug::get()->output("NoTask -> State fetch");
		}
		return;
	}

	if (untaggedCargo.size() > 0) { // cargo but no player
		Cargo* carg = selectNearest(untaggedCargo);
		markAsTagged(carg, claimTagID);	// tag cargo as claimed
		m_stateFuncPtr = &StdGameAI::stateFetchCargo;	// set state to fetching
		
		//Debug::get()->output("NoTask no player -> State fetch");

		return;
	}

	if (alivePlayers.size() > 0) { // player but no untagged cargo
		Ship* plShip = selectNearest(Players);
		markAsTagged(plShip, attackTagID);	// tag player ship
		m_stateFuncPtr = &StdGameAI::stateAttackPS;	// set state to attacking
		
		//Debug::get()->output("NoTask no cargo -> State attack");
		
		return;
	}
	else {	// no cargo, no ship, move to middle while waiting
		seekPos(Vector2f(0.0f, 0.0f));
		m_stateFuncPtr = &StdGameAI::stateWaitForPlayer; // set state to waiting
		//Debug::get()->output("NoTask -> WaitForPlayer");
	}
}

//--------------------------------------

void StdGameAI::stateWaitForPlayer() {
	// this state is entered when all cargo is being dragged and 
	// players have been shot and need to respawn

	// check if player is back
	// get player list
	Game::ShipList Players = GameEngine::get()->getPlayerList();
	Game::ShipList alivePlayers;

	for (ShipIter sIter = Players.begin(); sIter != Players.end(); sIter++) {
		if ((*sIter)->queryAlive())
			alivePlayers.push_back((*sIter));
	}

	if (alivePlayers.size() > 0) {  // player respawned, go attack
		Ship* plShip = selectNearest(alivePlayers);
		markAsTagged(plShip, attackTagID);	// tag player ship
		m_stateFuncPtr = &StdGameAI::stateAttackPS;	// set state to attacking
			
		//Debug::get()->output("WaitForPlayer -> State attack");
		return;
	}

	// check if arrived at origin
	if ((m_myShip->getPosition()).Distance(Vector2f(0.0f, 0.0f)) <= 2.0f * m_myShip->getRadius())
		// stop moving and just wait
		m_myShip->pilot(0.0f, m_myShip->getRotation());
	else
		seekPos(Vector2f(0.0f, 0.0f));  // keep moving to middle
}

//--------------------------------------

void StdGameAI::stateFetchCargo() {

	if (m_taggedEnt == NULL) return;
	// check if already arrived at cargo
	if ((m_myShip->getPosition()).Distance(m_taggedEnt->getPosition()) <= m_myShip->getRadius()) {
		// set offscreen position to go back to
		m_offScreen.x = m_myShip->getPosition().x;
		m_offScreen.y = (m_myShip->getPosition().y > 0.0f ? 1.1f : -1.1f);

		// ship needs to line up its backside with cargo for hooking
		m_lineUp.setDegrees(m_myShip->getRotation() + 180.0f);

		// set state to hooking
		m_stateFuncPtr = &StdGameAI::stateHookCargo; 
		
		//Debug::get()->output("Fetch -> State hook");
		
		return;
	}
	// keep steering towards selected cargo
	seekPos(m_taggedEnt->getPosition());
}

//--------------------------------------

void StdGameAI::stateHookCargo() {
// turn backside to cargo, aka line up with vector from cargo pos towards ship
// if turned far enough,
//   change state to drag cargo

	if (fabs(m_myShip->getRotation() - m_lineUp.getDegrees()) < 1.0f) {
		m_myShip->hookCargo(static_cast<Cargo*>(m_taggedEnt));
		m_stateFuncPtr = &StdGameAI::stateDragCargo;
		
		//Debug::get()->output("Hook -> State Drag Cargo");
		
		return;
	}

	// keep turning
	m_myShip->pilot(0.0f, m_lineUp.getDegrees());
}

//--------------------------------------

void StdGameAI::stateDragCargo() {

	// check if offscreen reached 
	if (m_offScreen.Distance(m_myShip->getPosition()) <= m_myShip->getRadius()) {
		// unhook cargo and leave it offscreen,
		unmarkTagged();
		m_myShip->unhookCargo();
		m_stateFuncPtr = &StdGameAI::stateNoTask; // set state to no task
		
		//Debug::get()->output("Drag -> return to State noTask");
		
		return;
	}

	// keep steering offscreen
	seekPos(m_offScreen);
}

//--------------------------------------

void StdGameAI::stateAttackPS() {

	if (!m_taggedEnt->queryAlive()) {  // check if tagged ship still exists
		unmarkTagged();				   // if not, change to state noTask
		m_stateFuncPtr = &StdGameAI::stateNoTask;
		
		//Debug::get()->output("attack -> return to State noTask");		
		return;
	}

	// check if we can shoot at player
	Vector2f toPlayer(m_myShip->getPosition() - m_taggedEnt->getPosition());
	float distToPlayer = toPlayer.Length();

	if ((distToPlayer < shootingRange * m_myShip->getRadius()) &&
		(fabs(Normalise(toPlayer).Dot(m_myShip->getOrientation())) > 0.92f))
		m_myShip->requestShoot();

	// check if any unclaimed cargo nearer than attacked ship
	// fetch list of cargo from game engine
	Game::CargoList allCargo = GameEngine::get()->getCargoList();

	// gather all unclaimed cargo into a list
	Game::CargoList untaggedCargo;
	for (CargoIter cIter = allCargo.begin(); cIter != allCargo.end(); cIter++) {
		if ((*cIter)->queryTag(claimTagID) == 0)
			untaggedCargo.push_back((*cIter));
	}

	if (untaggedCargo.size() > 0) {
		Cargo* carg = selectNearest(untaggedCargo);

		if (cHYST * (m_myShip->getPosition()).Distance(carg->getPosition()) < distToPlayer) {
			markAsTagged(carg, claimTagID);	// tag cargo as claimed
			m_stateFuncPtr = &StdGameAI::stateFetchCargo;	// set state to fetching
		
			//Debug::get()->output("attack -> State fetch");
		
			return;
		}
	}

	// keep attacking
	seekPos(m_taggedEnt->getPosition());
}

//--------------------------------------

void StdGameAI::Init() {
}

//--------------------------------------

void StdGameAI::Cleanup() {
	unmarkTagged();
}

