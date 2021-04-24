#pragma once

//class that contains geometry info, stored in vertex buffers
//
//3D objects will use it during creation, to store their arrays in the buffers,
//and during rendering, by calling draw()


#ifdef _3D

class VBOObjectIF{

private:
	VBOObjectIF(const VBOObjectIF& rhs){}
	VBOObjectIF& operator = (const VBOObjectIF& rhs){return *this;}

protected:
	
	unsigned int m_vertexBuffer, m_indexBuffer, m_normalBuffer, m_textureBuffer, m_normDispBuffer;
	int m_drawingMode;								//used for the index buffer, can take values like GL_TRIANGLES, GL_TRIANGLE_STRIP, etc;
	unsigned int m_count,m_numVertices;

public:
	
	VBOObjectIF();
	virtual ~VBOObjectIF();


	//sets the vertex buffer, filling it whith the contents of pData;
	//it doesn't free the memory of pVerticesData, the user(derived class) is responsible with
	//cleaning CPU resources
	void setVertexBuffer(float* pVerticesData, unsigned int numVertices, unsigned int vertexSize);

	//sets the index buffer, filling it whith the contents of pIndicesData;
	//it doesn't free the memory of pIndicesData, the user(derived class) is responsible with
	//cleaning CPU resources
	//drawing mode can be GL_TRIANGLES, GL_TRIANGLE_STRIP
	void setIndexBuffer(unsigned int* pIndicesData, unsigned int numIndices, int drawingMode, unsigned int count=0);
	
	//sets the normals' buffer, filling it whith the contents of pNormalsData;
	//it doesn't free the memory of pNormalsData, the user(derived class) is responsible with
	//cleaning CPU resources
	//it assumes a normal is a vector of 3 floats
	void setNormalsBuffer(float *pNormalsData, unsigned int numNormals);

	//sets the texture coords buffer, filling it whith the contents of pTextureCoordsData;
	//it doesn't free the memory of pTextureCoordsData, the user(derived class) is responsible with
	//cleaning CPU resources
	//a vertex will have numCoords texture coordinates (i.e numCoords=2)
	void setTextureCoordsBuffer(float *pTextureCoordsData, unsigned int numElements, unsigned int numCoords);

	void setNormalsDisplayBuffer(float *pNormDispData, unsigned int numVertices, unsigned int vertexComponents=3);

	//Default behaviour: draws all the elements corresponding with the index buffer;
	//if other functionality is desired - i.e rows of triangle strips - the derrived class has
	//to override this function
	void draw() const;

	//Sets the buffers for drawing
	void enableDrawingState() const;

	//Disables all the buffers used for drawing
	void disableDrawingState() const;

	//disables all the buffers used for drawind, but tries to draw normals
	//before disabling vertex pointer; if the normals do not need to be shown,
	//the function DisableDrawingState is faster.
	//by default, the draw function from this class uses DisableDrawingStateNormals,
	//not the faster one.
	void disableDrawingStateNormals(bool bDrawNormals) const;
	
	//draws the object normals only when displayNormals state is true
	void drawNormals() const;

};

#endif