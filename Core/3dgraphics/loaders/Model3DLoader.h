#pragma once

//
//Class used to load a 3D Model from a file.
//The load method receives a fileName and tries to load it.
//
//!!!!!
//
//NOTE:
//the loader is not using foundation/File.h fully, it still
//has some streaming. If streaming will not be compatible with other platforms
//this file must be changed!
//
//!!!!!
//
 
#ifdef _3D

#include "../Model3D.h"
#include "../Material.h"

class Model3DLoader{
private:

	typedef struct Vertex{
		Vector3f vertex;
		Vector3f normal;
		float u,v;
		bool assigned;
	} ModelVertex;
	vector<Vertex> m_vertices;
	vector<Vector3f> m_normals;
	vector<float> m_texCoords;
	vector<unsigned int> m_indices;
	string m_matLibName, m_fileName, m_localFolder;
	vector<string> m_matNames;
	
	char m_lineBuffer[100];
	int m_lengthOfLine;

	int m_topology;														//GL_POINTS, GL_LINES, GL_TRIANGLES, GL_POLYGONS
	
private:
	void parseVertex(const char* lineBuffer, int length);
	void parseNormal(const char* lineBuffer, int length);
	void parseTexture(const char* lineBuffer, int length);
	void parseFace(const char* lineBuffer, int length);

	string getTitle(const char* lineBuffer, int length);
	Material* parseMaterialLib(const string &fileName, const string& folder);
	Material* parseMaterialBlock(ifstream& fin, const string& folder);

	string computeFolder(const string& fileName);

	Material* parseOnlyForMatlib(const string& fileName);
public:
	Model3D* load(const string& fileName, float radius, Material** ppMaterial);
};

#endif