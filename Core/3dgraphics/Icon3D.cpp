#ifdef _3D

#include "Icon3D.h"
#include "managers/MeshManager.h"
#include "foundation/Vector2f.h"
#include "foundation/PSPHeap.h"
//#include "foundation/Matrix44f.h"

Icon3D::Icon3D(const Icon3D& rhs){
	/*
	m_width2=rhs.m_width2;
	m_height2=rhs.m_height2;				//half of width, height
	
	m_vaObject=rhs.m_vaObject;

	m_numVertices=rhs.m_numVertices;
	m_vertexSize=rhs.m_vertexSize;

	int size=3*m_numVertices;

	m_flags=rhs.m_flags;

	if (rhs.m_pVertices) {
		//m_pVertices=new float[size];
		m_pVertices=(float*)sceGuGetMemory(size*sizeof(float));
		memcpy(m_pVertices,rhs.m_pVertices,size*sizeof(float));

	}else m_pVertices=NULL;

	if (rhs.m_pTexCoords) {
		//m_pTexCoords=new float[2*m_numVertices];
		m_pTexCoords=(float*)sceGuGetMemory(2*m_numVertices*sizeof(float));
		memcpy(m_pTexCoords,rhs.m_pTexCoords,m_numVertices*2*sizeof(float));
	}else m_pTexCoords=NULL;
	if (rhs.m_pNormals) {
		//m_pNormals=new float[size];
		m_pNormals=(float*)sceGuGetMemory(size*sizeof(float));
		memcpy(m_pNormals,rhs.m_pNormals,size*sizeof(float));
	}else m_pNormals=NULL;

	if (rhs.m_pIndices) {
		//m_pIndices=new unsigned int[4];
		m_pIndices=(unsigned int*)sceGuGetMemory(4*sizeof(float));
		memcpy(m_pIndices,rhs.m_pIndices,4*sizeof(unsigned int));
	}else m_pIndices=NULL;
	if (rhs.m_pVertexTexNormals){
		//m_pVertexTexNormals=new float[size];
		m_pVertices=(float*)sceGuGetMemory(m_vertexSize*m_numVertices*sizeof(float));
		memcpy(m_pVertexTexNormals,rhs.m_pVertexTexNormals,m_vertexSize*m_numVertices*sizeof(float));
	}else m_pVertexTexNormals=NULL;


	
	m_topology=rhs.m_topology;

	
	m_pMaterial=rhs.m_pMaterial;	//copy only the pointer! the material manager will delete it when necessary

	m_renderer=rhs.m_renderer;
	*/

	m_width2=rhs.m_width2;
	m_height2=rhs.m_height2;				//half of width, height
	
	m_vaObject=rhs.m_vaObject;

	m_numVertices=rhs.m_numVertices;
	m_vertexSize=rhs.m_vertexSize;

	int size=3*m_numVertices;

	m_flags=rhs.m_flags;
	
	
	//int size=3*m_numVertices;
	
	if (rhs.m_pVertices) {
		m_pVertices=new float[size];
		memcpy(m_pVertices,rhs.m_pVertices,m_numVertices*3*sizeof(float));
	}else m_pVertices=NULL;

	if (rhs.m_pTexCoords) {
		m_pTexCoords=new float[2*m_numVertices];
		memcpy(m_pTexCoords,rhs.m_pTexCoords,m_numVertices*2*sizeof(float));
	}else m_pTexCoords=NULL;
	if (rhs.m_pNormals) {
		m_pNormals=new float[size];
		memcpy(m_pNormals,rhs.m_pNormals,m_numVertices*3*sizeof(float));
	}else m_pNormals=NULL;

	if (rhs.m_pIndices) {
		m_pIndices=new unsigned int[4];
		memcpy(m_pIndices,rhs.m_pIndices,4*sizeof(unsigned int));
	}else m_pIndices=NULL;
	if (rhs.m_pVertexTexNormals){
		m_pVertexTexNormals=new float[size];
		memcpy(m_pVertexTexNormals,rhs.m_pVertexTexNormals,m_vertexSize*m_numVertices*sizeof(float));
	}
	
	m_topology=rhs.m_topology;

	
	m_pMaterial=rhs.m_pMaterial;	//copy only the pointer! the material manager will delete it when necessary

	m_renderer=rhs.m_renderer;

}

