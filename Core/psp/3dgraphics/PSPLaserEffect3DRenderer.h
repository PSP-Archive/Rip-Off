#pragma once

#ifdef _3D
#ifdef _SPSP

#include "../../3dgraphics/LaserEffect3DRendererIF.h"
#include "../../3dgraphics/managers/MeshManager.h"

#include <libgu.h>
#include <libgum.h>

class PSPLaserEffect3DRenderer : public LaserEffect3DRendererIF {
public:
	void applyTransforms(const Vector3f& pos, const Vector3f& camDirection, float angle, float totalOffset, float texDelta, int hasDeltaTex=0) const;
	void discardTransforms(int hasDeltaTex) const;
};


inline void PSPLaserEffect3DRenderer::applyTransforms(const Vector3f& pos, const Vector3f& camDirection, float angle, float totalOffset, float texDelta, int hasDeltaTex) const{
	ScePspFVector3 p=pos.getPSPVector();
	p.z=0.0f;

	ScePspFVector3 totOff;
	totOff.x=totalOffset; totOff.y=0.0f; totOff.z=0.0f;

	if (hasDeltaTex){
		ScePspFVector3 v;
		v.x=texDelta; v.y=0; v.z=0;
		sceGumMatrixMode(SCEGU_MATRIX_TEXTURE);
		sceGumPushMatrix();
			sceGumTranslate(&v);
	}
	
	sceGumMatrixMode(SCEGU_MATRIX_WORLD);
	sceGumPushMatrix();
		sceGumTranslate(&p);
		sceGumRotateZ(-angle*DegRad);
		sceGumTranslate(&totOff);

	/*if (hasDeltaTex){
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
	*/
}

inline void PSPLaserEffect3DRenderer::discardTransforms(int hasDeltaTex) const{
	if (hasDeltaTex){
		sceGumMatrixMode(SCEGU_MATRIX_TEXTURE);
		sceGumPopMatrix();
	}
	sceGumMatrixMode(SCEGU_MATRIX_WORLD);
	sceGumPopMatrix();
	/*if (hasDeltaTex){
		glMatrixMode(GL_TEXTURE);
		glPopMatrix();
	}
	glMatrixMode(GL_MODELVIEW);

	glPopMatrix();
	*/
}

#endif
#endif