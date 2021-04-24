#pragma once

#ifdef _3D
#ifdef _PC

#include "../../3dgraphics/GFX3DInitializerIF.h"

#include "GL/glut.h"
#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glut32.lib")

class PCGfx3dInitializer:public GFX3DInitializerIF{
public:

	//common methods that are called before the rendering loop;
	void startRendering() const;

	void initializeForRendering(int *pWidth, int *pHeight, int lightOn) const;

	void getScreenSize(int *pWidth, int *pHeight) const;

};

#endif
#endif