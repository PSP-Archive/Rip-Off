#pragma once

#include "engine/Ship.h"
#include "foundation/Timer.h"

//--------------------------------------------------------------------------------
class GuardianShip : public Ship
{
public:
	// Ctor
	GuardianShip();
	
	// Dtor
	virtual ~GuardianShip() {}

	// Shoots a bullet
	void shoot();

	// Called when the entity should be updated
	virtual void onUpdate(float time);

	// Called when the ship collides
	void onCollide(const RigidBody *body);

	// Callback called when the body leaves the world bounds
	void onOutOfBounds();
	
	// Respawns the ship
	void spawn();
	
	// Kills the ship
	void kill();

	// Setters
	void setRespawnTime(float t) { m_respawnTime = t; }
	void setRespawnPoint(const Vector2f& t) { m_respawnPoint = t; }
	void setRespawnRotation(float t) { m_respawnRotation = t; }
	
private:
	static const unsigned int NUM_BULLETS = 4;
	
	// The bullets pool
	Bullet* m_bullets[NUM_BULLETS];

	// Respawn
	Timer m_respawnTimer;
	float m_respawnTime;
	Vector2f m_respawnPoint;
	float m_respawnRotation;
};

