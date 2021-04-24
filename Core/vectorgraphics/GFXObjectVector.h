#pragma once

#include "graphics/GFXObjectIF.h"
#include "vectorgraphics/LinePrimitive.h"
#include "vectorgraphics/VectorRenderer.h"

//--------------------------------------------------------------------------------
/**
	Basic vector rendering object.
*/
class GFXObjectVector : public GFXObjectIF
{
public:
	// Ctor
	GFXObjectVector();
	
	// Dtor
	~GFXObjectVector();
	
	// Renders the object at the position with the angle
	void render(const Vector2f& position, float angle);	
	
	// Adds a LinePrimitive to be rendered.
	void setPrimitive(LinePrimitive* lp) { m_geometry = lp; }

	// Returns the LinePrimitive
	LinePrimitive* GetLinePrimitive () { return m_geometry; }
	
	// Sets the color of the primitive.
	void SetColour (const Vector4f& colour_in)	{	m_colour = colour_in;	}
	
	// Returns the color of the primitive.
	Vector4f GetColour () const { return m_colour; }

	// Sets the color of the primitive.
	void SetLineWidth (float w) { m_lineWidth = w; }
	
	// Returns the color of the primitive.
	float GetLineWidth () const { return m_lineWidth; }

	// Sets the color of the primitive.
	void SetScale (float s) { m_scale = s; }
	
	// Returns the color of the primitive.
	float GetScale () const { return m_scale; }

private:
	LinePrimitive* m_geometry;

	// The width of the line
	float m_lineWidth;

	// The scale to apply on the object
	float m_scale;

	// The color of the primitive
	Vector4f m_colour;
};
