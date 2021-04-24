#pragma once

#include <cassert>

// Disable warning for unreferenced formal parameters as this is an interface
#pragma warning( disable: 4100 )

//--------------------------------------------------------------------------------
class SceneIF
{
public:
	//Initialize attributes like: activate culling, normalize normals etc,
	//which are called after the creation of the window.
	virtual void initializeForRendering() { assert(!"Interface not implemented"); }

	//render the elements that contain the environment
	//(like background and other artifacts)
	virtual void startRender() const { assert(!"Interface not implemented"); }

	// Stop rendering
	virtual void endRender() const { assert(!"Interface not implemented"); }

	// Called when the rendering should be cleaned up
	virtual void cleanUpForRendering() { assert(!"Interface not implemented"); }

	// Sets the aspect ratio
	void setAspectRatio(float ar) { m_aspectRatio = ar; onAspectRatioUpdate(); }

	// Returns the current aspect ratio
	float getAspectRatio() { return m_aspectRatio; }

protected:
	// Called when the aspect ratio is updated
	virtual void onAspectRatioUpdate() {}

private:
	float m_aspectRatio;
};