#pragma once

#ifdef _3D
#ifdef _PC

#include "../../3dgraphics/VAObjectIF.h"

#include "GL/glut.h"
#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glut32.lib")


class PCVAObject:public VAObjectIF{
private:
	static int topMappings[3];
public:
	void enableDrawingState(float *pVertices, float* pNormals, float* pTexCoords) const;
	void disableDrawingState() const;

	void enableDrawingStateNoNormals(float *pVertices, float* pTexCoords) const;
	void disableDrawingStateNoNormals() const;

	void render(unsigned int* pIndices, int numElements, int startElement, Topology topology) const;
};

inline void PCVAObject::render(unsigned int* pIndices, int numElements, int startElement, Topology topology) const{
	glDrawElements(topMappings[topology], numElements, GL_UNSIGNED_INT,&pIndices[startElement]);
}

inline void PCVAObject::enableDrawingState(float *pVertices, float* pNormals, float* pTexCoords) const{
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, pTexCoords);

	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 0, pNormals);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, pVertices);
}

inline void PCVAObject::disableDrawingState() const{
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

inline void PCVAObject::enableDrawingStateNoNormals(float *pVertices, float* pTexCoords) const{
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, pTexCoords);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, pVertices);
}

inline void PCVAObject::disableDrawingStateNoNormals() const{
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

#endif
#endif