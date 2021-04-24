#pragma once

//vertex array object
//it is a class that draws some given vertices arrays
//on the screen; 
//It must be extended for each platform


//USAGE:
//	during the render loop call the following methods:
//	enableDrawingState(vertex_array, normals_array, texCoords_array)
//	render(index_array, numElements, startIndex, (one of TRIANGLES, TRIANGLE_STRIP, QUADS))
//

#ifdef _3D

enum Topology{
	TRIANGLES=0,
	TRIANGLE_STRIP=1,
	QUADS=2
};

//------------------------------------------------------------------
//needed if the drawing calls refer to an array of structures of a certain vertex format
//(i.e. psp needs this for drawArrays, OpenGl does not etc)
enum VertexFormatFlags{
	VFF_VERTEX3=1,
	VFF_TEX2=2,
	VFF_NORMAL3=4,
	VFF_INDEX_USHORT=8,
	VFF_UNKNOWN=16
};
//------------------------------------------------------------------


class VAObjectIF{

public:

	
	//enables vertex/normals/textures pointers, and enables clientState
	virtual void enableDrawingState(float *pVertices, float* pNormals, float* pTexCoords) const=0;
	virtual void disableDrawingState() const=0;

	//enables vertex/normals/textures pointers, and enables clientState
	virtual void enableDrawingStateNoNormals(float *pVertices, float* pTexCoords) const=0;
	virtual void disableDrawingStateNoNormals() const=0;


	//draws the elements using the index array
	//input:
	//		pIndices  = the index array, must be unsigned int*
	//		numElements = the number of elements we have to draw from the index array
	//		startElement = from which index to start drawing
	//		topology = how to connect the vertices (in OpenGL would be GL_TRIANGLES, GL_TRIANGLE_STRIP etc)
	virtual void render(unsigned int* pIndices, int numElements, int startElement, Topology topology=TRIANGLES) const=0;


	virtual void render(float *pVertexFormatArray, unsigned short* pIndices, int numElements, int startElement, Topology topology=TRIANGLES) const=0;
	virtual void setFlags(int flags)=0;


};

#endif