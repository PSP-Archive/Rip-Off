#include "foundation/GlobalTimer.h"

#include "engine/InputController.h"
#include "NetworkController.h"
#include "basicai/AIController.h"
#include "basicai/StdGameAI.h"

#include "engine/Game.h"
#include "engine/Bullet.h"
#include "engine/ThiefShip.h"
#include "engine/GuardianShip.h"
#include "graphics/EffectIF.h"

#include "network/PSPNetwork.h"

// Always place as last include and only in cpp files!!
#include "foundation/Debug.h"

//--------------------------------------------------------------------------------
Game::Game(void) :
	m_difficulty(NORMAL),
	m_players(2),
	m_guardianShips(NULL),
	m_cargo(NULL),
	m_round(0),
	m_phase(0),
	m_shipSpeedIncrement(0.0f),
	m_spawnPointOffset(0.0f),
	m_distanceFromSpawnPoint(0.0f),
	m_isSpawning(false),
	m_phaseSpawnTime(1.5f),
	m_backgroundMusic(NULL),
	m_highScore(0)
{
	for(int i=0; i<PHASES_PER_ROUND; i++)
	{
		m_phaseMusic[i] = NULL;
	}
}

//--------------------------------------------------------------------------------
void
Game::init(const ConfigData* confData)
{
	data.load(confData);
}

