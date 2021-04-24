#include "engine/Cargo.h"
#include "engine/Game.h"

// Always place as last include and only in cpp files!!
#include "foundation/Debug.h"

//--------------------------------------------------------------------------------
Cargo::Cargo()
{
	setEntityType(Game::CARGO);
}

//--------------------------------------------------------------------------------
void Cargo::onCollide(const RigidBody *body)
{
	
}

//--------------------------------------------------------------------------------
void Cargo::onOutOfBounds()
{

}