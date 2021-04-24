#pragma once

#include "foundation/Vector2f.h"
#include "foundation/singleton.h"
#include "graphics/SceneIF.h"
#include "vectorgraphics/LinePrimitive.h"
#include "vectorgraphics/VectorRenderer.h"

//--------------------------------------------------------------------------------
/**
	Manager class for the Vector graphics.
*/
class VectorScene : public SceneIF
{
public:
	void initializeForRendering();
	void startRender() const;
	void endRender() const;
	void cleanUpForRendering();

	// Returns the reference to the vector renderer
	static VectorRenderer& getRenderer() { return m_renderer; }

protected:
	void onAspectRatioUpdate() { m_renderer.setAspectRatio(getAspectRatio()); }

private:
	static VectorRenderer m_renderer;
};
