#include "engine/Bullet.h"
#include "engine/Game.h"

// Always place as last include and only in cpp files!!
#include "foundation/Debug.h"

//--------------------------------------------------------------------------------
Bullet::Bullet()
{
	setEntityType(Game::BULLET);
}

//--------------------------------------------------------------------------------
void Bullet::onCollide(const RigidBody *body)
{
	// Dies if collides with thief ship or bullet
	if(body->getPhysicsGroup() == Game::PHYS_THIEF_SHIPS)
	{
		sleep();
	}
}

//--------------------------------------------------------------------------------
void Bullet::onOutOfBounds()
{
	sleep();
}