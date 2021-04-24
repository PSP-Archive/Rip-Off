#include "VectorTriangleExplosionEffect.h"

#include <cstdlib>
#include <cmath>

#include "vectorgraphics/VectorScene.h"

// Always place as last include and only in cpp files!!
#include "foundation/Debug.h"

//--------------------------------------------------------------------------------
VectorTriangleExplosionEffect::VectorTriangleExplosionEffect() :
	m_triangleCount(5),
	m_duration(2.0),
	m_triangleSize(0.5)
{
	// empty
}

//--------------------------------------------------------------------------------
void
VectorTriangleExplosionEffect::Start()
{
	// Resize the vector
	m_directions.resize(m_triangleCount);
	
	//	Radial Lines
	LinePrimitive* triangleExplosion = new LinePrimitive();
	triangleExplosion->SetLPType(LinePrimitive::LIST);
	
	// Create the vertices
	for(unsigned int i=0; i<m_triangleCount; i++)
	{
		// Assign the velocity direction
		m_directions[i][0] = float(cos((360.0f / m_triangleCount) * i * DegRad));
		m_directions[i][1] = float(sin((360.0f / m_triangleCount) * i * DegRad));

		// Create random triangle (but not so random)
		Vector2f m_verts[3];
		float offset = float(rand() % 360);
		for(int j=0; j<3; j++)
		{
			float angle = (120 * j) + offset + (-50 + (float(rand()) / RAND_MAX) * 100);
			m_verts[j][0] = float(cos(angle * DegRad)) * m_triangleSize;
			m_verts[j][1] = float(sin(angle * DegRad)) * m_triangleSize;
			
			// Move the triangles a little in their direction
			m_verts[j] += 0.5f * m_directions[i];
		}
	
		// Create the triangle		
		triangleExplosion->AddPoint(m_verts[0]);
		triangleExplosion->AddPoint(m_verts[1]);
		triangleExplosion->AddPoint(m_verts[1]);
		triangleExplosion->AddPoint(m_verts[2]);
		triangleExplosion->AddPoint(m_verts[2]);
		triangleExplosion->AddPoint(m_verts[0]);
	}

	// Create VectorObject from linePrimitive and add to list
	m_vectorObject.setPrimitive(triangleExplosion);

	m_timer.reset();
}

//--------------------------------------------------------------------------------
void VectorTriangleExplosionEffect::Render()
{
	if(!isFinished() && m_vectorObject.GetLinePrimitive())
	{
		m_vectorObject.render(getPosition(), getRotation());
	}
}

//--------------------------------------------------------------------------------
void VectorTriangleExplosionEffect::Update()
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
		int i=0;
		for(it = m_vectorObject.GetLinePrimitive()->GetList().begin();
			it != m_vectorObject.GetLinePrimitive()->GetList().end();
			++it, ++i)
		{
			// Move triangles
			(*it) += m_directions[i/6] * m_timer.getFrameTime() / m_duration;
		}
	}
}