#ifdef _3D
#ifdef _PC

#include "../3dgraphics/IconRendererIF.h"


#include "GL/glut.h"
#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glut32.lib")

class PCIconRenderer:public IconRendererIF{
public:
	void setNextIconDisplacement(float d) const;
	void enableRendering(const Vector3f& centre, float angle=0.0f, const Vector3f& axis=Vector3f(0,0,1)) const;
	void disableRendering() const;
};

inline void PCIconRenderer::setNextIconDisplacement(float d) const{
	glTranslatef(d,0,0);
}

inline void PCIconRenderer::enableRendering(const Vector3f& centre, float angle, const Vector3f& axis) const{
	//glDepthMask(GL_FALSE);
	glDisable(GL_DEPTH_TEST);


	glPushMatrix();
		
		//translate to its associated GFXObject centre
		
		glTranslatef(centre.x(),centre.y(),centre.z());
		glRotatef(angle,axis.x(),axis.y(),axis.z());
}

inline void PCIconRenderer::disableRendering() const{
	glPopMatrix();

	glEnable(GL_DEPTH_TEST);
}


#endif
#endif