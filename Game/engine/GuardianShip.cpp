#include "engine/Game.h"
#include "engine/GuardianShip.h"

// Always place as last include and only in cpp files!!
#include "foundation/Debug.h"

//--------------------------------------------------------------------------------
GuardianShip::GuardianShip() :
	m_respawnTime(0.0f),
	m_respawnPoint(0.0f, 0.0f),
	m_respawnRotation(0.0f)
{
	setEntityType(Game::GUARDIAN);

	// Upon creation create the bullets pool
	for(unsigned int i=0; i<NUM_BULLETS; ++i)
	{
		m_bullets[i] = GameEngine::get()->spawnBullet();
	}

	// Create sleeping and wait for spawn
	sleep();
}

//--------------------------------------------------------------------------------
void GuardianShip::shoot()
{
	if(!queryAlive())
		return;

	// Search for a free bullet
	for(unsigned int i=0; i<NUM_BULLETS; ++i)
	{
		if(!m_bullets[i]->queryAlive())
		{
			// Free bullet found, shoot it
			m_bullets[i]->setPosition(getPosition());
			m_bullets[i]->setRotation(getRotation());
			
			// Get a vector pointing in the direction where the ship is facing
			Vector2f vel(m_bullets[i]->getMaxSpeed() * float(cos(getRotation() * DegRad)),
				m_bullets[i]->getMaxSpeed() * float(sin(getRotation() * DegRad)));
			
			// Bullets go as fast as they can =)
			m_bullets[i]->setVelocity(vel);
			
			// Shoot it!! BANG
			m_bullets[i]->wake();

			// Play the sound
			Ship::shoot();
			
			break;
		}
	}
}

//--------------------------------------------------------------------------------
void GuardianShip::onCollide(const RigidBody *body)
{
	// Can only collide with thief ships
	if(body->getPhysicsGroup() == Game::PHYS_THIEF_SHIPS)
	{
		kill();
	}
}

//--------------------------------------------------------------------------------
void GuardianShip::onOutOfBounds()
{
	// Just replace the ship and invert its velocity
	if(getPosition().x > GameEngine::get()->getAspectRatio())
	{
		setPosition(Vector2f(GameEngine::get()->getAspectRatio(), getPosition().y));
		setVelocity(Vector2f(-getVelocity().x, getVelocity().y));
	}
	if(getPosition().x < -GameEngine::get()->getAspectRatio())
	{
		setPosition(Vector2f(-GameEngine::get()->getAspectRatio(), getPosition().y));
		setVelocity(Vector2f(-getVelocity().x, getVelocity().y));
	}
	if(getPosition().y > 1.0f)
	{
		setPosition(Vector2f(getPosition().x, 1.0f));
		setVelocity(Vector2f(getVelocity().x, -getVelocity().y));
	}
	if(getPosition().y < -1.0f)
	{
		setPosition(Vector2f(getPosition().x, -1.0f));
		setVelocity(Vector2f(getVelocity().x, -getVelocity().y));
	}
}
	
//--------------------------------------------------------------------------------
void GuardianShip::spawn()
{
	setPosition(m_respawnPoint);
	setVelocity(Vector2f(0.0f, 0.0f));
	setRotation(m_respawnRotation);

	wake();
}

//--------------------------------------------------------------------------------
void GuardianShip::onUpdate(float time)
{
	Ship::onUpdate(time);

	// If dead, check whether to respawn
	if(!queryAlive())
	{
		m_respawnTimer.update();

		if(m_respawnTimer.getTime() > m_respawnTime)
		{
			spawn();
		}
	}
}

//--------------------------------------------------------------------------------
void GuardianShip::kill()
{
	if (m_pEffect)
		m_pEffect->Kill();

	m_explodeSound->stop();
	m_explodeSound->play();

	GameEngine::get()->spawnGuardianExplosion1(getPosition(), getRotation(), getVelocity());
	GameEngine::get()->spawnGuardianExplosion2(getPosition(), getRotation(), getVelocity());

	sleep();
	m_respawnTimer.reset();
}
