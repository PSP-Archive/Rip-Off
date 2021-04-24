#pragma once

#ifdef _3D
#ifdef _PC

#include "../../3dgraphics/LaserEffect3DRendererIF.h"

#include "GL/glut.h"
#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glut32.lib")
#include "managers/MeshManager.h"

class PCLaserEffect3DRenderer : public LaserEffect3DRendererIF {
public:
	void applyTransforms(const Vector3f& pos, const Vector3f& camDirection, float angle, float totalOffset, float texDelta, int hasDeltaTex=0) const;
	void discardTransforms(int hasDeltaTex) const;
};


inline void PCLaserEffect3DRenderer::applyTransforms(const Vector3f& pos, const Vector3f& camDirection, float angle, float totalOffset, float texDelta, int hasDeltaTex) const{
	if (hasDeltaTex){
		glMatrixMode(GL_TEXTURE);
		glPushMatrix();
		glTranslatef(texDelta,0,0);
	}//else{
	//	glDisable(GL_DEPTH_TEST);
	//}
	glMatrixMode(GL_MODELVIEW);

		glPushMatrix();
		
		glTranslatef(pos.x(),pos.y(),0);
		
		glRotatef(angle,camDirection.x(),camDirection.y(),camDirection.z());
		glTranslatef(totalOffset,0,0);

}

inline void PCLaserEffect3DRenderer::discardTransforms(int hasDeltaTex) const{
	if (hasDeltaTex){
		glMatrixMode(GL_TEXTURE);
		glPopMatrix();
	}//else{
	//	glEnable(GL_DEPTH_TEST);
	//}
	

		glMatrixMode(GL_MODELVIEW);

		glPopMatrix();
}

#endif
#endif