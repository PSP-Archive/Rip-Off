#pragma once

#ifdef _3D

//the scenes need to have some attributes set at the
//creation of the window, like enable lights/culling etc
//these are platform dependend, so this class
//must be derived on each platform
//
//the main app must call initializeForRendering before starting the game loop

class GFX3DInitializerIF{
public:
	virtual ~GFX3DInitializerIF(){}


	//common methods that are called before the rendering loop;
	virtual void startRendering() const=0;


	//initialize the scene, setting the OpenGL scene (like enable lights, textures etc)
	//it returns in pWidth and pHeight the current sizes of the screen (getting the opengl viewport)
	virtual void initializeForRendering(int *pWidth, int *pHeight, int lightOn) const=0;

	virtual void getScreenSize(int *pWidth, int *pHeight) const=0;
};

#endif