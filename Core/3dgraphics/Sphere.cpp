#ifdef _3D

#include "Sphere.h"

#include "foundation/MathCon.h"
#include "foundation/PSPHeap.h"
#include <cmath>

Sphere::Sphere():m_radius(1),
				m_stacks(10),
				m_slices(10)
{}

void Sphere::setTesselation(unsigned int stacks, unsigned int slices){
	m_stacks=stacks;
	m_slices=slices;
}

void Sphere::setRadius(float radius){
	m_radius=radius;
}

void Sphere::setSlices(int slices){
	m_slices=slices;
}
void Sphere::setStacks(int stacks){
	m_stacks=stacks;
}

bool Sphere::create(){
	unsigned int numVertices;
	float stackInc,sliceInc,x,y,z,tempTex,tempRad;
	int vertexCount;

	float *pVerticesData, *pNormalsData, *pTextureData, *pNormDispData;
	float *pv, *pn, *pt, *tempPv, *tempPn, *pnd;		//pointers to go through the allocated data
	unsigned int *pIndicesData;
	unsigned int *pi;

	if ((m_stacks < 2) & (m_slices <2)) return false;

	numVertices = (m_slices+1)*(m_stacks-1)+2;			// +2 is for the top and bottom vertex

	pVerticesData=new float[3*numVertices];
	pNormDispData=new float[2*3*numVertices];
	pNormalsData=new float[3*numVertices];
	pIndicesData=new unsigned int [2+(m_stacks-1)*(m_slices+1)*2];
	pTextureData=new float[2*numVertices];


	stackInc = 1.0f/(float)m_stacks;
	sliceInc = (float)PI*2.0f/m_slices;

	pv=pVerticesData; pn=pNormalsData; pt=pTextureData; pnd=pNormDispData;
	// top point
	*pv=0.0f; pv++; *pv=m_radius;	pv++; *pv=0.0f;	pv++;
	*pn=0.0f; pn++; *pn=1.0f;   pn++; *pn=0.0f; pn++;
	*pt=0.0f; pt++; *pt=1.0f;   pt++;
	*pnd=0.0f; pnd++; *pnd=m_radius;	pnd++; *pnd=0.0f;	pnd++;
	*pnd=0.0f; pnd++; *pnd=m_radius+1.0f;	pnd++; *pnd=0.0f;	pnd++;
	

	// bottom point
	*pv=0.0f; pv++; *pv=-m_radius; pv++; *pv=0.0f; pv++;
	*pn=0.0f; pn++; *pn=-1.0f;   pn++; *pn=0.0f; pn++;
	*pt=0.0f; pt++; *pt=0.0f;    pt++;
	*pnd=0.0f; pnd++; *pnd=-m_radius;	pnd++; *pnd=0.0f;	pnd++;
	*pnd=0.0f; pnd++; *pnd=-m_radius-1.0f;	pnd++; *pnd=0.0f;	pnd++;
	

	for (unsigned int i = 1; i < m_stacks; i++) {
		y = sinf((float)PI*(0.5f - stackInc*(float)i));
		tempRad = cosf((float)PI*(0.5f - stackInc*(float)i));
		tempPv=pv; tempPn=pn;
		//tempVc = vertex_count;
		tempTex = 1.0f - stackInc*(float)i;
		for(unsigned int j = 0; j < m_slices; j++) {
			x = cosf((float)j*sliceInc); 
			z = -sinf((float)j*sliceInc);
			
			*pv=m_radius*tempRad*x; pv++;
			*pv=m_radius*y;		  pv++;
			*pv=m_radius*tempRad*z; pv++;
			
			*pn=tempRad*x;   pn++;
			*pn=y;		     pn++;
			*pn=tempRad*z;   pn++;

			*pnd=(*(pv-3)); pnd++;
			*pnd=(*(pv-2)); pnd++;
			*pnd=(*(pv-1)); pnd++;

			*pnd=(*(pv-3))+(*(pn-3)); pnd++;
			*pnd=(*(pv-2))+(*(pn-2)); pnd++;
			*pnd=(*(pv-1))+(*(pn-1)); pnd++;

			*pt=(float)j/(float)m_slices; pt++;			//beta/2 PI
			*pt=tempTex; pt++;
			
		};

		memcpy(pv,tempPv,3*sizeof(float)); pv+=3;
		memcpy(pn,tempPn,3*sizeof(float)); pn+=3;

		*pnd=(*(pv-3)); pnd++;
		*pnd=(*(pv-2)); pnd++;
		*pnd=(*(pv-1)); pnd++;

		*pnd=(*(pv-3))+(*(pn-3)); pnd++;
		*pnd=(*(pv-2))+(*(pn-2)); pnd++;
		*pnd=(*(pv-1))+(*(pn-1)); pnd++;

		*pt=1.0f; pt++;			//beta/2 PI
		*pt=tempTex; pt++;
	};

	// now generate the index array
	// start with triangle fans for the top
	vertexCount=2;
	pi=pIndicesData;
	*pi=0; pi++;
	for(unsigned int j = 0; j<= m_slices; j++) {
		*pi=vertexCount++; pi++;
	}
	vertexCount -= (m_slices+1);

	// now do the main strips
	for(unsigned int i = 0; i< (m_stacks-2); i++) {
		for(unsigned int j = 0; j<= m_slices; j++) {
			*pi=vertexCount++; pi++;
			*pi=m_slices+vertexCount; pi++;
		}
	}
	*pi=1; pi++;	// very bottom vertex
	for(unsigned int j = 0; j<= m_slices; j++) {
		*pi=vertexCount+m_slices-j; pi++;
	}

	//----------------------------------------------------------
	//m_vbObject.load();
	m_vbObject.setVertexBuffer(pVerticesData,numVertices,3);
	delete [] pVerticesData;
	
	m_vbObject.setNormalsBuffer(pNormalsData,numVertices);
	delete [] pNormalsData;

	m_vbObject.setTextureCoordsBuffer(pTextureData,numVertices,2);
	delete [] pTextureData;

#ifdef _PC
	m_vbObject.setIndexBuffer(pIndicesData,(2+(m_stacks-1)*(m_slices+1)*2),GL_TRIANGLE_STRIP);
	delete [] pIndicesData;
#endif

	m_vbObject.setNormalsDisplayBuffer(pNormDispData,numVertices);
	delete [] pNormDispData;
	
	return true;
}


void Sphere::renderGeometry() const {

	m_vbObject.enableDrawingState();
	m_renderer.drawCore(m_stacks, m_slices);
	m_vbObject.disableDrawingState();
	
	//debug normals
	//m_vbObject.disableDrawingStateNormals(bDrawNormals);
	
}


#endif