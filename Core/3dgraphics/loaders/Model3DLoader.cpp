#ifdef _3D

#include "Model3DLoader.h"

#include <fstream>
#include <strstream>
#include <cassert>
#include "foundation/File.h"
#include "../managers/MeshManager.h"
#include "../managers/MaterialManager.h"
#include "../managers/TextureManager.h"

void Model3DLoader::parseVertex(const char* lineBuffer, int length){
	istrstream streamin (lineBuffer, length);
	Vertex v;
	streamin>>v.vertex[0]>>v.vertex[1]>>v.vertex[2];
	v.assigned=false;
	m_vertices.push_back(v);
}
void Model3DLoader::parseNormal(const char* lineBuffer, int length){
	istrstream streamin (lineBuffer, length);
	Vector3f n;
	streamin>>n[0]>>n[1]>>n[2];
	m_normals.push_back(n);
}
void Model3DLoader::parseTexture(const char* lineBuffer, int length){
	istrstream streamin (lineBuffer, length);
	float u,v;
	streamin>>u>>v;
	m_texCoords.push_back(u);
	m_texCoords.push_back(v);
}

void Model3DLoader::parseFace(const char* lineBuffer, int length){

	istrstream streamin (lineBuffer, length);
	int iv,ivt=0,ivn,i=0;	//i=index, v=vertex, n=normal, t=texcoord
	char ch;
	if (m_texCoords.size()==0){
		while (streamin>>iv>>ch>>ch>>ivn){
			//if (streamin.fail()) throw Exception(ERR_IFSTREAM_ERROR," Parse .obj failed");
			iv--; ivn--;
			i++;
			Vertex* pV=&m_vertices[iv];
			if (pV->assigned ){
				if (pV->normal!=m_normals[ivn] || pV->v!=m_texCoords[2*ivt+1]){
					Vertex newVertex;
					newVertex.vertex=m_vertices[iv].vertex;
					newVertex.normal=m_normals[ivn];
					newVertex.u=0;
					newVertex.v=0;
					newVertex.assigned=true;
					m_vertices.push_back(newVertex);
					assert( (int)(m_vertices.size()-1)>=0);
					m_indices.push_back((unsigned int)(m_vertices.size()-1));
				}else{
					assert(iv>=0);
					m_indices.push_back((unsigned int)iv);
				}
			}else{
				m_vertices[iv].normal=m_normals[ivn];
				m_vertices[iv].u=0;
				m_vertices[iv].v=0;
				m_vertices[iv].assigned=true;
				assert(iv>=0);
				m_indices.push_back((unsigned int)iv);
			}
		}
	}else{
		while (streamin>>iv>>ch>>ivt>>ch>>ivn){
			//if (streamin.fail()) throw Exception(ERR_IFSTREAM_ERROR," Parse .obj failed");
			iv--; ivt--; ivn--;
			i++;
			Vertex* pV=&m_vertices[iv];
			if (pV->assigned ){
				if (pV->normal!=m_normals[ivn] || pV->u!=m_texCoords[2*ivt] || pV->v!=m_texCoords[2*ivt+1]){
					Vertex newVertex;
					newVertex.vertex=m_vertices[iv].vertex;
					newVertex.normal=m_normals[ivn];
					newVertex.u=m_texCoords[2*ivt];
					newVertex.v=m_texCoords[2*ivt+1];
					newVertex.assigned=true;
					m_vertices.push_back(newVertex);
					assert((m_vertices.size()-1)>=0);
					m_indices.push_back((unsigned int)(m_vertices.size()-1));
				}else{
					assert(iv>=0);
					m_indices.push_back((unsigned int)iv);
				}
			}else{
				m_vertices[iv].normal=m_normals[ivn];
				m_vertices[iv].u=m_texCoords[2*ivt];
				m_vertices[iv].v=m_texCoords[2*ivt+1];
				m_vertices[iv].assigned=true;
				assert(iv>=0);
				m_indices.push_back((unsigned int)iv);
			}
		}
	}
	
}