//--------------------------------------------------------------------------------
void
Game::start(void)
{

	

	if(m_players > 1)
	{
		if (PSPNetwork::get()->isHost())
		{
			RigidBody::resetID(0);
			/*unsigned int seed = (unsigned int)GlobalTimer::get()->getTime() * 1000;
			srand(seed);
			
			WelcomeMessage message;
			message.msgID = WELCOME;
			message.seed = seed;

			printf("size of WelcomeMessage > %d\n", sizeof(WelcomeMessage));
			char* buffer = new char[sizeof(WelcomeMessage)];
			
			memcpy(buffer, &message, sizeof(WelcomeMessage));

			printf("seed is > %d, buffer is > %s\n", seed, buffer);
			PSPNetwork::get()->sendMessage(buffer, sizeof(WelcomeMessage));
			delete [] buffer;*/
		}
		else
		{
			RigidBody::resetID(10000);
			/*char* buffer = new char[sizeof(WelcomeMessage)];
			
			PSPNetwork::get()->recieveMessage(buffer, sizeof(WelcomeMessage));

			WelcomeMessage *message = (WelcomeMessage*)buffer;
			
			srand(message->seed);

			printf("seed is > %d\n", message->seed);
			delete[] buffer;*/
		}
	}
	else
	{
		RigidBody::resetID(0);
	}

	m_physics.addCollisionPair(PHYS_BULLETS, PHYS_THIEF_SHIPS);
	m_physics.addCollisionPair(PHYS_GUARDIAN_SHIPS, PHYS_THIEF_SHIPS);

	//srand((unsigned int)GlobalTimer::get()->getTime());
	
	// Create graphics scene from loader
	m_pScene = data.createScene();

	//CREATE AN ARRAY OF POINTERS TO SHIPS
	/*
	for(int i=0; i<m_players; i++)
	{
		GuardianShip *ship = data.createGuardianShip(i);

		// Add to the world
		m_guardianShips.push_back(ship);
		m_entities.push_back(ship);
		m_physics.addBody(ship);
		ship->setPhysicsGroup(PHYS_GUARDIAN_SHIPS);

		// Apply the controller
		ControllerIF *controller = new InputController(i);
		controller->setShip(ship);
		ship->setController(controller);
		m_controllers.push_back(controller);

		ship->spawn();
	}*/

	//----------------------------------------------------------------

	// ALTER THE NUMBER OF CANISTERS DEPENDING ON DIFFICULTY
	// CREATE AN ARRAY OF POINTERS TO CARGO
	int cargoCount = (m_difficulty == EASY) ? 12 : 8;
	for(int i=0; i<cargoCount; i++)
	{
		Cargo *cargo = data.createCargo();
		
		if(m_players > 1 && !PSPNetwork::get()->isHost())
		{
			cargo->updateID(-10000);
		}

		//ADD TO THE ENTITIES ARRAY FOR RENDERING
		m_entities.push_back(cargo);
		m_cargo.push_back(cargo);

		m_physics.addBody(cargo);
		cargo->setPhysicsGroup(PHYS_CARGOS);

		// Arrange them in some random way
		cargo->setRotation(float((92*i) % 360));
		cargo->setPosition(Vector2f( float(i%3) * 0.1f - 0.1f, float(i/3) * 0.1f - 0.1f ));
	}


	//----------------------------------------------------------------

	GuardianShip *ship0 = data.createGuardianShip(0);
	m_guardianShips.push_back(ship0);
	m_entities.push_back(ship0);
	m_physics.addBody(ship0);
	ship0->setPhysicsGroup(PHYS_GUARDIAN_SHIPS);

	//if 2 players
	if(m_players == 2)
	{
		ControllerIF *controller0;
		//ControllerIF *controller1;

		GuardianShip *ship1 = data.createGuardianShip(1);
		m_guardianShips.push_back(ship1);
		m_entities.push_back(ship1);
		m_physics.addBody(ship1);
		ship1->setPhysicsGroup(PHYS_GUARDIAN_SHIPS);

		controller0 = new InputController(0);
		//controller1 = new NetworkController(1);

		if(PSPNetwork::get()->isHost())
		{
			controller0->setShip(ship0);
			//controller1->setShip(ship1);
			
			ship0->setController(controller0);
			//ship1->setController(controller1);
		}
		else
		{
			controller0->setShip(ship1);
			//controller1->setShip(ship0);

			//ship0->setController(controller1);
			ship1->setController(controller0);
		}

		m_controllers.push_back(controller0);
		//m_controllers.push_back(controller1);

		

	
		ship0->spawn();
		ship1->spawn();
	}
	else
	{
		ControllerIF *controller0 = new InputController(0);
		controller0->setShip(ship0);
		m_controllers.push_back(controller0);

		ship0->setController(controller0);
		ship0->spawn();
	}
	
	/*
	// ALTER THE NUMBER OF CANISTERS DEPENDING ON DIFFICULTY
	// CREATE AN ARRAY OF POINTERS TO CARGO
	int cargoCount = (m_difficulty == EASY) ? 12 : 8;
	for(int i=0; i<cargoCount; i++)
	{
		Cargo *cargo = data.createCargo();
		
		if(m_players > 1 && !PSPNetwork::get()->isHost())
		{
			cargo->updateID(-10000);
		}

		//ADD TO THE ENTITIES ARRAY FOR RENDERING
		m_entities.push_back(cargo);
		m_cargo.push_back(cargo);

		m_physics.addBody(cargo);
		cargo->setPhysicsGroup(PHYS_CARGOS);

		// Arrange them in some random way
		cargo->setRotation(float((92*i) % 360));
		cargo->setPosition(Vector2f( float(i%3) * 0.1f - 0.1f, float(i/3) * 0.1f - 0.1f ));
	}
	*/
	
	m_pScene->initializeForRendering();
	m_pScene->setAspectRatio(m_aspectRatio);


	// Start the game
	m_timer.reset();
	m_score = 0;
	m_isOver = false;
	m_round = 0;
	m_phase = 0;
	m_isFirstPhase = true;
	
	// Spawn first phase
	m_isSpawning = true;
	m_phaseSpawnTimer.reset();

	// Start music
	m_backgroundMusic->play();
}

