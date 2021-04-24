#pragma once

#include <list>

#include "foundation/Vector2f.h"
#include "foundation/Vector4f.h"

//--------------------------------------------------------------------------------
/**
	The basic rendering primitive for the vector engine.
*/
class LinePrimitive 
{
public:
	
	// Enumeration for the type of primitive
	// STRIP - the list of points should be connected to from a line strip
	// LIST - the points should be taken 2 by 2 to form separate lines
	enum LinePrimitiveType
	{
		STRIP = 0,
		LIST
	};

	// Ctor
	LinePrimitive();
	
	// Sets the type of primitive.
	void SetLPType (LinePrimitiveType LPType_in) { m_LPType = LPType_in; }
	
	// Returns the type of primitive.
	LinePrimitiveType GetLPType() const { return m_LPType; }

	// Adds a point to the primitive.
	void AddPoint(const Vector2f& point);

	// Returns a const reference to the list of points
	std::list<Vector2f>& GetList () { return m_data; }

private:
	// The point data
	std::list<Vector2f> m_data;
	LinePrimitiveType m_LPType;
};
