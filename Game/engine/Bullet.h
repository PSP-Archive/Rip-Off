#pragma once
#include "engine/GameEntity.h"

//--------------------------------------------------------------------------------
class Bullet : public GameEntity
{
public:
	// Ctor
	Bullet();

	// Dtor
	virtual ~Bullet() {}

	// React to collisions
	void onCollide(const RigidBody *body);

	// React to out of bounds
	void onOutOfBounds();
};
