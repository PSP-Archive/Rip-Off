#include "PSPVAObject.h"

#ifdef _3D
#ifdef _SPSP



//to be declared on each platform in the same order
int PSPVAObject::topMappings[3]={SCEGU_PRIM_TRIANGLES, SCEGU_PRIM_TRIANGLE_STRIP, SCEGU_PRIM_RECTANGLES};

PSPVAObject::PSPVAObject():m_flags(SCEGU_VERTEX_FLOAT)
{}


//not used in PSP version because the differences of fvf arrays
void PSPVAObject::render(unsigned int* pIndices, int numElements, int startElement, Topology topology) const{	
	sceGuDisable(SCEGU_CULL_FACE);
	if (m_pVertices)
	sceGumDrawArray(SCEGU_PRIM_TRIANGLE_STRIP, SCEGU_VERTEX_FLOAT,4,0,m_pVertices);
}



#endif
#endif