#pragma once
#ifdef _3D

#include "foundation/Vector3f.h"
#include "Material.h"
#include "VAObject.h"
#include "IconRenderer.h"



//creates a quad in xOy plane.
//it differs from the quad by the fact it is roteted to be perpendicular on the camera,
//and it has its own material
//it creates 4 vertices stored in the following way:
//
//	^ Oy
//	|
//	|	3____2
//	|	|	 |
//	|	0____1
//	|______________> Ox

class Icon3D{

public:
	Icon3D();
	~Icon3D();

	Icon3D(const Icon3D& rhs);
	Icon3D& operator = (const Icon3D& rhs);

	
	

	//------------------------------------------------------------------

	bool create(const Vector3f& u, const Vector3f& v, int flags);

	void renderGeometry(const Vector3f& centre, float angle=0.0f) const;
	//void renderNonAligned(const Vector3f& centre, float rotAngle) const;

	void setWidth2(float width2);
	void setHeight2(float height2);
	void setMaterial(Material* pMat);
	void setTextureCoordinates(float* texCoords);
	void setNextIconDisplacement(float d) const;
	void grow(float delta, float maxWidth, float maxHeight);

	void resetMesh(const Vector3f& u, const Vector3f& v) const;
	
	//resets the icon including the texture coordinates
	void resetMesh() const;
	
	//resets only the vertices of the icon; the icon will keep the old texture coordinates
	void resetMeshNoTexCoords() const;


private:
	float m_width2, m_height2;				//half of width, height
	
	VAObject m_vaObject;
	mutable float *m_pVertices;		//can be reseted during draw time
	mutable float *m_pNormals;		//can be reseted during draw time
	mutable float *m_pVertexTexNormals;		//contains an array of vertices with the format vx,vy,vz,tx,ty
	mutable char m_dispList[48] __attribute__((aligned(64)));
	VertexFormatFlags	m_flags;
	int m_vertexSize;				//3+2+3 maximum, from vertex+texture+normals according to the flags

	float *m_pTexCoords;


	
	unsigned int *m_pIndices;

	int m_numVertices;
	Topology m_topology;

	Material *m_pMaterial;

	IconRenderer m_renderer;

	

};


inline Icon3D::Icon3D():m_pVertices(NULL),
						m_pTexCoords(NULL),
						m_pNormals(NULL),
						m_pIndices(NULL),
						m_pVertexTexNormals(NULL),
						m_flags(VFF_VERTEX3),
						m_vertexSize(3),
						m_numVertices(0),
						m_width2(0.2),
						m_height2(0.2)
{}

inline	Icon3D::~Icon3D(){
	delete [] m_pVertices;
	delete [] m_pNormals;
	delete [] m_pTexCoords;
	delete [] m_pIndices;
	delete [] m_pVertexTexNormals;
}

inline void Icon3D::setNextIconDisplacement(float d) const{
	m_renderer.setNextIconDisplacement(d);
}

inline void Icon3D::setMaterial(Material* pMat){
	m_pMaterial=pMat;
}

inline void Icon3D::setWidth2(float width2){
	m_width2=width2;
}
inline void Icon3D::setHeight2(float height2){
	m_height2=height2;
}

/*inline void Icon3D::resetMesh(const Vector3f& u, const Vector3f& v) const{
	
	printf("right=(%f,%f,%f)\n",u.x(),u.y(),u.z());
	printf("vup=(%f,%f,%f)\n",v.x(),v.y(),v.z());

	Vector3f vertex;
	Vector3f normal=u.Cross(v);
	normal.Normalise();

	//vertex=centre-u*m_width2-v*m_height2;
	

	vertex=-u*m_width2+v*m_height2;
	memcpy(m_pVertices,vertex.GetArray(),3*sizeof(float));
	memcpy(m_pNormals,normal.GetArray(),3*sizeof(float));

	vertex=-u*m_width2-v*m_height2;
	memcpy(m_pVertices+3,vertex.GetArray(),3*sizeof(float));
	memcpy(m_pNormals+3,normal.GetArray(),3*sizeof(float));

	vertex=u*m_width2+v*m_height2;
	memcpy(m_pVertices+6,vertex.GetArray(),3*sizeof(float));
	memcpy(m_pNormals+6,normal.GetArray(),3*sizeof(float));

	vertex=u*m_width2-v*m_height2;
	memcpy(m_pVertices+9,vertex.GetArray(),3*sizeof(float));
	memcpy(m_pNormals+9,normal.GetArray(),3*sizeof(float));


	//if the camera is perpendicular to the game scene, we have
	//u=(1,0,0)
	//v=(0,1,0)
	//s


	/vertex=-u*m_width2-v*m_height2;
	memcpy(m_pVertices,vertex.GetArray(),3*sizeof(float));
	memcpy(m_pNormals,normal.GetArray(),3*sizeof(float));

	vertex=u*m_width2-v*m_height2;
	memcpy(m_pVertices+3,vertex.GetArray(),3*sizeof(float));
	memcpy(m_pNormals+3,normal.GetArray(),3*sizeof(float));

	vertex=u*m_width2+v*m_height2;
	memcpy(m_pVertices+6,vertex.GetArray(),3*sizeof(float));
	memcpy(m_pNormals+6,normal.GetArray(),3*sizeof(float));

	vertex=-u*m_width2+v*m_height2;
	memcpy(m_pVertices+9,vertex.GetArray(),3*sizeof(float));
	memcpy(m_pNormals+9,normal.GetArray(),3*sizeof(float));
	/
}*/

inline void Icon3D::grow(float delta, float maxWidth2, float maxHeight2){
	if (m_width2<maxWidth2) m_width2+=delta;
	if (m_height2<maxHeight2) m_height2+=delta;
}

/*
inline void Icon3D::setTextureCoordinates(float *texCoords){
	if (m_flags&VFF_UNKNOWN){
		if (m_pTexCoords && texCoords)
			memcpy(m_pTexCoords,texCoords,8*sizeof(float));
	}else if (m_pVertexTexNormals && texCoords && (m_flags&VFF_TEX2)){
		
		int offsetDest=0, offsetSrc=0; 
		for (int i=0;i<4;i++){
			memcpy(m_pVertexTexNormals+offsetDest,texCoords+offsetSrc,2*sizeof(float));
			offsetDest+=m_vertexSize;
			offsetSrc+=2;
		}
	}

}*/

#endif