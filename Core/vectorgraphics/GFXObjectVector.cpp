#ifdef _VECTOR

#include <algorithm>
#include "vectorgraphics/GFXObjectVector.h"
#include "vectorgraphics/VectorScene.h"

// Always place as last include and only in cpp files!!
#include "foundation/Debug.h"

//--------------------------------------------------------------------------------
GFXObjectVector::GFXObjectVector() :
	m_geometry(NULL),
	m_lineWidth(1.0f),
	m_scale(1.0f),
	m_colour(1.0f, 1.0f, 1.0f, 1.0f)
{
	// empty
}

//--------------------------------------------------------------------------------
void
GFXObjectVector::render(const Vector2f& position, float angle)
{
	if(m_geometry)
	{
		VectorScene::getRenderer().Render(*m_geometry, m_colour, m_lineWidth, position, angle, m_scale);
	}
}

//--------------------------------------------------------------------------------
GFXObjectVector::~GFXObjectVector()
{
	if(m_geometry)
	{
		delete m_geometry;
	}
}

#endif