//--------------------------------------------------------------------------------
void
Game::update()
{
	m_timer.update();

	// Check if game is over
	if(m_cargo.size() == 0)
	{
		m_phaseMusic[m_phase]->stop();

		m_isOver = true;
	}

	// If the game is not over process phases
	if(!m_isOver)
	{
		// Check weather to start new phase spawning
		if(!m_isSpawning && m_thiefShips.size() == 0)
		{
			m_phaseMusic[m_phase]->stop();

			m_isSpawning = true;
			m_phaseSpawnTimer.reset();
		}
		// Check if new phase should be spawned
		else if(m_isSpawning)
		{
			m_phaseSpawnTimer.update();
			
			if(m_phaseSpawnTimer.getTime() > m_phaseSpawnTime)
			{
				// Dont increase the phase if first one
				if(!m_isFirstPhase)
				{
					m_phase++;
				}
				else
				{
					m_isFirstPhase = false;
				}

				if(m_phase >= PHASES_PER_ROUND)
				{
					m_phase = 0;
					m_round++;
				}

				if(m_players < 2 || PSPNetwork::get()->isHost())
				{
					spawnPhase();
				}

				// Start the music
				#ifdef _3D
				#ifdef _PC			
					// detect where the enemy spawn
					m_phaseMusic[m_phase]->setListenerPosition((*m_thiefShips.front()).getPosition());
				#endif
				#endif
				m_phaseMusic[m_phase]->play();

				m_isSpawning = false;
			}
		}
	}

	//Update the controllers
	
	/*if(PSPNetwork::get()->isHost())
	{*/
		for(ControllerIt it = m_controllers.begin(); it != m_controllers.end(); it++)
		{	
			(*it)->Update(m_timer.getFrameTime());
		}
	//}
	
	//MOVE ALL ITEMS IN THE GAMEWORLD AND CHECK FOR COLLISIONS
	m_physics.update(m_timer.getFrameTime());

	//Update the game entities
	for(EntityIt it = m_entities.begin(); it != m_entities.end(); it++)
	{	
		(*it)->onUpdate(m_timer.getFrameTime());
	}

	// Update all effects
	for(EffectIt it = m_effects.begin(); it != m_effects.end(); /* empty */)
	{	
		if((*it)) (*it)->Update();

		// Check if the effect has finished
		if((*it) && (*it)->isFinished())
		{
			delete (*it);
			it = m_effects.erase(it);
		}
		else
		{
			++it;
		}
	}


	// Destroy all entities that need to be destroyed
	for(std::set<GameEntity*>::iterator it = m_toDestroy.begin(); it != m_toDestroy.end(); ++it)
	{	
		// Remove it from the world
		m_physics.removeBody(*it);
		m_entities.remove(*it);

		// Check if it needs to be removed from a list and controller
		if((*it)->getEntityType() == CARGO)
		{
			m_cargo.remove(static_cast<Cargo*>(*it));
		}
		else if((*it)->getEntityType() == THIEF)
		{
			ThiefShip* ship = static_cast<ThiefShip*>(*it);
			
			m_thiefShips.remove(ship);
			if(ship->getController())
			{
				m_controllers.remove(ship->getController());
				ship->getController()->Cleanup();
				delete ship->getController();
			}
		}
		else if((*it)->getEntityType() == GUARDIAN)
		{
			GuardianShip* ship = static_cast<GuardianShip*>(*it);

			m_guardianShips.remove(ship);
			if(ship->getController())
			{
				m_controllers.remove(ship->getController());
				ship->getController()->Cleanup();
				delete ship->getController();
			}
		}

		// Finally delete the entity
		delete (*it);
		//*it=NULL;
	}

	m_toDestroy.clear();
}


