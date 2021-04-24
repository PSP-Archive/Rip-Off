/* VERSION HISTORY

13/04/2010 - Wendy - setListenerPosition when shoot and explode
*/

#pragma once

#include "engine/Ship.h"

//--------------------------------------------------------------------------------
class ThiefShip : public Ship
{
public:
	// Ctor
	ThiefShip();
	
	// Dtor
	virtual ~ThiefShip() {}

	// Shoots a bullet in the direction in which it is facing
	void shoot();

	// Called when the ship collides
	void onCollide(const RigidBody *body);

	// Callback called when the body leaves the world bounds
	void onOutOfBounds();
	
	// Sets the length of the laser
	void setLaserLength(float l) { m_laserLength = l; }

	// Kills the ship
	void kill();

private:
	// Length of the laser beam
	float m_laserLength;
};

