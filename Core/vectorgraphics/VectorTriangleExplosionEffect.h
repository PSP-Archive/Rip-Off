#pragma once

#include <vector>

#include "graphics/EffectIF.h"
#include "vectorgraphics/GFXObjectVector.h"
#include "foundation/Timer.h"

//--------------------------------------------------------------------------------
class VectorTriangleExplosionEffect : public EffectIF
{
public:
	// Ctor
	VectorTriangleExplosionEffect();

	// Renders the effect
	void Start();
	
	// Renders the effect
	void Render();
	
	// Updates the effect
	void Update();

	// Returns a reference to the graphics object
	GFXObjectVector& getGfxObject() { return m_vectorObject; }

	// Setters
	void setTriangleCount(unsigned int v) { m_triangleCount = v; }
	void setDuration(float v) { m_duration = v; }
	void setTriangleSize(float v) { m_triangleSize = v; }

private:
	// Data
	GFXObjectVector m_vectorObject;
	std::vector<Vector2f> m_directions;

	// Effects timer
	Timer m_timer;

	// Params
	unsigned int m_triangleCount;
	float m_duration;
	float m_triangleSize;
};