void 
Game::postUpdate(){
	m_timer.update();
	// Update all effects

	//Update the game entities
	for(EntityIt it = m_entities.begin(); it != m_entities.end(); it++)
	{	
		//if ((*it)->getEntityType() == BULLET)
			(*it)->sleep();
	//		delete (*it);
	}

	for(EffectIt it = m_effects.begin(); it != m_effects.end(); /* empty */)
	{	
		if((*it)) (*it)->Update();

		// Check if the effect has finished
		if((*it) && (*it)->isFinished())
		{
			delete (*it);
			it = m_effects.erase(it);
		}
		else
		{
			++it;
		}
	}

	// Destroy all entities that need to be destroyed
	for(std::set<GameEntity*>::iterator it = m_toDestroy.begin(); it != m_toDestroy.end(); ++it)
	{	
		// Remove it from the world
		m_physics.removeBody(*it);
		m_entities.remove(*it);

		// Check if it needs to be removed from a list and controller
		if((*it)->getEntityType() == CARGO)
		{
			m_cargo.remove(static_cast<Cargo*>(*it));
		}
		else if((*it)->getEntityType() == THIEF)
		{
			ThiefShip* ship = static_cast<ThiefShip*>(*it);
			
			m_thiefShips.remove(ship);
			if(ship->getController())
			{
				m_controllers.remove(ship->getController());
				ship->getController()->Cleanup();
				delete ship->getController();
			}
		}
		else if((*it)->getEntityType() == GUARDIAN)
		{
			GuardianShip* ship = static_cast<GuardianShip*>(*it);

			m_guardianShips.remove(ship);
			if(ship->getController())
			{
				m_controllers.remove(ship->getController());
				ship->getController()->Cleanup();
				delete ship->getController();
			}
		}

		// Finally delete the entity
		delete (*it);
		//*it=NULL;
	}

	m_toDestroy.clear();
}

//--------------------------------------------------------------------------------
void 
Game::render()
{
	// Start the rendering
	m_pScene->startRender();
	

	// Render all effects
	for(EffectIt it = m_effects.begin(); it != m_effects.end(); ++it)
	{	
		(*it)->Render();
	}

	// Render all entities
	for(EntityIt it = m_entities.begin(); it != m_entities.end(); it++)
	{	
		if((*it)->queryAlive())
		{
			(*it)->Render();
		}
	}

	// Render all effects
	//for(EffectIt it = m_effects.begin(); it != m_effects.end(); ++it)
	//{	
	//	(*it)->Render();
	//}
	
	// End rendering
	m_pScene->endRender();
	
}

//--------------------------------------------------------------------------------
void 
Game::end()
{
	// Start music
	m_backgroundMusic->stop();

	//DELETE ALL ENTITIES AND CONTROLLERS
	for(ControllerIt it = m_controllers.begin(); it != m_controllers.end(); it++)
	{
		delete (*it);
	}
	m_controllers.clear();
	for(EntityIt it = m_entities.begin(); it != m_entities.end(); it++)
	{
		delete (*it);
	}
	m_entities.clear();

	// Delete all effects
	for(EffectIt it = m_effects.begin(); it != m_effects.end(); ++it)
	{	
		delete (*it);
	}
	m_effects.clear();
	
	m_cargo.clear();
	m_guardianShips.clear();
	m_thiefShips.clear();

	m_physics.cleanup();
	m_pScene->cleanUpForRendering();

	delete m_pScene;
}

//--------------------------------------------------------------------------------
Ship* Game::spawnEnemy(unsigned int type)
{
	// Create ship
	Ship *thief = data.createThiefShip(type);

	// Add to the world
	m_entities.push_back(thief);
	m_thiefShips.push_back(thief);
	m_physics.addBody(thief);
	thief->setPhysicsGroup(PHYS_THIEF_SHIPS);

	// Apply controller
	AIController *controller = new AIController();

	// Apply implementation
	controller->SetImpl(new StdGameAI);

	// set ship
	controller->setShip(thief);
	thief->setController(controller);

	m_controllers.push_back(controller);

	return thief;
}

//--------------------------------------------------------------------------------
Bullet*
Game::spawnBullet()
{
	Bullet* bullet = data.createBullet();

	// Add it to the world
	m_entities.push_back(bullet);
	m_physics.addBody(bullet);
	bullet->setPhysicsGroup(PHYS_BULLETS);

	// Bullets are asleep when created
	bullet->sleep();

	return bullet;
}

//--------------------------------------------------------------------------------
void
Game::setAspectRatio(float ar)
{
	m_aspectRatio = ar;

	m_physics.setBoundary(-m_aspectRatio, -1, m_aspectRatio, 1);
}

