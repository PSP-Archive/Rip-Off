#include "PhysicsWorld.h"

// Always place as last include and only in cpp files!!
#include "foundation/Debug.h"

//--------------------------------------------------------------------------------
PhysicsWorld::PhysicsWorld() :
	m_boundaryMin(-1.2f, 1.2f), // enlarged boundaries a bit, Birgit
	m_boundaryMax(-1.2f, 1.2f)
{
	// Initially nobody can collide
	for(unsigned int i=0; i<MAX_PHYSICS_GROUPS; i++)
	{
		m_groupMapping[i] = 0;
	}
}

//--------------------------------------------------------------------------------
PhysicsWorld::~PhysicsWorld(void)
{

}

//--------------------------------------------------------------------------------
void PhysicsWorld::addCollisionPair(int group1Id, int group2Id)
{
	// Set the proper bits in the field
	m_groupMapping[group1Id] |= 1 << group2Id;
	m_groupMapping[group2Id] |= 1 << group1Id;
}

//--------------------------------------------------------------------------------
void PhysicsWorld::update(float stepSize)
{
	//MOVE ALL BODIES BY THE STEP SIZE SPECIFIED
	for(BodyIt it = m_bodies.begin(); it != m_bodies.end(); ++it)
	{
		(*it)->move(stepSize);

		// Check if outside the bounds
		if((*it)->getPosition().x < m_boundaryMin.x ||
			(*it)->getPosition().y < m_boundaryMin.y ||
			(*it)->getPosition().x > m_boundaryMax.x ||
			(*it)->getPosition().y > m_boundaryMax.y)
		{
			(*it)->onOutOfBounds();
		}
	}

	//CHECK FOR COLLISIONS AFTER THIS MOVE
	for(BodyIt it1 = m_bodies.begin(); it1 != m_bodies.end(); ++it1)
	{
		for(BodyIt it2 = m_bodies.begin(); it2 != m_bodies.end(); ++it2)
		{
			if(CanCollide((*it1)->getPhysicsGroup(), (*it2)->getPhysicsGroup())
				&& (*it1)->hasCollided((*it2)))
			{
				//COLLISION RESPONSE HERE (not needed for now)
				(*it1)->onCollide((*it2));
				(*it2)->onCollide((*it1));
			}
		}
	}
}

//--------------------------------------------------------------------------------
void PhysicsWorld::cleanup()
{
	m_bodies.clear();
}

//--------------------------------------------------------------------------------
void
PhysicsWorld::setBoundary(float minX, float minY, float maxX, float maxY)
{
	// Just make sure
	float _minX = (minX < maxX) ? minX : maxX;
	float _maxX = (minX > maxX) ? minX : maxX;
	float _minY = (minY < maxY) ? minY : maxY;
	float _maxY = (minY > maxY) ? minY : maxY;

	m_boundaryMin[0] = _minX;
	m_boundaryMin[1] = _minY;
	m_boundaryMax[0] = _maxX;
	m_boundaryMax[1] = _maxY;
}
