#pragma once



#include "vectorgraphics/LinePrimitive.h"
#include "vectorgraphics/VectorRendererIF.h"

//--------------------------------------------------------------------------------
/**
	PSP specific vector renderer.
*/
class PSPVectorRenderer : public VectorRendererIF
{
public:
	void init();
	void Render(LinePrimitive& primitive, const Vector4f& color, float lineWidth,
		const Vector2f& position, float angle, float scale);
	void cleanUp();
	void startRender();
	void endRender();
};