Material* Model3DLoader::parseOnlyForMatlib(const string& fileName){
	File fin;
	if (!fin.open(fileName)){
		//model path not valid
		return NULL;
	}

	//char lineBuffer[100];
	string lineBuffer;
	while (fin.readLine(lineBuffer)){
		int lengthOfLine=lineBuffer.length();
		if (lengthOfLine==0) continue;

		if (!strncmp(lineBuffer.c_str(),"mtllib",6)){
			istrstream streamin (lineBuffer.c_str()+7, lengthOfLine-7);
			streamin>>m_matLibName;
			string folder=computeFolder(m_fileName);
			m_matLibName=folder+m_matLibName;
			continue;
		}
	}

	Material *pMat;
	string folder=computeFolder(fileName);
	pMat=parseMaterialLib(m_matLibName,folder);

	if (!pMat){
		pMat=MaterialManager::get()->hasMaterial("defMaterial");
		if (!pMat){
			pMat=new Material();
			pMat->setName("defMaterial");
			MaterialManager::get()->addMaterial(pMat);
		}
	}
	return pMat;
}

Model3D* Model3DLoader::load(const string& fileName, float radius, Material** ppMaterial){
	
	Model3D *pModel;
	pModel=(Model3D*)MeshManager::get()->hasMesh(fileName);		//returns NULL if pModel not found, the reference to the model
																//otherwise
	if (pModel) {
		//model found in the manager
		*ppMaterial=parseOnlyForMatlib(fileName);
		//pModel->setCentre(centre);
		return pModel;
	}
	

	float *pVerticesData, *pNormalsData, *pTextureCoordsData, *pNormDispData;
	unsigned int *pIndicesData;
	int vertexSize=3, numCoords=2;
	//int matCount=0;

	File fin;
	if (!fin.open(fileName)){
		//model path not valid
		return NULL;
	}

	//char lineBuffer[100];
	string lineBuffer;
	while (fin.readLine(lineBuffer)){
		int lengthOfLine=lineBuffer.length();
		if (lengthOfLine==0) continue;
		//if (strlen(lineBuffer)==0) continue;
		

		if (lineBuffer[0]=='v' && lineBuffer[1]==' '){
			parseVertex(lineBuffer.c_str()+2,lengthOfLine-2);
			continue;
		}
		if (lineBuffer[0]=='v' && lineBuffer[1]=='n'){
			parseNormal(lineBuffer.c_str()+3,lengthOfLine-3);
			continue;
		}
		if (lineBuffer[0]=='v' && lineBuffer[1]=='t'){
			parseTexture(lineBuffer.c_str()+3,lengthOfLine-3);
			continue;
		}
		if (lineBuffer[0]=='f' && lineBuffer[1]==' '){
			parseFace(lineBuffer.c_str()+2,lengthOfLine-2);
			continue;
		}
		if (!strncmp(lineBuffer.c_str(),"usemtl",6)){
			istrstream streamin (lineBuffer.c_str()+7, lengthOfLine-7);
			string mat;
			streamin>>mat;
			m_matNames.push_back(mat);
			continue;
		}
		if (!strncmp(lineBuffer.c_str(),"mtllib",6)){
			istrstream streamin (lineBuffer.c_str()+7, lengthOfLine-7);
			streamin>>m_matLibName;
			string folder=computeFolder(m_fileName);
			m_matLibName=folder+m_matLibName;
			continue;
		}
	
	}

#ifdef _PC
	m_topology=GL_TRIANGLES;
#elif _SPSP
	//m_topology=...
#endif
	//don't need these vectors anymore, the info is stored in m_vertices
	m_normals.clear();
	m_texCoords.clear();

	vector<Vertex>::iterator it=m_vertices.begin();
	
	unsigned int numVertices=m_vertices.size();
	pVerticesData=new float[3*numVertices];
	pNormalsData=new float[3*numVertices];
	pTextureCoordsData=new float[2*m_vertices.size()];
	pNormDispData=new float[6*numVertices];
	float *pv=pVerticesData, *pn=pNormalsData, *pt=pTextureCoordsData, *pnd=pNormDispData;
	
	float R=0;		//compute its bounding circle in xOy plane

	for (;it!=m_vertices.end();it++){
		Vertex v=(*it);
		float r=v.vertex[0]*v.vertex[0]+v.vertex[1]*v.vertex[1];
		if (r>R) R=r;
	}

	R=sqrtf(R);
	float scale=radius/R;

	for (it=m_vertices.begin();it!=m_vertices.end();it++){
		Vertex v=(*it);
		//add a vertex into the vertex array
		(*pv)=scale*v.vertex[0]; pv++;
		(*pv)=scale*v.vertex[1]; pv++;
		(*pv)=scale*v.vertex[2]; pv++;

		//pointer normals data - add a normal for each vertex
		(*pn)=v.normal[0]; pn++;
		(*pn)=v.normal[1]; pn++;
		(*pn)=v.normal[2]; pn++;

		//pointer normals display data - builds lines for each normal
		*pnd=(*(pv-3)); pnd++;
		*pnd=(*(pv-2)); pnd++;
		*pnd=(*(pv-1)); pnd++;

		*pnd=(*(pv-3))+(*(pn-3)); pnd++;
		*pnd=(*(pv-2))+(*(pn-2)); pnd++;
		*pnd=(*(pv-1))+(*(pn-1)); pnd++;

		//pointer texture - filles u,v coordinates
		(*pt)=v.u; pt++;
		(*pt)=v.v; pt++;
	}
	m_vertices.clear();

	
	
	int numIndices=m_indices.size();
	pIndicesData=new unsigned int[numIndices];
	unsigned int *pi=pIndicesData;
	vector<unsigned int>::iterator iter=m_indices.begin();
	for (;iter!=m_indices.end();iter++){
		(*pi)=(*iter); pi++;
	}
	m_indices.clear();


	//-------------------------------------------------------------------------
	//the arrays have been loaded in sys mem. It is time to create a new model and set the GPU buffers
	
	pModel=new Model3D();
	pModel->setName(fileName);
	//pModel->setCentre(centre);

	pModel->setVertexBuffer(pVerticesData,numVertices,vertexSize);
	delete [] pVerticesData;

	pModel->setIndexBuffer(pIndicesData,numIndices,m_topology);
	delete [] pIndicesData;

	pModel->setNormalsBuffer(pNormalsData,numVertices);
	delete [] pNormalsData;

	pModel->setTextureCoordsBuffer(pTextureCoordsData,numVertices,numCoords);
	delete [] pTextureCoordsData;

	pModel->setNormalsDisplayBuffer(pNormDispData,numVertices);
	delete [] pNormDispData;
	

	string folder=computeFolder(fileName);
	*ppMaterial=parseMaterialLib(m_matLibName,folder);

	if (!(*ppMaterial)){
		(*ppMaterial)=MaterialManager::get()->hasMaterial("defMaterial");
		if (!(*ppMaterial)){
			(*ppMaterial)=new Material();
			(*ppMaterial)->setName("defMaterial");
			MaterialManager::get()->addMaterial((*ppMaterial));
		}
	}

	MeshManager::get()->addMesh(pModel);

	return pModel;
}

