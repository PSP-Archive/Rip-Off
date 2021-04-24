/* VERSION HISTORY

20/02/2010 - ??? - Created by...
20/02/2010 - David Wright - Began adding methods and attribures required for movement
26/02/10	- Birgit - added getter functions for position, orientation, velocity and maxSpeed
07/03/10	- Birgit - added query fun for radius
09/03/10	- Birgit - added orientation member and method
*/

#pragma once
#include "foundation/Vector2f.h"
#include "foundation/Angle.h"

class EffectIF;

//--------------------------------------------------------------------------------
class RigidBody
{
public:
	// Ctor
	RigidBody();

	// Dtor
	virtual ~RigidBody() {};

	// Callback called when the body collides with another body
	virtual void onCollide(const RigidBody *body) = 0;
	
	// Callback called when the body leaves the world bounds
	virtual void onOutOfBounds() {}
	
	// Returns weather the body has collided or not with another body
	bool hasCollided(const RigidBody *body);

	// Applies a force to the body
	void applyForce(const Vector2f& force);

	// Manually set the position of the body
	void setPosition(const Vector2f &position) { m_position = position; }

	// Return the position of the body
	const Vector2f& getPosition() { return m_position; }

	// Return the position of the body
	const Vector2f& getOrientation() { return m_orientation; }

	// Manually set the velocity of the body
	void setVelocity(const Vector2f &v) { m_velocity = v; }

	void setEffect(EffectIF* pEffect) const;

	// Return the velocity of the body
	const Vector2f& getVelocity() { return m_velocity; }

	// Manually sets the rotation of the body
	// also updates orientation
	void setRotation(float rotation);

	// Returns the current rotation of the body
	float getRotation() { return m_rotation.getDegrees(); }
	const Angle& getRotationAngle() { return m_rotation; }

	// Updates the rigid body dynamics
	void move(const float stepSize);

	// Sets the mass
	void setMass(float mass) { m_mass = mass; }
	
	// Sets the radius used for collision
	void setRadius(float radius) { m_radius = radius; }

	// query radius
	float getRadius() const { return m_radius; }
	
	// Sets the max magnitude of the velocity
	void setMaxSpeed(float maxSpeed) { m_maxSpeed = maxSpeed; }

	// Returns the max magnitude of the velocity
	float getMaxSpeed() { return m_maxSpeed; }

	// Sets the drag
	void setDrag(float d) { m_drag = d; }

	// Awake
	void sleep() { m_alive = false; }
	void wake() { m_alive = true; }
	bool queryAlive() const { return m_alive; }

	// Sets the collision detection group
	void setPhysicsGroup(unsigned int g) { m_group = g; }

	// Returns the collision detection group
	unsigned int getPhysicsGroup() const { return m_group; }

	// return ID so AI can identify itself
	int getID() { return m_id; }
	static void resetID(int id) { count = id; }
	void setID(int id) { m_id = id; }
	void updateID(int id) { m_id += id; }

protected:

	//id used to prevent collision detection on itself
	static int count;
	int m_id;

	float m_mass;

	//Location and orientation
	Vector2f m_position;
	Vector2f m_orientation;
	Angle m_rotation;
	
	// Dynamics params
	Vector2f m_velocity;
	float m_drag;
	float m_maxSpeed;

	//Collision values
	float m_radius;

	//Total forces
	Vector2f m_totalForce;

	// States weather the object is active or sleeping
	bool m_alive;

	mutable EffectIF *m_pEffect;		//the fire jet needs to know when the ship is killed

	// The physics group for collision detection
	unsigned int m_group;
};
