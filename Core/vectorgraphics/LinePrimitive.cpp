#ifdef _VECTOR

#include "vectorgraphics/LinePrimitive.h"

// Always place as last include and only in cpp files!!
#include "foundation/Debug.h"

//--------------------------------------------------------------------------------
LinePrimitive::LinePrimitive() :
	m_LPType(STRIP)
{
	// empty
}

//--------------------------------------------------------------------------------
void
LinePrimitive::AddPoint(const Vector2f& point)
{
	m_data.push_back(point);
}

#endif
