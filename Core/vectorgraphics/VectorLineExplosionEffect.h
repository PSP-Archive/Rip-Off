#pragma once

#include "graphics/EffectIF.h"
#include "vectorgraphics/GFXObjectVector.h"
#include "foundation/Timer.h"

//--------------------------------------------------------------------------------
class VectorLineExplosionEffect : public EffectIF
{
public:
	// Ctor
	VectorLineExplosionEffect();

	// Renders the effect
	void Start();
	
	// Renders the effect
	void Render();
	
	// Updates the effect
	void Update();

	// Returns a reference to the graphics object
	GFXObjectVector& getGfxObject() { return m_vectorObject; }

	// Setters
	void setLineCount(unsigned int v) { m_lines = v; }
	void setDuration(float v) { m_duration = v; }
	void setLengthRandomness(float v) { m_lengthRand = v; }
	void setAngleRandomness(float v) { m_angleRand = v; }

private:
	// Collection of lines
	GFXObjectVector m_vectorObject;
	
	// Effect timer
	Timer m_timer;

	// Parameters
	unsigned int m_lines;
	float m_duration;
	float m_lengthRand;
	float m_angleRand;
};