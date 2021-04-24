/* VERSION HISTORY

20/02/2010 - David Wright - Class created
27/02/10 - Birgit - added function setCargo
					and function queryShipSize
09/03/10 - Birgit - added function getOrientation
13/04/2010 - Wendy - added hooksSound object and update hookCargo function to play sound
*/

#pragma once

#include "engine/GameEntity.h"
#include "engine/Cargo.h"
#include "engine/ControllerIf.h"
#include "engine/Bullet.h"
#include "sound/Sound.h"

class ControllerIF;

//--------------------------------------------------------------------------------
class Ship : public GameEntity
{
public:
	// Ctor
	Ship();
	
	// Dtor
	virtual ~Ship() {}

	// Accelerates the ship by an amount of its capacity (speed should be [0, 1]
	void throttle(float speed);

	// Steers the ship by an amount of its capacity  (rotation should be [-1, 1])
	void steer(float rotation);

	// Shoots a bullet in the direction in which it is facing
	virtual void shoot();

	// Kills the ship, should be implemented in ship type
	virtual void kill();

	// Sets the acceleration capability of the ship
	void setThrottle(float t) { m_throttle = t; }

	// Returns the acceleration capability of the ship
	float getThrottle() { return m_throttle; }

	// returns current speed of the ship
	float getSpeed() { return m_speed; }

	// Sets the steering capability of the ship
	void setSteering(float t) { m_steering = t; }

	// Returns the steering capability of the ship
	float getSteering() { return m_steering; }

	// Sets the shound to play when shooting
	void setShootingSound(Sound* sound) { m_shootSound = sound; }

	// Sets the shound to play when shooting
	void setCargoHookGfx(GFXObject* hook) { m_cargoHookGfx = hook; }

	// Called when the entity should be updated
	virtual void onUpdate(float time);

	// Hooks the cargo to the ship
	void hookCargo(Cargo* c);

	// Unhook the cargo from the ship
	void unhookCargo()  { m_cargo = NULL; }

	// Override render to add rendering of cargo hook
	void Render();

	// Sets the shound to play when shooting
	void setExplosionSound(Sound* sound) { m_explodeSound = sound; }

	// Sets the shound to play when hooks the cargo
	void setHookCargoSound(Sound* sound) { m_hookCragoSound = sound; }

	// Sets the distance at which the cargo is carried
	void setCargoCarryDistance(float c) { m_cargoCarryDistance = c; }

	// AI Specific methods

	// Pilot method to set the required speed and rotation
	// velo is absolute speed, 0.0 - 1.0
	// rotation is absolute heading, 0.0 - 360.0
	void pilot(float velo, float rotation);

	// Stops the piloting on the ship
	void stopPiloting() { m_isPiloting = false; }

	// Stops the piloting on the ship
	void requestShoot() { m_shootRequest = true; }

	// Stops the piloting on the ship
	bool isShootRequested() { return m_shootRequest; }

	// Manage the controller
	ControllerIF* getController() { return m_controller; }
	void setController(ControllerIF* c) { m_controller = c; }

protected:
	// Possible cargo (NULL if not found)
	Cargo *m_cargo;

	// Sound for shooting
	Sound* m_shootSound;

	// Gfx for cargo hook
	GFXObject* m_cargoHookGfx;

	// Sound for explosion
	Sound* m_explodeSound;

	// Sound for hooks cargo
	Sound* m_hookCragoSound;

private:
	// Characteristics of the ship
	float m_throttle;
	float m_speed;
	float m_steering;
	float m_accum;

	// Pilot variables
	bool m_isPiloting;
	float m_pilotThrottle;
	Angle m_pilotRotation;

	// Shoot request
	bool m_shootRequest;

	// Distance of the cargo when being carried
	float m_cargoCarryDistance;

	// The controller for this ship
	ControllerIF* m_controller;
};

