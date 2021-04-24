#include "PCGfx3dInitializer.h"

#ifdef _3D
#ifdef _PC


void PCGfx3dInitializer::initializeForRendering(int *pWidth, int *pHeight, int lightOn) const{
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	getScreenSize(pWidth,pHeight);

	if (lightOn){
		glEnable(GL_LIGHTING);
		glShadeModel(GL_SMOOTH);
		glEnable(GL_NORMALIZE);
	}

	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
}

void PCGfx3dInitializer::startRendering() const{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

void PCGfx3dInitializer::getScreenSize(int *pWidth, int *pHeight) const{
	int data[4];
	glGetIntegerv(GL_VIEWPORT,data);
	*pWidth=data[2]-data[0];
	*pHeight=data[3]-data[1];
}

#endif
#endif