#pragma once

#ifdef _3D
#ifdef _SPSP

#include "../../3dgraphics/VAObjectIF.h"

#include <libgu.h>
#include <libgum.h>

class PSPVAObject:public VAObjectIF{
public:

	PSPVAObject();

	void enableDrawingState(float *pVertices, float* pNormals, float* pTexCoords) const;
	void disableDrawingState() const;

	void enableDrawingStateNoNormals(float *pVertices, float* pTexCoords) const;
	void disableDrawingStateNoNormals() const;

	void render(unsigned int* pIndices, int numElements, int startElement, Topology topology) const;

	void render(float *pVertexFormatArray, unsigned short* pIndices, int numElements, int startElement, Topology topology=TRIANGLES) const;
	void setFlags(int flags);

private:
	static int topMappings[3];
	mutable float *m_pVertices;			//hack; copy the pointer in enable drawing state
								//to use it in draw state; the openGL-like interface
								//does not provide the vertex array in draw, it does so
								//only in enable drawing state
	mutable int m_flags;		//SCEGU_TEXTURE_FLOAT or SCEGU_NORMAL_FLOAT or SCEGU_VERTEX_FLOAT or SCEGU_INDEX_USHORT
								// or a combination of those
								//must be set in enable state;

};


inline void PSPVAObject::render(float *pVertexFormatArray, unsigned short* pIndices, int numElements, int startElement, Topology topology) const{
	//prim ,type, count, idx, vtx
	sceGumDrawArray(topMappings[topology], m_flags,numElements,pIndices,pVertexFormatArray);
}

inline void PSPVAObject::setFlags(int flags){
	if (flags&VFF_TEX2)    m_flags|=SCEGU_TEXTURE_FLOAT;
	if (flags&VFF_NORMAL3) m_flags|=SCEGU_NORMAL_FLOAT;
	if (flags&VFF_VERTEX3) m_flags|=SCEGU_VERTEX_FLOAT;
	if (flags&VFF_INDEX_USHORT) m_flags|=SCEGU_INDEX_USHORT;
	
}
	

inline void PSPVAObject::enableDrawingState(float *pVertices, float* pNormals, float* pTexCoords) const{
	m_pVertices=pVertices;		//copy the pointer!!!
	m_flags=SCEGU_TEXTURE_FLOAT|SCEGU_NORMAL_FLOAT|SCEGU_VERTEX_FLOAT;
}

inline void PSPVAObject::enableDrawingStateNoNormals(float *pVertices, float* pTexCoords) const{
	m_flags=SCEGU_TEXTURE_FLOAT|SCEGU_VERTEX_FLOAT;
	m_pVertices=pVertices;
}

inline void PSPVAObject::disableDrawingState() const{
	m_pVertices=0;
}

inline void PSPVAObject::disableDrawingStateNoNormals() const{
	m_pVertices=0;
}


#endif
#endif