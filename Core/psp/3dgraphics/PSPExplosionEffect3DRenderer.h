
#pragma once

#ifdef _3D
#ifdef _SPSP

#include "../../3dgraphics/ExplosionEffect3DRendererIF.h"
#include "../../3dgraphics/managers/MeshManager.h"

#include <libgu.h>
#include <libgum.h>

class PSPExplosionEffect3DRenderer : public ExplosionEffect3DRendererIF {
public:
	void applyTransforms(const Vector3f& pos, float texDelta, int hasDeltaTex=0) const;
	void discardTransforms(int hasDeltaTex) const;
};


inline void PSPExplosionEffect3DRenderer::applyTransforms(const Vector3f& pos, float texDelta, int hasDeltaTex) const{
	ScePspFVector3 p=pos.getPSPVector();
	ScePspFVector3 s;
	s.x=texDelta; s.y=texDelta; s.z=texDelta;

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
		sceGumScale(&s);

	/*if (hasDeltaTex){
		glMatrixMode(GL_TEXTURE);
		glPushMatrix();
		glTranslatef(texDelta,0,0);
	}
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
		
	glTranslatef(pos.x(),pos.y(),0);
	glScalef(texDelta,texDelta,texDelta);
	*/	

}

inline void PSPExplosionEffect3DRenderer::discardTransforms(int hasDeltaTex) const{
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
