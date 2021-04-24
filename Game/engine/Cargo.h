#pragma once
#include "gameentity.h"

//--------------------------------------------------------------------------------
class Cargo : public GameEntity
{
public:
	// Ctor
	Cargo();

	// Dtor
	virtual ~Cargo() {}

	// Called when the ship collides
	void onCollide(const RigidBody *body);

	// Callback called when the body leaves the world bounds
	void onOutOfBounds();
};