//--------------------------------------------------------------------------------
void
Game::spawnPhase()
{
	// Find the number of ships to spawn
	unsigned int nShips = m_round + 3;
	if(m_players == 1)
	{
		nShips--;
	}

	// Choose a spawning point
	Vector2f spawnPoint;
	switch(rand() % 6)
	{
		case 0:
			spawnPoint.x = -GameEngine::get()->getAspectRatio() - m_spawnPointOffset;
			spawnPoint.y = 1.0f + m_spawnPointOffset;
		break;

		case 1:
			spawnPoint.x = 0.0f;
			spawnPoint.y = 1.0f + m_spawnPointOffset;
		break;

		case 2:
			spawnPoint.x = GameEngine::get()->getAspectRatio() + m_spawnPointOffset;
			spawnPoint.y = 1.0f + m_spawnPointOffset;
		break;

		case 3:
			spawnPoint.x = -GameEngine::get()->getAspectRatio() - m_spawnPointOffset;
			spawnPoint.y = -1.0f - m_spawnPointOffset;
		break;

		case 4:
			spawnPoint.x = 0.0f - m_spawnPointOffset;
			spawnPoint.y = -1.0f - m_spawnPointOffset;
		break;

		case 5: default:
			spawnPoint.x = GameEngine::get()->getAspectRatio() + m_spawnPointOffset;
			spawnPoint.y = -1.0f - m_spawnPointOffset;
		break;
	}

	// Distribute the ships around the spawn point
	float angle = 2*float(PI) / nShips;
	
	// Spawn all the ships in one of the six spawning positions
	for(unsigned int i=0; i<nShips; i++)
	{
		// Create the ship in the world
		Ship* ship = GameEngine::get()->spawnEnemy(m_phase);

		// Place it at its spawning position
		ship->setPosition(spawnPoint + m_distanceFromSpawnPoint * Vector2f(cos(angle * i), sin(angle * i)));

		// Sets its max speed
		ship->setMaxSpeed(ship->getMaxSpeed() * (1 + m_shipSpeedIncrement * m_round));

		//--------------------------------------------------
		// DEBUG STUFF -- COMMENT OUT ONCE AI IS IMPLEMENTED
		//float angle = float(atan(ship->getPosition().y / ship->getPosition().x)) / float(DegRad);
		//if(ship->getPosition().x < 0.0f)
		//{
		//	angle += 180.0f;
		//}
		//angle += 180.0f;

		//ship->pilot(1.0, angle);
		//ship->setRotation(angle);
	}
}

//--------------------------------------------------------------------------------
void
Game::spawnThiefExplosion1(const Vector2f& pos, float rot, const Vector2f& velocity)
{
	EffectIF* effect = data.createThiefExplosion1();

	if(effect)
	{
		effect->SetPosition(pos);
		effect->SetRotation(rot);
		effect->SetVelocity(velocity);
		effect->Start();

		m_effects.push_back(effect);
	}
}

//--------------------------------------------------------------------------------
void
Game::spawnThiefExplosion2(const Vector2f& pos, float rot, const Vector2f& velocity)
{
	EffectIF* effect = data.createThiefExplosion2();

	if(effect)
	{
		effect->SetPosition(pos);
		effect->SetRotation(rot);
		effect->SetVelocity(velocity);

		effect->Start();

		m_effects.push_back(effect);
	}
}

//--------------------------------------------------------------------------------
void
Game::spawnGuardianExplosion1(const Vector2f& pos, float rot, const Vector2f& velocity)
{
	EffectIF* effect = data.createGuardianExplosion1();

	if(effect)
	{
		effect->SetPosition(pos);
		effect->SetRotation(rot);
		effect->SetVelocity(velocity);

		effect->Start();

		m_effects.push_back(effect);
	}
}

//--------------------------------------------------------------------------------
void
Game::spawnGuardianExplosion2(const Vector2f& pos, float rot, const Vector2f& velocity)
{
	EffectIF* effect = data.createGuardianExplosion2();

	if(effect)
	{
		effect->SetPosition(pos);
		effect->SetRotation(rot);
		effect->SetVelocity(velocity);

		effect->Start();

		m_effects.push_back(effect);
	}
}