Icon3D& Icon3D::operator = (const Icon3D& rhs){

	/*m_width2=rhs.m_width2;
	m_height2=rhs.m_height2;				//half of width, height
	
	m_vaObject=rhs.m_vaObject;

	m_numVertices=rhs.m_numVertices;
	m_vertexSize=rhs.m_vertexSize;

	int size=3*m_numVertices;

	m_flags=rhs.m_flags;

	if (rhs.m_pVertices) {
		//m_pVertices=new float[size];
		m_pVertices=(float*)sceGuGetMemory(size*sizeof(float));
		memcpy(m_pVertices,rhs.m_pVertices,size*sizeof(float));

	}else m_pVertices=NULL;

	if (rhs.m_pTexCoords) {
		//m_pTexCoords=new float[2*m_numVertices];
		m_pTexCoords=(float*)sceGuGetMemory(2*m_numVertices*sizeof(float));
		memcpy(m_pTexCoords,rhs.m_pTexCoords,m_numVertices*2*sizeof(float));
	}else m_pTexCoords=NULL;
	if (rhs.m_pNormals) {
		//m_pNormals=new float[size];
		m_pNormals=(float*)sceGuGetMemory(size*sizeof(float));
		memcpy(m_pNormals,rhs.m_pNormals,size*sizeof(float));
	}else m_pNormals=NULL;

	if (rhs.m_pIndices) {
		//m_pIndices=new unsigned int[4];
		m_pIndices=(unsigned int*)sceGuGetMemory(4*sizeof(float));
		memcpy(m_pIndices,rhs.m_pIndices,4*sizeof(unsigned int));
	}else m_pIndices=NULL;
	if (rhs.m_pVertexTexNormals){
		//m_pVertexTexNormals=new float[size];
		m_pVertices=(float*)sceGuGetMemory(m_vertexSize*m_numVertices*sizeof(float));
		memcpy(m_pVertexTexNormals,rhs.m_pVertexTexNormals,m_vertexSize*m_numVertices*sizeof(float));
	}else m_pVertexTexNormals=NULL;


	
	m_topology=rhs.m_topology;

	
	m_pMaterial=rhs.m_pMaterial;	//copy only the pointer! the material manager will delete it when necessary

	m_renderer=rhs.m_renderer;
*/
	m_width2=rhs.m_width2;
	m_height2=rhs.m_height2;				//half of width, height
	
	m_vaObject=rhs.m_vaObject;

	m_numVertices=rhs.m_numVertices;
	m_vertexSize=rhs.m_vertexSize;

	int size=3*m_numVertices;

	m_flags=rhs.m_flags;
	
	
	//int size=3*m_numVertices;
	
	if (rhs.m_pVertices) {
		m_pVertices=new float[size];
		memcpy(m_pVertices,rhs.m_pVertices,m_numVertices*3*sizeof(float));
	}else m_pVertices=NULL;

	if (rhs.m_pTexCoords) {
		m_pTexCoords=new float[2*m_numVertices];
		memcpy(m_pTexCoords,rhs.m_pTexCoords,m_numVertices*2*sizeof(float));
	}else m_pVertices=NULL;
	if (rhs.m_pNormals) {
		m_pNormals=new float[size];
		memcpy(m_pNormals,rhs.m_pNormals,m_numVertices*3*sizeof(float));
	}else m_pNormals=NULL;

	if (rhs.m_pIndices) {
		m_pIndices=new unsigned int[4];
		memcpy(m_pIndices,rhs.m_pIndices,4*sizeof(unsigned int));
	}else m_pIndices=NULL;
	if (rhs.m_pVertexTexNormals){
		m_pVertexTexNormals=new float[size];
		memcpy(m_pVertexTexNormals,rhs.m_pVertexTexNormals,m_vertexSize*m_numVertices*sizeof(float));
	}
	
	m_topology=rhs.m_topology;

	
	m_pMaterial=rhs.m_pMaterial;	//copy only the pointer! the material manager will delete it when necessary

	m_renderer=rhs.m_renderer;

	return *this;
}


//--------------------------------------------------------------------------------


