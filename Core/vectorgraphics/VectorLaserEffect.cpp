#include "vectorgraphics/VectorLaserEffect.h"

// Always place as last include and only in cpp files!!
#include "foundation/Debug.h"

//--------------------------------------------------------------------------------
VectorLaserEffect::VectorLaserEffect() :
	m_length(0.2f),
	m_width(0.01f),
	m_duration(0.2f),
	m_offset(0.0f)
{
	// empty
}

//--------------------------------------------------------------------------------
void
VectorLaserEffect::Start()
{
	LinePrimitive* laser = new LinePrimitive();
	laser->SetLPType(LinePrimitive::STRIP);
	
	// Create the lines
	laser->AddPoint(Vector2f(m_offset, -m_width));
	laser->AddPoint(Vector2f(m_length + m_offset, 0.0f));
	laser->AddPoint(Vector2f(m_offset, m_width));

	// Create VectorObject from linePrimitive and add to list
	m_vectorObject.setPrimitive(laser);

	m_timer.reset();
}

//--------------------------------------------------------------------------------
void VectorLaserEffect::Render()
{
	if(!isFinished() && m_vectorObject.GetLinePrimitive())
	{
		m_vectorObject.render(getPosition(), getRotation());
	}
}

//--------------------------------------------------------------------------------
void VectorLaserEffect::Update()
{
	if(!isFinished() && m_vectorObject.GetLinePrimitive())
	{
		m_timer.update();

		// Check if time expired
		if(m_timer.getTime() > m_duration)
		{
			terminate();
			return;
		}

		// Nothing to update
	}
}