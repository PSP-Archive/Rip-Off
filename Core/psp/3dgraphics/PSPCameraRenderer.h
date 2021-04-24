#pragma once

#ifdef _3D
#ifdef _SPSP

#include "../../3dgraphics/CameraRendererIF.h"

#include <libgu.h>
#include <libgum.h>

class PSPCameraRenderer:public CameraRendererIF{
public:
	void applyLookAt(const Vector3f& observer, const Vector3f lookAt, const Vector3f& up) const;
	void applyProjection(float fov, float aspect, float near, float far) const;
	void applyViewport(float width, float height) const;
	
	void adjustScaling(float s, const Vector3f& pivot, float zCentre=0) const;
	void resetScaling() const;
};


inline void PSPCameraRenderer::adjustScaling(float s, const Vector3f& pivot, float zCentre) const{
	ScePspFVector3 v=pivot.getPSPVector();
	v.x*=s; v.y*=s; v.z+=s*(zCentre-0.4f);
	ScePspFVector3 scaleV;
	scaleV.x=s;
	scaleV.y=s;
	scaleV.z=s;//(s,s,s);

	sceGumPushMatrix();
		sceGumTranslate(&v);
		sceGumScale(&scaleV);
	
}
inline void PSPCameraRenderer::resetScaling() const{
	sceGumPopMatrix();
}

inline void PSPCameraRenderer::applyLookAt(const Vector3f& observer, const Vector3f lookAt, const Vector3f& vup) const{
	
	sceGumMatrixMode(SCEGU_MATRIX_WORLD);
	sceGumLoadIdentity();

	//sceGumLookAt(&observer.getPSPVector(),&lookAt.getPSPVector(), &vup.getPSPVector());
	sceGumLookAt(observer.getAddrPSPVector(),lookAt.getAddrPSPVector(), vup.getAddrPSPVector());

	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	//gluLookAt(observer.x(),observer.y(),observer.z(),lookAt.x(), lookAt.y(),lookAt.z(), vup.x(),vup.y(),vup.z());
	
}

inline void PSPCameraRenderer::applyProjection(float fov, float aspect, float _near, float _far) const{
	
	sceGumMatrixMode(SCEGU_MATRIX_PROJECTION);
	sceGumLoadIdentity();
	sceGumPerspective(fov, aspect, _near, _far);
	
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//gluPerspective(fov, aspect, _near, _far); //(fov, aspect, near, far);
	
}

inline void PSPCameraRenderer::applyViewport(float width, float height) const{

	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	//glViewport(0,0, width, height);

	//sceGumMatrixMode(SCEGU_MATRIX_VIEW);
	sceGumMatrixMode(SCEGU_MATRIX_WORLD);
	sceGumLoadIdentity();

	//sceGumMatrixMode(SCEGU_MATRIX_VIEW);
	//sceGumLoadIdentity();
	sceGuOffset(SCEGU_SCR_OFFSETX, SCEGU_SCR_OFFSETY);
	sceGuViewport(2048, 2048, SCEGU_SCR_WIDTH, SCEGU_SCR_HEIGHT);
	sceGuDepthRange(50000, 10000);

	sceGuScissor(0, 0, SCEGU_SCR_WIDTH, SCEGU_SCR_HEIGHT);
	sceGuEnable(SCEGU_SCISSOR_TEST);
	//sceGumMatrixMode(SCEGU_MATRIX_WORLD);

}

#endif
#endif