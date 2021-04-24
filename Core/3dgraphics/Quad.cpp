#include "Quad.h"
#ifdef _3D

#include "foundation/PSPHeap.h"

Quad::Quad():m_pVertices(NULL),
			m_pTexCoords(NULL),
			m_pNormals(NULL),
			m_pIndices(NULL),
			m_numVertices(0)
{}

Quad::~Quad(){
	delete [] m_pVertices;
	delete [] m_pNormals;
	delete [] m_pTexCoords;
	delete [] m_pIndices;
}

bool Quad::create(float width, float height, const Vector3f& u, const Vector3f& v){
	//m_centre=centre;
	m_width2=width/2.0f;
	m_height2=height/2.0f;

	m_numVertices=4;
	int size=3*m_numVertices;
	
	m_pVertices=new float[size];
	m_pNormals=new float[size];
	m_pTexCoords=new float[2*m_numVertices];
	m_pIndices=new unsigned int[4];


	//setup vertex arrays
	Vector3f vertex;
	Vector3f normal=u.Cross(v);
	normal.Normalise();

	//vertex=centre-u*m_width2-v*m_height2;
	vertex=-u*m_width2-v*m_height2;
	memcpy(m_pVertices,vertex.GetArray(),3*sizeof(float));
	memcpy(m_pNormals,normal.GetArray(),3*sizeof(float));
	m_pTexCoords[0]=0; m_pTexCoords[1]=0;

	//vertex=centre+u*m_width2-v*m_height2;
	vertex=u*m_width2-v*m_height2;
	memcpy(m_pVertices+3,vertex.GetArray(),3*sizeof(float));
	memcpy(m_pNormals+3,normal.GetArray(),3*sizeof(float));
	m_pTexCoords[2]=1; m_pTexCoords[3]=0;

	//vertex=centre+u*m_width2+v*m_height2;
	vertex=u*m_width2+v*m_height2;
	memcpy(m_pVertices+6,vertex.GetArray(),3*sizeof(float));
	memcpy(m_pNormals+6,normal.GetArray(),3*sizeof(float));
	m_pTexCoords[4]=1; m_pTexCoords[5]=1;

	//vertex=centre-u*m_width2+v*m_height2;
	vertex=-u*m_width2+v*m_height2;
	memcpy(m_pVertices+9,vertex.GetArray(),3*sizeof(float));
	memcpy(m_pNormals+9,normal.GetArray(),3*sizeof(float));
	m_pTexCoords[6]=0; m_pTexCoords[7]=1;

	m_pIndices[0]=0;
	m_pIndices[1]=1;
	m_pIndices[2]=2;
	m_pIndices[3]=3;
	m_topology=QUADS;

	return true;
}

void Quad::renderGeometry() const{
	//m_positioner.adjustTransforms();
	m_vaObject.enableDrawingState(m_pVertices,m_pNormals,m_pTexCoords);
	m_vaObject.render(m_pIndices,m_numVertices,0,m_topology);
	m_vaObject.disableDrawingState();
}

#endif