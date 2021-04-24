#include "Ship.h"
#include "engine/Game.h"

// Always place as last include and only in cpp files!!
#include "foundation/Debug.h"

//--------------------------------------------------------------------------------
Ship::Ship() :
	m_shootSound(NULL),
	m_cargo(NULL),
	m_isPiloting(false),
	m_shootRequest(false),
	m_cargoCarryDistance(0.0f),
	m_speed(0.0f),
	m_accum(2.1f),
	m_controller(NULL),
	m_explodeSound(NULL),
	m_hookCragoSound(NULL)
{
	// empty	
}

//--------------------------------------------------------------------------------
void Ship::throttle(float speed)
{
	if(queryAlive())
	{
		if(speed > 1.0) speed = 1.0;
		else if(speed < 0.0) speed = 0.0;
		
		// Get a vector pointing in the direction where the ship is facing
		m_speed = speed;
		Vector2f force(m_throttle * speed * getOrientation());
		
		RigidBody::applyForce(force);
		
	}
}

//--------------------------------------------------------------------------------
void Ship::steer(float rotation)
{
	if(queryAlive())
	{
		if(rotation > 1.0) rotation = 1.0;
		else if(rotation < -1.0) rotation = -1.0;

		setRotation(getRotation() + m_steering * rotation);
	}
}

//--------------------------------------------------------------------------------

void Ship::shoot(void)
{
	if(queryAlive())
	{
#ifdef _3D
#ifdef _PC
		m_shootSound->setListenerPosition(m_position);
#endif
#endif
		m_shootSound->stop();
		m_shootSound->play();
	}
}

//--------------------------------------------------------------------------------

void Ship::hookCargo(Cargo* c) 
{ 
#ifdef _3D
#ifdef _PC
	m_hookCragoSound->setListenerPosition(m_position);
#endif
#endif
	m_hookCragoSound->stop();
	m_hookCragoSound->play();
	m_cargo = c; 
}

//--------------------------------------------------------------------------------
void Ship::onUpdate(float time)
{
	// Check if piloting
	if(m_isPiloting)
	{
		throttle(m_pilotThrottle);

#ifdef _3D
		if (m_pilotThrottle>0 && m_accum>1.8f){
			GameEngine::get()->spawnFireJet(getPosition(), getRotation(), getVelocity(), this);
			m_accum=0.0f;
		}else m_accum+=time;
#endif

		Angle delta = m_pilotRotation - getRotationAngle();
		float absDelta = std::abs(delta.getDegrees());

		// Only steer if we are within 1 degree
		// the original 2 degrees was too much, set it to 0.1 - Birgit
		if(absDelta > 0.5f)
		{
			// Check amount ship can steer in this frame
			float steering = time;
			if(absDelta < m_steering * time)
			{
				steering = absDelta / m_steering;
			}
			
			// Steer in the shortest direction
			if(delta.getDegrees() > 180.0f)
			{
				steer(-steering);
			}
			else
			{
				steer(steering);
			}
		}
	}

	// Check if shoot was requested
	if(m_shootRequest)
	{
		shoot();
		m_shootRequest = false;
	}

	// Update the cargo
	if(m_cargo)
	{
		m_cargo->setRotation(getRotation());
		m_cargo->setPosition(getPosition() - m_cargoCarryDistance * getOrientation());
	}
}

//--------------------------------------------------------------------------------
void Ship::Render()
{
	GameEntity::Render();

	if(queryAlive() && m_cargo && m_cargoHookGfx)
	{
		m_cargoHookGfx->render(getPosition(), getRotation());
	}
}

//--------------------------------------------------------------------------------
void Ship::pilot(float velo, float rotation)
{
	m_isPiloting = true;

	m_pilotThrottle = velo;
	m_pilotRotation.setDegrees(rotation);
}

//--------------------------------------------------------------------------------
void Ship::kill()
{
	// empty
}
