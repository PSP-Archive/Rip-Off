#pragma once

#include <list>
#include "rigidbody.h"

//--------------------------------------------------------------------------------
class PhysicsWorld
{
public:
	// Ctor
	PhysicsWorld(void);

	// Dtor
	~PhysicsWorld(void);

	// Adds a body to the world
	void addBody(RigidBody *body)  { m_bodies.push_back(body); };
	
	// Removes a body from the world
	void removeBody(RigidBody *body) { m_bodies.remove(body); };
	
	// Enables two groups of colliding
	void addCollisionPair(int group1Id, int group2Id);
	
	// Updates the world
	void update(float stepSize);

	// Cleans up
	void cleanup();

	// Sets the world's boundary
	void setBoundary(float minX, float minY, float maxX, float maxY);

	static const unsigned int MAX_PHYSICS_GROUPS = 10;
private:
	// World boundary
	Vector2f m_boundaryMin;
	Vector2f m_boundaryMax;
	
	// The bodies in the world
	std::list<RigidBody*> m_bodies;
	typedef std::list<RigidBody*>::iterator BodyIt;

	// Stores what groups can collide with what
	unsigned int m_groupMapping[MAX_PHYSICS_GROUPS];

	// Returns weather two group can collide
	bool CanCollide(const int group1Id, const int group2Id);
};

//--------------------------------------------------------------------------------
inline
bool PhysicsWorld::CanCollide(const int group1Id, const int group2Id)
{
	return (m_groupMapping[group1Id] & (1 << group2Id)) != 0;
}

