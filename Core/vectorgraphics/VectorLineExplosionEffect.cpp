#include "vectorgraphics/VectorLineExplosionEffect.h"
#include "vectorgraphics/VectorScene.h"

// Always place as last include and only in cpp files!!
#include "foundation/Debug.h"

//--------------------------------------------------------------------------------
VectorLineExplosionEffect::VectorLineExplosionEffect() :
	m_lines(20),
	m_duration(2.0f),
	m_lengthRand(0.1f),
	m_angleRand(20.0f)
{
	// empty
}

//--------------------------------------------------------------------------------
void VectorLineExplosionEffect::Start()
{
	//	Radial Lines
	LinePrimitive* radialExplosion = new LinePrimitive();
	radialExplosion->SetLPType(LinePrimitive::LIST);
	
	// create the vertices
	for(unsigned int i=0; i<m_lines; i++)
	{
		// The angle is randomized between [angle - m_angleRand/2, angle + m_angleRand/2]
		float angle = (360.0f / m_lines) * i + (-m_angleRand / 2 + (float(rand())/RAND_MAX)*m_angleRand);
		Vector2f vec(float(sin(angle * DegRad)), float(cos(angle * DegRad)));
		
		// The length is randomized between [1.0f - m_lengthRand/2, 1.0f + m_lengthRand/2]
		radialExplosion->AddPoint(Vector2f(0.0f, 0.0f));
		radialExplosion->AddPoint((1.0f + (-m_lengthRand / 2 + (float(rand())/RAND_MAX)*m_lengthRand)) * vec);
	}

	// Create VectorObject from linePrimitive and add to list
	m_vectorObject.setPrimitive(radialExplosion);

	m_timer.reset();
}

//--------------------------------------------------------------------------------
void VectorLineExplosionEffect::Render()
{
	if(!isFinished() && m_vectorObject.GetLinePrimitive())
	{
		m_vectorObject.render(getPosition(), getRotation());
	}
}

//--------------------------------------------------------------------------------
void VectorLineExplosionEffect::Update()
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
		
		// Update
		std::list<Vector2f>::iterator it;
		for(it = m_vectorObject.GetLinePrimitive()->GetList().begin();
			it != m_vectorObject.GetLinePrimitive()->GetList().end();
			++it)
		{
			// Go to the next one as the first one is the line origin
			++it;

			// Change line size
			(*it) *= (1.0f - m_timer.getTime() / m_duration) /
				(1.0f - (m_timer.getTime() - m_timer.getFrameTime()) / m_duration);
		}
	}
}