string Model3DLoader::getTitle(const char* lineBuffer, int length){
	string str;
	istrstream streamin (lineBuffer, length);
	streamin>>str;
	return str;
}

string Model3DLoader::computeFolder(const string& fileName){
	size_t index=fileName.find_last_of("/\\");
	if (index==string::npos) return "";
	m_localFolder=fileName.substr(0,index);
	index=m_localFolder.find_last_of("/\\");
	if (index==string::npos) index=0;
	else index++;														//don't include the first '/'
	m_localFolder=m_localFolder.substr(index)+string("/");
	return "assets/3d/models/"+m_localFolder;
}


Material* Model3DLoader::parseMaterialLib(const string &fileName, const string& folder){
	Material *pMat=NULL;

	string matLibName=folder+fileName;
	ifstream fin(matLibName.c_str());
	if (!fin.is_open()){
		//App::MsgPrintf("Cannot load file %s. \n",matLibName.c_str());			//the app will not break;
																				//if an object doesn't have a material it will use default material
		return NULL;
	}

	
	for (; !fin.eof(); ) {
		fin.getline(m_lineBuffer, sizeof(m_lineBuffer));
		m_lengthOfLine = fin.gcount();

		if (m_lengthOfLine==0 || m_lengthOfLine==1) continue;
		m_lengthOfLine--;

		//while(!fin.eof() && !strncmp(m_lineBuffer,"newmtl",6)){
		if (!strncmp(m_lineBuffer,"newmtl",6)){
			pMat=parseMaterialBlock(fin,folder);
		
			break;		//parse only the first material
		}
		//}
	}
	return pMat;
}

