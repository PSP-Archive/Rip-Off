#pragma once

#ifdef _3D
#ifdef _PC

#include "../../3dgraphics/CameraRendererIF.h"

#include "GL/glut.h"
#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glut32.lib")

class PCCameraRenderer:public CameraRendererIF{
public:
	void applyLookAt(const Vector3f& observer, const Vector3f lookAt, const Vector3f& up) const;
	void applyProjection(float fov, float aspect, float near, float far) const;
	void applyViewport(float width, float height) const;
	
	void adjustScaling(float s, const Vector3f& pivot, float zCentre=0) const;
	void resetScaling() const;
	//void applyScale(float s) const;
	//void applyTranslate(float tz) const;
};


inline void PCCameraRenderer::adjustScaling(float s, const Vector3f& pivot, float zCentre) const{
	glPushMatrix();
		//glTranslatef(0,0,pivot.z());
		glTranslatef(s*pivot.x(),s*pivot.y(),s*zCentre+pivot.z());
		glScalef(s,s,s);
		//glTranslatef(-pivot.x(),-pivot.y(),-pivot.z());
		//glTranslatef(0,0,-pivot.z());
}
inline void PCCameraRenderer::resetScaling() const{
	glPopMatrix();
}

//inline void PCCameraRenderer::applyTranslate(float tz) const{
//	glTranslatef(0,0,tz);
//}

//inline void PCCameraRenderer::applyScale(float s) const{
//	glScalef(s,s,s);
//}

inline void PCCameraRenderer::applyLookAt(const Vector3f& observer, const Vector3f lookAt, const Vector3f& vup) const{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(observer.x(),observer.y(),observer.z(),lookAt.x(), lookAt.y(),lookAt.z(), vup.x(),vup.y(),vup.z());
}

inline void PCCameraRenderer::applyProjection(float fov, float aspect, float _near, float _far) const{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, aspect, _near, _far); //(fov, aspect, near, far);
}

inline void PCCameraRenderer::applyViewport(float width, float height) const{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glViewport(0,0, width, height);
}

#endif
#endif