#include "PSPVBOObject.h"

#ifdef _3D
#ifdef _SPSP

PSPVBOObject::PSPVBOObject(){
	//PCGlex::get()->load();
}

PSPVBOObject::~PSPVBOObject(){
	/*if (m_vertexBuffer){
		PCGlex::get()->deleteBuffersARB(1,&m_vertexBuffer);
	}
	if (m_indexBuffer){
		PCGlex::get()->deleteBuffersARB(1,&m_indexBuffer);
	}
	if (m_normalBuffer){
		PCGlex::get()->deleteBuffersARB(1,&m_normalBuffer);
	}
	if (m_textureBuffer){
		PCGlex::get()->deleteBuffersARB(1,&m_textureBuffer);
	}
	if (m_normDispBuffer){
		PCGlex::get()->deleteBuffersARB(1,&m_normDispBuffer);
	}*/
}

void PSPVBOObject::setVertexBuffer(float* pVerticesData, unsigned int numVertices, unsigned int vertexSize){
	/*m_numVertices=numVertices;

	PCGlex::get()->genBuffersARB( 1, &m_vertexBuffer);
	PCGlex::get()->bindBufferARB( GL_ARRAY_BUFFER_ARB, m_vertexBuffer);
	PCGlex::get()->bufferDataARB( GL_ARRAY_BUFFER_ARB, vertexSize*numVertices*sizeof(float), pVerticesData, GL_STATIC_DRAW_ARB );
	PCGlex::get()->bindBufferARB( GL_ARRAY_BUFFER_ARB, 0);
	*/
}

void PSPVBOObject::setIndexBuffer(unsigned int* pIndicesData, unsigned int numIndices, int drawingMode, unsigned int count){
	/*m_drawingMode=drawingMode;
	if (count) m_count=count;
	else m_count=numIndices;
	PCGlex::get()->genBuffersARB( 1, &m_indexBuffer);
	PCGlex::get()->bindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, m_indexBuffer);
	PCGlex::get()->bufferDataARB( GL_ELEMENT_ARRAY_BUFFER_ARB, numIndices*sizeof(unsigned int), pIndicesData, GL_STATIC_DRAW_ARB );
	PCGlex::get()->bindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
	*/
}

void PSPVBOObject::setNormalsBuffer(float *pNormalsData, unsigned int numNormals){
	/*
	PCGlex::get()->genBuffersARB( 1, &m_normalBuffer);
	PCGlex::get()->bindBufferARB( GL_ARRAY_BUFFER_ARB, m_normalBuffer);
	PCGlex::get()->bufferDataARB( GL_ARRAY_BUFFER_ARB, 3*numNormals*sizeof(float), pNormalsData, GL_STATIC_DRAW_ARB );
	PCGlex::get()->bindBufferARB( GL_ARRAY_BUFFER_ARB, 0);
	*/
}

void PSPVBOObject::setTextureCoordsBuffer(float *pTextureCoordsData, unsigned int numVertices, unsigned int numCoords){
	/*
	PCGlex::get()->genBuffersARB( 1, &m_textureBuffer);
	PCGlex::get()->bindBufferARB( GL_ARRAY_BUFFER_ARB, m_textureBuffer);
	PCGlex::get()->bufferDataARB( GL_ARRAY_BUFFER_ARB, numCoords*numVertices*sizeof(float), pTextureCoordsData, GL_STATIC_DRAW_ARB );
	PCGlex::get()->bindBufferARB( GL_ARRAY_BUFFER_ARB, 0);
	*/
}

void PSPVBOObject::setNormalsDisplayBuffer(float *pNormDispData, unsigned int numVertices, unsigned int vertexComponents){
	/*
	PCGlex::get()->genBuffersARB( 1, &m_normDispBuffer);
	PCGlex::get()->bindBufferARB( GL_ARRAY_BUFFER_ARB, m_normDispBuffer);
	PCGlex::get()->bufferDataARB( GL_ARRAY_BUFFER_ARB, 2*vertexComponents*numVertices*sizeof(float), pNormDispData, GL_STATIC_DRAW_ARB );
	PCGlex::get()->bindBufferARB( GL_ARRAY_BUFFER_ARB, 0);
	*/
}


void PSPVBOObject::enableDrawingState() const{
	/*
	glEnableClientState( GL_VERTEX_ARRAY );		
	PCGlex::get()->bindBufferARB( GL_ARRAY_BUFFER_ARB, m_vertexBuffer);
	glVertexPointer( 3, GL_FLOAT, 0, (char *) NULL );
	
	glEnableClientState( GL_INDEX_ARRAY);
	PCGlex::get()->bindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, m_indexBuffer);
	
	glEnableClientState( GL_NORMAL_ARRAY);
	PCGlex::get()->bindBufferARB( GL_ARRAY_BUFFER_ARB, m_normalBuffer);
	glNormalPointer(GL_FLOAT,0,(char*)NULL);

	glEnableClientState( GL_TEXTURE_COORD_ARRAY );
	PCGlex::get()->bindBufferARB( GL_ARRAY_BUFFER_ARB, m_textureBuffer);
	glTexCoordPointer(2, GL_FLOAT, 0, (char *) NULL );

	*/
}

void PSPVBOObject::disableDrawingState() const{
	/*PCGlex::get()->bindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
	PCGlex::get()->bindBufferARB( GL_ARRAY_BUFFER_ARB, 0);
	
	glDisableClientState( GL_TEXTURE_COORD_ARRAY );
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState( GL_INDEX_ARRAY);
	glDisableClientState( GL_VERTEX_ARRAY );
	*/
}

void PSPVBOObject::disableDrawingStateNormals(bool bDrawNormals) const{
	/*PCGlex::get()->bindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
	PCGlex::get()->bindBufferARB( GL_ARRAY_BUFFER_ARB, 0);
	

 	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState( GL_INDEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	//if (bDrawNormals)
	//drawNormals();
	
	glDisableClientState( GL_VERTEX_ARRAY );
	*/
}

void PSPVBOObject::drawNormals() const{

	/*glDisable(GL_LIGHTING);
	glColor4f(0.0f,1.0f,0.0f,1.0f);
	PCGlex::get()->bindBufferARB( GL_ARRAY_BUFFER_ARB, m_normDispBuffer);
	glVertexPointer( 3, GL_FLOAT, 0, (char *) NULL );
	glDrawArrays(GL_LINES,0,2*m_numVertices);
	PCGlex::get()->bindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, 0);

	glEnable(GL_LIGHTING);
	*/
}

void PSPVBOObject::draw() const{
	
	/*
	enableDrawingState();

	glDrawElements(m_drawingMode,m_count,GL_UNSIGNED_INT,(const GLuint*)NULL);
	
	disableDrawingStateNormals(false);
	*/	

	
}

#endif
#endif