//parses a materaial block from a .mtl file; it scans the stream fin until it reaches eof,
//or until it reaches a new material block, starting with "newmtl"; In this case ("newmtl"),
//it returns the last line parsed and its size, so it can be used by the next mtl block.
Material* Model3DLoader::parseMaterialBlock(ifstream& fin, const string& folder){
	Material *pMat=NULL;
	
	string name=getTitle(m_lineBuffer+7,m_lengthOfLine-7);
	pMat=MaterialManager::get()->hasMaterial(name);
	if (pMat) return pMat;

	pMat=new Material();
	pMat->setName(name);

	memset(m_lineBuffer, 0, m_lengthOfLine*sizeof(char));
	TexFilter filter=LINEAR_MIPMAP_LINEAR;

	while(strncmp(m_lineBuffer,"newmtl",6) && !fin.eof()){
		fin.getline(m_lineBuffer, 100*sizeof(char));
		m_lengthOfLine = fin.gcount();
		m_lengthOfLine--;
		istrstream streamin (m_lineBuffer, m_lengthOfLine);
		string name;
		streamin>>name;

		if (!name.compare("Ka")){
			float r,g,b,a;
			streamin >> r >> g >>b;
			if (!(streamin>>a)){
				a=1;
				streamin.clear();
			}
			pMat->setAmbient(Vector4f(r,g,b,a));
			continue;
		}
		if (!name.compare("Kd")){
			float r,g,b,a;
			streamin >> r >> g >>b;
			if (!(streamin>>a)){
				a=1;
				streamin.clear();
			}
			pMat->setDiffuse(Vector4f(r,g,b,a));
			continue;
		}
		if (!name.compare("Ks")){
			float r,g,b,a;
			streamin >> r >> g >>b;
			if (!(streamin>>a)){
				a=1;
				streamin.clear();
			}
			pMat->setSpecular(Vector4f(r,g,b,a));
			continue;
		}
		if (!name.compare("Ke")){
			float r,g,b,a;
			streamin >> r >> g >>b;
			if (!(streamin>>a)){
				a=1;
				streamin.clear();
			}
			pMat->setEmissive(Vector4f(r,g,b,a));
			continue;
		}
		if (!name.compare("Ns")){
			float shiny;
			streamin>>shiny;
			pMat->setShininess(shiny);
			continue;
		}
		if (!name.compare("texFilter")){
			string str;
			streamin>>str;
			if (!str.compare("NEAREST")) filter=NEAREST;
			else if (!str.compare("LINEAR")) filter=LINEAR;
			continue;
		}
		if (!name.compare("map_Kd")){
			string texName;
			streamin>>texName;
			
			texName=folder+texName;
			Texture* pTex;
			pTex=TextureManager::get()->hasTexture(texName);
			if (!pTex){
				pTex=new Texture();
				if (!pTex->create(texName,LINEAR)){
					//couldn't find texture file
					delete pTex;
				}else{
					TextureManager::get()->addTexture(pTex);
					pMat->setTexture(pTex);
				}
			}else{
				pMat->setTexture(pTex);
			}
			continue;
		}
		
	}
	MaterialManager::get()->addMaterial(pMat);
	return pMat;
	//m_materials.push_back(mat);
}

#endif