bool Icon3D::create(const Vector3f& u, const Vector3f& v, int flags){
	//m_width2=width/2.0f;
	//m_height2=height/2.0f;

	m_numVertices=4;
	int size;
	m_flags=(VertexFormatFlags)flags;

	if (flags&VFF_UNKNOWN){
		size=3*m_numVertices;
		m_pVertices=new float[size];
		m_pNormals=new float[size];
		m_pTexCoords=new float[2*m_numVertices];
		m_pIndices=new unsigned int[4];

		resetMesh(u,v);

		m_pTexCoords[0]=0; m_pTexCoords[1]=0;
		m_pTexCoords[2]=1; m_pTexCoords[3]=0;
		m_pTexCoords[4]=1; m_pTexCoords[5]=1;
		m_pTexCoords[6]=0; m_pTexCoords[7]=1;

		m_pIndices[0]=0;
		m_pIndices[1]=1;
		m_pIndices[2]=2;
		m_pIndices[3]=3;
		//m_topology=QUADS;
		m_topology=TRIANGLE_STRIP;
	}else{
		if (flags&(VFF_VERTEX3|VFF_TEX2)){
			m_vertexSize=5;
		}else if (flags&(VFF_VERTEX3|VFF_TEX2|VFF_NORMAL3)){
			m_vertexSize=8;
		}else if (flags&(VFF_VERTEX3|VFF_NORMAL3)){
			m_vertexSize=6;
		}else if (flags&(VFF_VERTEX3)){
			m_vertexSize=3;
		}else return false;

		m_vaObject.setFlags(flags);
		size=m_vertexSize*m_numVertices;
		m_pVertexTexNormals=new float[size];
		m_pIndices=new unsigned int[4];
		//sceGuStart(SCEGU_IMMEDIATE, m_dispList, sizeof(m_dispList));
		//m_pVertexTexNormals=(float*)sceGuGetMemory(size*sizeof(float));
		//m_pIndices=(unsigned int*)sceGuGetMemory(4*sizeof(unsigned int));

		resetMesh();

		m_pIndices[0]=0;
		m_pIndices[1]=1;
		m_pIndices[2]=2;
		m_pIndices[3]=3;

		m_topology=TRIANGLE_STRIP;

		//sceGuFinish();
	}


	return true;
}

//--------------------------------------------------------------------------------
//static char call_list[0x100] __attribute__((aligned(64)));
void Icon3D::renderGeometry(const Vector3f& centre, float angle) const{
	
	
	//sceGuColor(0xffffffff);
	//sceGumDrawArray(SCEGU_PRIM_TRIANGLE_STRIP,
	//			SCEGU_TEXTURE_FLOAT|SCEGU_NORMAL_FLOAT|SCEGU_VERTEX_FLOAT,
	//			4, 0, model);
	
	
	m_pMaterial->apply();	

	//const Vector3f right=MeshManager::get()->getCameraRight();
	//const Vector3f vup=MeshManager::get()->getCameraVup();
	////const Vector3f vup(0,1,0);
	////printf("right=(%f,%f,%f)\n",right.x(),right.y(),right.z());
	////printf("vup=(%f,%f,%f)\n",vup.x(),vup.y(),vup.z());
	
	//resetMesh(right, vup);
	
	//m_renderer.enableRendering(centre,angle,right.Cross(vup));
	//	m_vaObject.enableDrawingStateNoNormals(m_pVertices,m_pTexCoords);
	//		m_vaObject.render(m_pIndices,m_numVertices,0,m_topology);
	//	m_vaObject.disableDrawingStateNoNormals();
	//m_renderer.disableRendering();


	//resetMesh();

	//sceGuStart(SCEGU_CALL, call_list, sizeof(call_list));

	unsigned int m_size=m_numVertices*m_vertexSize*sizeof(float);
	float* pGfxVff=(float*)sceGuGetMemory(m_size);
	memcpy(pGfxVff,m_pVertexTexNormals,m_size);



	m_renderer.enableRendering(centre,angle,Vector3f(0,0,1));
	//m_vaObject.render(m_pVertexTexNormals,0,m_numVertices,0,m_topology);
	m_vaObject.render(pGfxVff,0,m_numVertices,0,m_topology);
	m_renderer.disableRendering();
	//sceGuFinish();
	//sceGuSync( SCEGU_SYNC_FINISH, SCEGU_SYNC_WAIT );	// Wait for end of drawing

	m_pMaterial->dismiss();
	
}

void Icon3D::setTextureCoordinates(float *texCoords){
	if (m_flags&VFF_UNKNOWN){
		if (m_pTexCoords && texCoords)
			memcpy(m_pTexCoords,texCoords,8*sizeof(float));
	}else if (m_pVertexTexNormals && texCoords && (m_flags&VFF_TEX2)){
		
		int offsetDest=0, offsetSrc=0; 
		for (int i=0;i<4;i++){
			memcpy(m_pVertexTexNormals+offsetDest,texCoords+offsetSrc,2*sizeof(float));
			offsetDest+=m_vertexSize;
			offsetSrc+=2;
		}
	}

}


//------------------------------------------------------------------------------------------


