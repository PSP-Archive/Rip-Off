#include "engine/ThiefShip.h"
#include "engine/Game.h"

#include "network/PSPNetwork.h"

// Always place as last include and only in cpp files!!
#include "foundation/Debug.h"

//--------------------------------------------------------------------------------
ThiefShip::ThiefShip() :
	m_laserLength(0.1f)
{
	setEntityType(Game::THIEF);
}

//--------------------------------------------------------------------------------
void ThiefShip::shoot(void)
{
	if(!queryAlive())
		return;

	Ship::shoot();

	// Play the effect
	GameEngine::get()->spawnLaser(getPosition(), getRotation());

	// Find the laser points
	Vector2f p1 = getPosition();
	Vector2f p2 = getOrientation();
	p2 *= m_laserLength;
	p2 += p1;

	// Get the list of ships
	Game::ShipList::iterator it;
	for(it = GameEngine::get()->getPlayerList().begin();
		it != GameEngine::get()->getPlayerList().end();
		++it)
	{
		if((*it)->queryAlive())
		{
			Vector2f p3 = (*it)->getPosition();

			float a = (p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y);
			float b = 2*((p2.x - p1.x)*(p1.x - p3.x) + (p2.y - p1.y)*(p1.y - p3.y));
			float c = p3.x*p3.x + p3.y*p3.y + p1.x*p1.x + p1.y*p1.y
				- 2*(p3.x*p1.x + p3.y*p1.y) - (*it)->getRadius()*(*it)->getRadius();
			
			// Find the descriminant
			float descr = b*b - 4*a*c;
			if(descr > 0)
			{
				float r1 = (-b + sqrt(descr)) / (2*a);
				float r2 = (-b - sqrt(descr)) / (2*a);

				if( (r1 >= 0.0f && r1 <= 1.0f) || (r2 >= 0.0f && r2 <= 1.0f) )
				{
					// Hit detected, kill the ship
					(*it)->kill();
				}
			}
		}
	}
}

//--------------------------------------------------------------------------------
void ThiefShip::onCollide(const RigidBody *body)
{
	// Dies if collides with guardian ship or bullet
	if(body->getPhysicsGroup() == Game::PHYS_GUARDIAN_SHIPS || 
		body->getPhysicsGroup() == Game::PHYS_BULLETS)
	{
		if (GameEngine::get()->getPlayers() == 1 || PSPNetwork::get()->isHost())
		{
			if (m_alive)
			{
				kill();
			}
		}
	}
}

//--------------------------------------------------------------------------------
void ThiefShip::onOutOfBounds()
{
	// Only destroy an out of bounds ship if it has a cargo
	if(m_cargo)
	{
		GameEngine::get()->registerDestruction(m_cargo);
		unhookCargo();

		getController()->Cleanup();
		destroy();
		m_alive=false;

		if (m_pEffect){
			m_pEffect->Kill();
			m_pEffect=NULL;
		}
	}

	
}

//--------------------------------------------------------------------------------
void ThiefShip::kill()
{
	if(!queryAlive()){
		if (m_pEffect){
			m_pEffect->Kill();
			m_pEffect=NULL;
		}
		return;
	}

#ifdef _3D
	#ifdef _PC
	m_explodeSound->setListenerPosition(m_position);
	#endif
#endif

	if (m_pEffect){
		m_pEffect->Kill();
		m_pEffect=NULL;
	}

	m_explodeSound->stop();
	m_explodeSound->play();

	GameEngine::get()->spawnThiefExplosion1(getPosition(), getRotation(), getVelocity());
	GameEngine::get()->spawnThiefExplosion2(getPosition(), getRotation(), getVelocity());

	getController()->Cleanup();
	unhookCargo();
	destroy();

	// Increment score
	//if(queryAlive())
		GameEngine::get()->addScore(100);

	m_alive = false;
			
	//printf("Kill ID = %d, and now die? %d\n", m_id, m_alive);
}
