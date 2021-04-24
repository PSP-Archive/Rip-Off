#pragma once

#ifdef _3D

//#include "GFXObject3D.h"
#include "Shape3D.h"
#include "VBOObject.h"
#include "SphereRenderer.h"


class Sphere: public Shape3D{
private:
	unsigned int m_stacks, m_slices;

	SphereRenderer m_renderer;

	float m_radius;	

	VBOObject m_vbObject;
	
public:

	Sphere();

	void setTesselation(unsigned int stacks, unsigned int slices);

	bool create();

	void renderGeometry() const;

	//const Vector3f& getPivot() const{ return m_centre; }


	void setRadius(float radius);
	//void setCentre(const Vector3f& centre);
	void setSlices(int slices);
	void setStacks(int stacks);
	
};

#endif
