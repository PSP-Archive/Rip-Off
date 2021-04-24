#pragma once

#ifdef _PC

#include <windows.h>
#include <gl/gl.h>

#include "vectorgraphics/LinePrimitive.h"
#include "vectorgraphics/VectorRendererIF.h"

//--------------------------------------------------------------------------------
/**
	PC specific vector renderer.
*/
class PCVectorRenderer : public VectorRendererIF
{
public:
	void init();
	void Render(LinePrimitive& primitive, const Vector4f& color, float lineWidth,
		const Vector2f& position, float angle, float scale);
	void cleanUp();
	void startRender();
	void endRender();
};

#endif