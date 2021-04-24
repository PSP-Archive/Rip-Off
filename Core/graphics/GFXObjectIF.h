#pragma once

#include <cassert>
#include "foundation/Vector2f.h"

// Disable warning for unreferenced formal parameters as this is an interface
#pragma warning( disable: 4100 )

//--------------------------------------------------------------------------------
/**
	Generic interface for an object with a graphical representation.
*/
class GFXObjectIF
{
public:
	// Called when the object should be rendered to the screen.
	virtual void render(const Vector2f& position, float angle) { assert(!"Interface not implemented"); }
};
