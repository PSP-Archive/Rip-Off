#pragma once

#include <vector>

#include "graphics/EffectIF.h"
#include "vectorgraphics/GFXObjectVector.h"
#include "foundation/Timer.h"

//--------------------------------------------------------------------------------
class VectorLaserEffect : public EffectIF
{
public:
	// Ctor
	VectorLaserEffect();

	// Renders the effect
	void Start();
	
	// Renders the effect
	void Render();
	
	// Updates the effect
	void Update();

	// Returns a reference to the graphics object
	GFXObjectVector& getGfxObject() { return m_vectorObject; }

	// Setters
	void setLength(float v) { m_length = v; }
	void setWidth(float v) { m_width = v; }
	void setDuration(float v) { m_duration = v; }
	void setOffset(float v) { m_offset = v; }

private:
	// Data
	GFXObjectVector m_vectorObject;

	// Effects timer
	Timer m_timer;

	// Params
	float m_length;
	float m_width;
	float m_duration;
	float m_offset;
};