//--------------------------------------------------------------------------------
void
Game::spawnLaser(const Vector2f& pos, float rot)
{
	EffectIF* effect = data.createLaser();

	if(effect)
	{
		effect->SetPosition(pos);
		effect->SetRotation(rot);

		effect->Start();

		m_effects.push_back(effect);
	}
}

//--------------------------------------------------------------------------------
void
Game::spawnGameoverExplosion(const Vector2f& pos, float rot)
{
	EffectIF* effect = data.createGameoverExplosion();

	if(effect)
	{
		effect->SetPosition(pos);
		effect->SetRotation(rot);

		effect->Start();

		m_effects.push_back(effect);
	}
}

//--------------------------------------------------------------------------------
void
Game::spawnGameoverExplosion1(const Vector2f& pos, float rot)
{
	EffectIF* effect = data.createGameoverExplosion1();

	if(effect)
	{
		effect->SetPosition(pos);
		effect->SetRotation(rot);

		effect->Start();

		m_effects.push_back(effect);
	}
}

//--------------------------------------------------------------------------------
void 
Game::spawnFireJet(const Vector2f& pos, float rot, const Vector2f& velocity, const RigidBody* pBody){
	EffectIF* effect = data.createFireJet();

	if(effect)
	{
		effect->SetPosition(pos);
		effect->SetRotation(rot);
		//effect->SetVelocity(velocity);
		effect->setTrace(pBody);
		pBody->setEffect(effect);
		
		effect->Start();

		m_effects.push_back(effect);
	}
}

//--------------------------------------------------------------------------------
#ifdef _SPSP
int 
Game::packMessage(void* buffer)
{	
	//buffer = new char[sizeof(EntityMessage)];

	// create a copy in char* format
	EntityMessage *ptr = (EntityMessage*)buffer;


	int messageSize = 0;

	

	if (PSPNetwork::get()->isHost())
	{
		// first get the game information
		//GameMessage gameInfo;
		//gameInfo.totalEntities = m_entities.size();

		messageSize = sizeof(EntityMessage);
		//memcpy(ptr, &gameInfo, messageSize);
		//ptr += messageSize;


		/*for(EntityIt it = m_entities.begin(); it != m_entities.end(); it++)
		{*/
			EntityMessage message;
			ShipList::iterator it = m_guardianShips.begin();
			//it++;
			(*it)->packMessage(message);

			messageSize = sizeof(message);
			memcpy(ptr, &message, messageSize);
			ptr++;;

			//for(ShipList::iterator it1 = m_thiefShips.begin(); it1 != m_thiefShips.end(); it1++)
			//{
			//	(*it1)->packMessage(message);
			//	memcpy(ptr, &message, messageSize);
			//	ptr++;
			//}

			for(EntityIt it1 = m_entities.begin(); it1 != m_entities.end(); it1++)
			{
				if((*it1)->getEntityType() == 3 ||(*it1)->getEntityType() == 4 || ((*it1)->getEntityType() == 1 && (*it1)->queryAlive() && (*it1)->getID() < 9999))
				{
					(*it1)->packMessage(message);
					memcpy(ptr, &message, messageSize);
					ptr++;
				}
			}





		//}
	}
	else
	{
			EntityMessage message;
			ShipList::iterator it = m_guardianShips.begin();
			it++;
			(*it)->packMessage(message);

			messageSize = sizeof(message);
			memcpy(ptr, &message, messageSize);
			ptr++;

			for(EntityIt it1 = m_entities.begin(); it1 != m_entities.end(); it1++)
			{
				if((*it1)->getEntityType() == 1 && (*it1)->getID() > 9999 && (*it1)->queryAlive())
				{
					(*it1)->packMessage(message);
					memcpy(ptr, &message, messageSize);
					ptr++;
				}
			}
	}
	/* set my ether addr */
	//sceNetGetLocalEtherAddr(&scope[0].addr);

	//memcpy(ptr, &scope[0], SCOPE_TX_SIZE);
	//ptr += SCOPE_TX_SIZE;

	//scope[0].beam_flag = 0;

	// calculate the length of message
	return (unsigned char *)ptr - (unsigned char *)buffer;
}

