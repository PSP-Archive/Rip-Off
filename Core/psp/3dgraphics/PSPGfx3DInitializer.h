#pragma once

#ifdef _3D
#ifdef _SPSP

#include "../../3dgraphics/GFX3DInitializerIF.h"

#include <libgu.h>
#include <libgum.h>

class PSPGfx3DInitializer:public GFX3DInitializerIF{
public:

	//common methods that are called before the rendering loop;
	void startRendering() const;

	void initializeForRendering(int *pWidth, int *pHeight, int lightOn) const;

	void getScreenSize(int *pWidth, int *pHeight) const;

};

#endif
#endif