#ifdef _VECTOR

#include "VectorScene.h"

// Always place as last include and only in cpp files!!
#include "foundation/Debug.h"

VectorRenderer VectorScene::m_renderer;

//--------------------------------------------------------------------------------
void
VectorScene::initializeForRendering()
{
	m_renderer.init();
}

//--------------------------------------------------------------------------------
void
VectorScene::startRender() const
{
	m_renderer.startRender();
}

//--------------------------------------------------------------------------------
void
VectorScene::endRender() const
{
	m_renderer.endRender();
}

//--------------------------------------------------------------------------------
void
VectorScene::cleanUpForRendering()
{
	m_renderer.cleanUp();
}

#endif