void Icon3D::resetMesh(const Vector3f& u, const Vector3f& v) const{
	
	//printf("right=(%f,%f,%f)\n",u.x(),u.y(),u.z());
	//printf("vup=(%f,%f,%f)\n",v.x(),v.y(),v.z());

	Vector3f vertex;
	Vector3f normal=u.Cross(v);
	normal.Normalise();

	//vertex=centre-u*m_width2-v*m_height2;
	

	vertex=-u*m_width2+v*m_height2;
	memcpy(m_pVertices,vertex.GetArray(),3*sizeof(float));
	memcpy(m_pNormals,normal.GetArray(),3*sizeof(float));

	vertex=-u*m_width2-v*m_height2;
	memcpy(m_pVertices+3,vertex.GetArray(),3*sizeof(float));
	memcpy(m_pNormals+3,normal.GetArray(),3*sizeof(float));

	vertex=u*m_width2+v*m_height2;
	memcpy(m_pVertices+6,vertex.GetArray(),3*sizeof(float));
	memcpy(m_pNormals+6,normal.GetArray(),3*sizeof(float));

	vertex=u*m_width2-v*m_height2;
	memcpy(m_pVertices+9,vertex.GetArray(),3*sizeof(float));
	memcpy(m_pNormals+9,normal.GetArray(),3*sizeof(float));


	//if the camera is perpendicular to the game scene, we have
	//u=(1,0,0)
	//v=(0,1,0)
	//s


}


void Icon3D::resetMesh() const{
	Vector3f vertex; float texCoord[2];
	Vector3f normal(0,0,1); 
	int offset=0;
	
	//vertex=-u*m_width2+v*m_height2;
	vertex=Vector3f(-m_width2,m_height2,0); texCoord[0]=0; texCoord[1]=1;
	memcpy(m_pVertexTexNormals+offset,&texCoord,2*sizeof(float)); offset+=2;
	memcpy(m_pVertexTexNormals+offset,vertex.GetArray(),3*sizeof(float)); offset+=3;
	
	

	//vertex=-u*m_width2-v*m_height2;
	vertex=Vector3f(-m_width2,-m_height2,0); texCoord[0]=0; texCoord[1]=0; //texCoord=Vector2f(0,0);
	memcpy(m_pVertexTexNormals+offset,&texCoord,2*sizeof(float)); offset+=2;
	memcpy(m_pVertexTexNormals+offset,vertex.GetArray(),3*sizeof(float)); offset+=3;
	

	//vertex=u*m_width2+v*m_height2;
	vertex=Vector3f(m_width2,m_height2,0); texCoord[0]=1; texCoord[1]=1; //texCoord=Vector2f(1,1);
	memcpy(m_pVertexTexNormals+offset,&texCoord,2*sizeof(float)); offset+=2;
	memcpy(m_pVertexTexNormals+offset,vertex.GetArray(),3*sizeof(float)); offset+=3;

	//vertex=u*m_width2-v*m_height2;
	vertex=Vector3f(m_width2,-m_height2,0); texCoord[0]=1; texCoord[1]=0; //texCoord=Vector2f(1,0);
	memcpy(m_pVertexTexNormals+offset,&texCoord,2*sizeof(float)); offset+=2;
	memcpy(m_pVertexTexNormals+offset,vertex.GetArray(),3*sizeof(float)); offset+=3;
	



	//theoretically, we should have done smth like:
	//if (m_flags&VFF_TEX2){...}
	//if (m_flags&VFF_NORMAL3){...}
	//practically, an icon will always have Vertex3 and tex2, and we
	//can remove all the ifs;
	//We could have also used (u,v) but they are fixed in this case as well

}


void Icon3D::resetMeshNoTexCoords() const{
	Vector3f vertex;
	int offset=0;
	
	//vertex=-u*m_width2+v*m_height2;
	vertex=Vector3f(-m_width2,m_height2,0); offset+=2;
	memcpy(m_pVertexTexNormals+offset,vertex.GetArray(),3*sizeof(float)); offset+=3;
	
	

	//vertex=-u*m_width2-v*m_height2;
	vertex=Vector3f(-m_width2,-m_height2,0); offset+=2;
	memcpy(m_pVertexTexNormals+offset,vertex.GetArray(),3*sizeof(float)); offset+=3;
	

	//vertex=u*m_width2+v*m_height2;
	vertex=Vector3f(m_width2,m_height2,0); offset+=2;
	memcpy(m_pVertexTexNormals+offset,vertex.GetArray(),3*sizeof(float)); offset+=3;

	//vertex=u*m_width2-v*m_height2;
	vertex=Vector3f(m_width2,-m_height2,0); offset+=2;
	memcpy(m_pVertexTexNormals+offset,vertex.GetArray(),3*sizeof(float)); offset+=3;
}

#endif