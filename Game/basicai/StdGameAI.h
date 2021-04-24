#pragma once
#include "engine/AI_ImplementationIF.h"
#include "engine/Game.h" 
#include "engine/Ship.h"
#include "engine/Cargo.h"
#include "foundation/Vector2f.h"
#include "foundation/Angle.h"
#include <vector>

const int claimTagID = 1; // tag for claiming cargo
const int attackTagID = 2; // tag for attacking player

class StdGameAI : public AI_ImplementationIF {
public:
	StdGameAI();
	~StdGameAI();
	void Update(Ship* pShip);
	void setAgentType(int AIType) { m_AIType = AIType; }

	// call once after connecting controller and ship
	void Init();

	// call whenever ship gets switched to dead
	// this removes any active tags this ship may have set somewhere
	void Cleanup();

private:
	void stateNoTask();
	void stateWaitForPlayer();
	void stateFetchCargo();
	void stateHookCargo();
	void stateDragCargo();
	void stateAttackPS();

	void markAsTagged(GameEntity* ent, int tagID);
	void unmarkTagged();

	Cargo* selectNearest(Game::CargoList cList);
	Ship* selectNearest(Game::ShipList sList);
	float distSqr(const Vector2f& v1, const Vector2f& v2);

	// seek to position
	void seekPos(const Vector2f& tPos);

	// returns a direction vector allowing thieves to keep separate from fellow ships
	Vector2f Separate();

	// helper fun, calculate orientation vector from rotation angle of ship
	//Vector2f getOriVec(GameEntity* pShip);

	// getting a linker error when trying to use the standard normalise fun,
	// so using my own...
	Vector2f Normalise(const Vector2f& V);

	// variables
	void (StdGameAI::*m_stateFuncPtr)();

	Ship*				m_myShip;
	GameEntity*			m_taggedEnt;

	int					m_tagID,
						m_AIType;

	Angle				m_lineUp;

	Vector2f			m_offScreen;
						

	typedef Game::CargoList::iterator CargoIter;
	typedef Game::ShipList::iterator ShipIter;
};

inline Vector2f StdGameAI::Normalise(const Vector2f &V)
{
	float r = V.Length();
	if (fabs(r) > 0.0000001f)	// guard against divide by zero
		return V*(1.0f/r);		// normalise and return
	else
		return Vector2f(0.0f);
}