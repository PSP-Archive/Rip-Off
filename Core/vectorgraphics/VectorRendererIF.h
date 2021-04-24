#pragma once

#include <cassert>

#include "LinePrimitive.h"

// Disable warning for unreferenced formal parameters as this is an interface
#pragma warning( disable: 4100 )

//--------------------------------------------------------------------------------
/**
	Generic interface for the vector engine renderer.
*/
class VectorRendererIF
{
public:
	// Called when the vector rendering should be initialized
	void init() { assert(!"Interface not implemented"); }

	// Called when starting the render loop
	void startRender() { assert(!"Interface not implemented"); }

	// Called when a vectro primitive should be rendered at a position with a rotation
	void Render(const LinePrimitive& primitive, const Vector4f& color, float lineWidth,
		const Vector2f& position, float angle, float scale)
	{
		assert(!"Interface not implemented");
	}

	// Called when starting the render loop
	void endRender() { assert(!"Interface not implemented"); }

	// Called when the vector rendering should be cleaned up
	void cleanUp() { assert(!"Interface not implemented"); }

	// Sets the aspect ratio
	void setAspectRatio(float ar) { m_aspectRatio = ar; }

	// Returns the current aspect ratio
	float getAspectRatio() { return m_aspectRatio; }

private:
	float m_aspectRatio;
};