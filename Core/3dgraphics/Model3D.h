#pragma once

//class that creates a 3D model;

//USAGE:
//
//loading:
//
//the loader is made for any GFXObjects by the GFXObject3DLoader,
//according to the ConfigItem it receives.
//If the item holds information that is telling the GFXLoader is a 3D model
//the GFXObjectIF* returned will be a reference to a Model3D.
//the loading code that could be called by the game:
//
//			GFXObjectIF *pGFXObject;
//			GFXObject3DLoader loader;
//			pGFXObject=loader.load(ConfigItem);
//			...
//			pGFXObject->render(Vector2f(2.0f,0.0f),40.0f);


#ifdef _3D

//#include "GFXObject3D.h"
#include "Shape3D.h"
#include "VBOObject.h"

#include "foundation/Vector3f.h"
#include <vector>
#include <map>

class Model3D : public Shape3D{
private:
	VBOObject m_vboObj;
	Vector3f m_centre;

public:

	void renderGeometry() const;

	Model3D(){}

	~Model3D();

	//models will always be centred in the origin
	//const Vector3f& getPivot() const{ return m_centre; };

	//setters for filling vboObject
	//these setters should be used by the Model3DLoader only
	void setVertexBuffer(float* pVerticesData, unsigned int numVertices, unsigned int vertexSize);
	void setIndexBuffer(unsigned int* pIndicesData, unsigned int numIndices, int drawingMode, unsigned int count=0);
	void setNormalsBuffer(float *pNormalsData, unsigned int numNormals);
	void setTextureCoordsBuffer(float *pTextureCoordsData, unsigned int numElements, unsigned int numCoords);
	void setNormalsDisplayBuffer(float *pNormDispData, unsigned int numVertices, unsigned int vertexComponents=3);
	
};



#endif