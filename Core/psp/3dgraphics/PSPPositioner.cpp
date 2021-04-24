#include "PSPPositioner.h"

#ifdef _3D
#ifdef _SPSP

#include <libgu.h>
#include <libgum.h>
#include "../../foundation/MathCon.h"

void PSPPositioner::applyTransforms(const Vector2f& position2D, float angleRot) const{
	
	ScePspFVector3 v;
	v.x=position2D.x;
	v.y=position2D.y;
	v.z=0;

	sceGumPushMatrix();
		sceGumTranslate(&v);
		sceGumRotateZ(angleRot*DegRad);
	
	//glPushMatrix();
	//glTranslatef(position2D.x,position2D.y,0);
	//glRotatef(angleRot,0,0,1);

}

void PSPPositioner::resetTransforms() const{
	sceGumPopMatrix();
	//glPopMatrix();

}


#endif
#endif