#pragma once
#ifdef _3D

//#include "GFXObject3D.h"
#include "foundation/Vector3f.h"
#include "VAObject.h"
#include "Shape3D.h"


//creates a quad in xOy plane.
//it creates 4 vertices stored in the following way:
//
//	^ Oy
//	|
//	|	3____2
//	|	|	 |
//	|	0____1
//	|______________> Ox

class Quad:public Shape3D{
private:
	float m_width2, m_height2;				//half of width, height
	Vector3f m_centre;
	//Vector3f m_u,m_v;
	
	VAObject m_vaObject;
	float *m_pVertices;
	float *m_pTexCoords;
	float *m_pNormals;
	unsigned int *m_pIndices;

	int m_numVertices;
	Topology m_topology;

	Quad(const Quad& rhs){};
	Quad& operator = (const Quad& rhs){};


public:
	Quad();
	~Quad();
	
	bool create(float width, float height, const Vector3f& u, const Vector3f& v);

	void renderGeometry() const;

	//const Vector3f& getPivot() const{ return m_centre; }
};

#endif