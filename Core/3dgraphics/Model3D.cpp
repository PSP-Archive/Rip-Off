#include "Model3D.h"

#ifdef _3D

#include "Model3D.h"
#include <fstream>
#include <strstream>
#include <cassert>


using namespace std;

Model3D::~Model3D(){
	//delete m_pVboObj;
}


void Model3D::setVertexBuffer(float* pVerticesData, unsigned int numVertices, unsigned int vertexSize){
	m_vboObj.setVertexBuffer(pVerticesData,numVertices,vertexSize);
}

void Model3D::setIndexBuffer(unsigned int* pIndicesData, unsigned int numIndices, int drawingMode, unsigned int count){
	m_vboObj.setIndexBuffer(pIndicesData,numIndices,drawingMode,count);
}

void Model3D::setNormalsBuffer(float *pNormalsData, unsigned int numNormals){
	m_vboObj.setNormalsBuffer(pNormalsData,numNormals);
}

void Model3D::setTextureCoordsBuffer(float *pTextureCoordsData, unsigned int numElements, unsigned int numCoords){
	m_vboObj.setTextureCoordsBuffer(pTextureCoordsData,numElements,numCoords);
}

void Model3D::setNormalsDisplayBuffer(float *pNormDispData, unsigned int numVertices, unsigned int vertexComponents){
	m_vboObj.setNormalsDisplayBuffer(pNormDispData,numVertices,vertexComponents);
}



void Model3D::renderGeometry() const{
	m_vboObj.draw();
}


#endif