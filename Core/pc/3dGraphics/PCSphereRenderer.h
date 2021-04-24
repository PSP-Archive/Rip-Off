#pragma once

#ifdef _3D
#ifdef _PC

#include "GL/glut.h"
#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glut32.lib")

#include "../../3dgraphics/SphereRendererIF.h"


class PCSphereRenderer: public SphereRendererIF{
public:
	void drawCore(unsigned int stacks, unsigned int slices) const;
};


inline void PCSphereRenderer::drawCore(unsigned int stacks, unsigned int slices) const{
	glDrawElements(GL_TRIANGLE_FAN, slices+2, GL_UNSIGNED_INT, (unsigned int*)NULL);
	for (unsigned int i = 0; i < (stacks-2); i++) { 
		glDrawElements(GL_TRIANGLE_STRIP, (slices+1)*2, GL_UNSIGNED_INT, (unsigned int*)NULL+(slices+2+i*(slices+1)*2));
	}
	glDrawElements(GL_TRIANGLE_FAN, slices+2, GL_UNSIGNED_INT, (unsigned int*)NULL+(slices+2+(stacks-2)*(slices+1)*2));
}


#endif
#endif