//--------------------------------------------------------------------------------
void
Game::updateNetworkData(void *buffer, int bufferSize)
{

bool cargoUpdated = false;

	int messages = bufferSize / sizeof(EntityMessage);

	EntityMessage *ptr = (EntityMessage*)buffer;
	if(!ptr->entityType)
		return;

	for(int i=0; i<messages; i++)
	{


		EntityMessage *message = (EntityMessage*)ptr;


		if(message->entityType == 0)
			continue;

		//its a bullet
		if(message->entityType == 1)
		{
			int found = false;
			for(EntityIt it = m_entities.begin(); it != m_entities.end(); it++)
			{	
				// check for the existence of the entity
				
				

				if ((*it)->getID() == message->id)
				{		
					found = true;
					(*it)->unpackMessage(*message);

	/*				if((*it)->queryAlive() && !message->isAlive)
					{
						(*it)->sleep();
					}*/
					(*it)->flagUpdate();
				}
				
			}
			if(!found)
			{
				//printf("Spawning enemy.\n");
				Bullet *bullet = spawnBullet();
				bullet->setID(message->id);
				bullet->unpackMessage(*message);
				bullet->flagUpdate();
			}
		}
		else if(message->entityType == 3)
		{
			int found = false;
			for(ShipList::iterator it = m_thiefShips.begin(); it != m_thiefShips.end(); it++)
			{	
				// check for the existence of the entity
				
				if ((*it)->getID() == message->id)
				{		
					found = true;
					if((*it)->queryAlive())
					{
						(*it)->unpackMessage(*message);
						(*it)->flagUpdate();
					}
				}
			}
			if(!found)
			{
				//printf("Spawning enemy.\n");
				Ship *enemy = spawnEnemy(m_phase);
				enemy->setID(message->id);
				enemy->unpackMessage(*message);
				enemy->flagUpdate();
			}
		}
		//if its a guardian
		else if(message->entityType == 2)
		{
			ShipList::iterator it = m_guardianShips.begin();
			if(PSPNetwork::get()->isHost())
			{
				it++;
			}
			
			(*it)->unpackMessage(*message);

			if((*it)->queryAlive() && !message->isAlive)
			{
				(*it)->kill();
			}

		}
		//if its a cargo
		else if(message->entityType == 4)
		{
			
			for(CargoList::iterator it = m_cargo.begin(); it != m_cargo.end(); it++)
			{	
				// check for the existence of the entity
				if ((*it)->getID() == message->id)
				{		
					cargoUpdated = true;
					(*it)->unpackMessage(*message);
					(*it)->flagUpdate();
				}
			}
		}

		ptr++;

	}


	
	// post unpacking process of join player

	if (!PSPNetwork::get()->isHost())
	{
		if(!cargoUpdated)
		{
			//ptr = (EntityMessage*)buffer;
			//for(int i=0; i<messages;i++)
			//{
			//	printf("entity: %d\n", ptr->entityType);
			//	ptr++;
			//}

			//printf("CARGO ERROR!\n");
		}

		for(EntityIt it1 = m_entities.begin(); it1 != m_entities.end(); it1++)
		{
			if((*it1)->getEntityType() == 3)
			{
				// assumption, unupdated entities are destroyed
				if ((*it1)->notUpdated() && (*it1)->queryAlive())
				{
					ThiefShip* ship = static_cast<ThiefShip*>(*it1);
					ship->kill();
				}
			}
			else if ((*it1)->getEntityType() == 1)
			{
				/*if ((*it1)->notUpdated())
				{
					(*it1)->sleep();
				}*/
			}
			//cargo
			else if ((*it1)->getEntityType() == 4)
			{
				if ((*it1)->notUpdated())
				{
					GameEngine::get()->registerDestruction((*it1));
				}
			}
		}

		for(EntityIt it = m_entities.begin(); it != m_entities.end(); it++)
		{
			// unflag every ships
			(*it)->clearUpdateFlag();
		}
	}
}
#endif