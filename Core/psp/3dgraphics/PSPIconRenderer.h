#ifdef _3D
#ifdef _SPSP

#include "../../3dgraphics/IconRendererIF.h"

#include <libgu.h>
#include <libgum.h>

class PSPIconRenderer:public IconRendererIF{
public:
	void setNextIconDisplacement(float d) const;
	void enableRendering(const Vector3f& centre, float angle=0.0f, const Vector3f& axis=Vector3f(0,0,1)) const;
	void disableRendering() const;
};


inline void PSPIconRenderer::setNextIconDisplacement(float d) const{
	ScePspFVector3 v;
	v.x=d; v.y=0; v.z=0;
	sceGumTranslate(&v);
	//glTranslatef(d,0,0);
}

inline void PSPIconRenderer::enableRendering(const Vector3f& centre, float angle, const Vector3f& axis) const{

	//glDisable(GL_DEPTH_TEST);
	//glPushMatrix();
	//	glTranslatef(centre.x(),centre.y(),centre.z());
	//	glRotatef(angle,axis.x(),axis.y(),axis.z());


	//ScePspFVector3 c; 
	//c.x=centre.x(); c.y=centre.y(); c.z=centre.z();
	ScePspFVector3 c=centre.getPSPVector();
	//printf("place icon at (%f,%f,%f) \n",c.x,c.y,c.z);
	//ScePspFVector3 a=axis.getPSPVector();

	sceGuDisable(SCEGU_DEPTH_TEST);
	sceGumPushMatrix();
		sceGumTranslate(&c);
		sceGumRotateZ(angle*DegRad);
}

inline void PSPIconRenderer::disableRendering() const{
	sceGumPopMatrix();
	sceGuEnable(SCEGU_DEPTH_TEST);
	//sceGuDisable(SCEGU_BLEND);
	
	//glPopMatrix();
	//glEnable(GL_DEPTH_TEST);
}


#endif
#endif