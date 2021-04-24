#pragma once

#ifdef _3D
#ifdef _PC

#include "../../3dgraphics/MaterialRendererIF.h"

#include "GL/glut.h"
#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glut32.lib")

class PCMaterialRenderer:public MaterialRendererIF{
public:
	void applyNoLighting(const Vector4f& color) const;

	void apply(const Vector4f& ambient, 
					   const Vector4f& diffuse,
					   const Vector4f& specular,
					   const Vector4f& emissive,
					   float shininess) const;

	void dismiss() const;
	void dismissNoLighting() const;

};

inline void PCMaterialRenderer::apply(const Vector4f& ambient, 
									   const Vector4f& diffuse,
									   const Vector4f& specular,
									   const Vector4f& emissive,
									   float shininess) const
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient.GetArray());
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse.GetArray());
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular.GetArray());
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emissive.GetArray());
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,&shininess);
	
}

inline void PCMaterialRenderer::applyNoLighting(const Vector4f& color) const{
	glDisable(GL_LIGHTING);		//by default lighting is on, if we don't use it we switch it off
	glColor4fv(color.GetArray());
}

inline void PCMaterialRenderer::dismiss() const{
	float black[4]={0.0f,0.0f,0.0f,0.0f};
	float shininess=0;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, black);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, black);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, black);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,&shininess);
}

inline void PCMaterialRenderer::dismissNoLighting() const{
	float black[4]={0.0f,0.0f,0.0f,0.0f};
	glColor4fv(black);
	glEnable(GL_LIGHTING);		//reset lighting to default (on)
}

#endif
#endif