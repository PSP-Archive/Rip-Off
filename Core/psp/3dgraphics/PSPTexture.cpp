#ifdef _3D
#ifdef _SPSP


#include "PSPTexture.h"
//#include <libgu.h>
//#include <libgum.h>

//#include "TextureData/TestTexture4444.h"

#include "PSPTexMemInitializer.h"


//GLuint PSPTexture::s_texTypes[2]={GL_TEXTURE_2D, GL_TEXTURE_3D};
int PSPTexture::s_texMode[16]={
							SCEGU_PF5551,
							SCEGU_PF5650,
							SCEGU_PF4444,
							SCEGU_PF8888,
							SCEGU_PFIDX4,
							SCEGU_PFIDX8
							};
//int PSPTexture::s_CLUTMode[1]={
//								SCEGU_PF5551
//							 };
int PSPTexture::s_texFilters[6]={SCEGU_LINEAR,
								SCEGU_NEAREST,
								SCEGU_LINEAR_MIPMAP_LINEAR,
								SCEGU_LINEAR_MIPMAP_NEAREST,
								SCEGU_NEAREST_MIPMAP_LINEAR,
								SCEGU_NEAREST_MIPMAP_NEAREST};


//u_char8 *PSPTexture::s_vramaddr=(u_char8 *)sceGeEdramGetAddr();

PSPTexture::PSPTexture(){}

PSPTexture::~PSPTexture(){
	//if (m_texId>0)
	//	glDeleteTextures(1,&m_texId);
}


//void PSPTexture::_initGraphicsVram(){
//	vramaddr+=SCEGU_VRAM_BUFSIZE32*2+SCEGU_VRAM_BUFSIZE;
//}

void PSPTexture::_setVramTexture(const unsigned short *pTexData, unsigned int texSize){
//void PSPTexture::_setVramTexture(const u_int32 *pTexData, unsigned int texSize){
	//m_pVram=PSPTexMemInitializer::get()->getVramAddr();
	//printf("size=%d, addr=%d\n",texSize,m_pVram);
	//memcpy(m_pVram,pTexData,texSize);

	//m_pVram=PSPTexMemInitializer::get()->getVramAddr();
	//int size=sizeof(clut_tex_pfidx4);
	//memcpy(m_pVram,clut_tex_pfidx4,size);
	//void *pVram=((u_int32*)m_pVram)+size;
	//size=sizeof(pix_tex_pfidx4);
	//memcpy(pVram,pix_tex_pfidx4,size);

	u_char8* pVram;
	pVram=(u_char8*)sceGeEdramGetAddr();//PSPTexMemInitializer::get()->getVramAddr();
	pVram+=SCEGU_VRAM_BUFSIZE32*2+SCEGU_VRAM_BUFSIZE;
	memcpy(pVram,pTexData,texSize);
	
	m_pVram=pVram;
	PSPTexMemInitializer::get()->increaseVramAddr(texSize);

//puc8Vram=(u_char8*)sceGeEdramGetAddr();
//	puc8Vram+=SCEGU_VRAM_BUFSIZE32*2+SCEGU_VRAM_BUFSIZE;
//	m_pVram=puc8Vram;


}
#include <kernel.h>
bool PSPTexture::create(const std::string& fileName, TexFilter filter){

	
	m_sceGuType=SCEGU_TEXTURE;
	m_sceTexMode=s_texMode[3];
	m_filter=s_texFilters[filter];
	m_name=fileName;


	//m_width=256;
	//m_height=128;
	//m_type=SCEGU_PF4444;

	//_setVramTexture(pix_tex_pf4444,sizeof(pix_tex_pf4444));
	

//	m_width=128;
//	m_height=256;
//	m_type=SCEGU_PF4444; //SCEGU_PF5551;

//	_setVramTexture(pix_tex_pf4444,sizeof(pix_tex_pf4444));


	
	//-------------------------------------------------------------------------------------------
	// read file and store it in an array
	//-------------------------------------------------------------------------------------------
	SceUID fd = sceIoOpen(fileName.c_str(), SCE_O_RDONLY, 0);
	if (fd<0) return false;		//file not found
	SceUInt32 sourceSize = (SceUInt32)sceIoLseek(fd, (SceOff)0, SCE_SEEK_END);

	int id = sceKernelAllocMemoryBlock(fileName.c_str(), SCE_KERNEL_SMEM_LOW, sourceSize, NULL);
	void* buffer;
	
	sceKernelGetMemoryBlockAddr(id, &buffer);
	memset(buffer, '\0', sourceSize);

	sceIoLseek(fd, 0, SCE_SEEK_SET);
	sceIoRead(fd, buffer, sourceSize);
	
	sceIoClose(fd);

	//-----------------------------------------------
	//		parse the contents of buffer
	//-----------------------------------------------

	char *pc=(char*)buffer;
	int type;
	memcpy(&type,pc,sizeof(int));	pc+=sizeof(int);
	memcpy(&m_width,pc,sizeof(int));	pc+=sizeof(int);
	memcpy(&m_height,pc,sizeof(int));	pc+=sizeof(int);
	
	//sceIoRead(fd,&type,sizeof(int));
	//sceIoRead(fd,&m_width,sizeof(int));
	//sceIoRead(fd,&m_height,sizeof(int));
	
	unsigned short usVal;
	u_int32 uiVal;
	u_char8 *puc8Vram;


	//puc8Vram=(u_char8*)sceGeEdramGetAddr();
	//puc8Vram+=SCEGU_VRAM_BUFSIZE32*2+SCEGU_VRAM_BUFSIZE;
	//m_pVram=puc8Vram;

	switch(type){
		case 5551:
			m_type=SCEGU_PF5551;
			break;
		case 4444:
			m_type=SCEGU_PF4444;
			break;
		case 5650:
			m_type=SCEGU_PF5650;
			break;
		case 8888:
			m_type=SCEGU_PF8888;
			break;
		default:
			//unkown format
			return false;
	}

	if (type==5551 || type==4444 || type==5650){
		m_pVram=puc8Vram=PSPTexMemInitializer::get()->getVramAddr();
		//m_pusData=new unsigned short [m_width*m_height];
		char cNum4[4];
		for (int i=0;i<m_width*m_height;i++){
			
			//memcpy(&usVal,pc,sizeof(unsigned short));
			memcpy(puc8Vram,pc,sizeof(unsigned short)); pc+=sizeof(unsigned short);
				

			//memcpy(puc8Vram,pc,sizeof(unsigned short));	pc+=sizeof(unsigned short);
			puc8Vram+=sizeof(unsigned short);
			//memcpy(m_pusData,&pc,sizeof(unsigned short));	pc+=sizeof(unsigned short);
			//m_pusData+=1;//sizeof(unsigned short);
		}
		PSPTexMemInitializer::get()->increaseVramAddr(m_width*m_height*sizeof(unsigned short));
	}else if (type==8888){
		m_pVram=puc8Vram=PSPTexMemInitializer::get()->getVramAddr();
		char cNum4[8];
		for (int i=0;i<m_width*m_height;i++){
			memcpy(puc8Vram,pc,sizeof(unsigned int)); pc+=sizeof(unsigned int);
			puc8Vram+=sizeof(unsigned int);
		}
		PSPTexMemInitializer::get()->increaseVramAddr(m_width*m_height*sizeof(unsigned int));
	}

	/*switch(type){
		case 5551:
			m_type=SCEGU_PF5551;
			m_pVram=puc8Vram=PSPTexMemInitializer::get()->getVramAddr();
			//m_pusData=new unsigned short [m_width*m_height];
			for (int i=0;i<m_width*m_height;i++){
				//sceIoRead(fd,&usVal,sizeof(unsigned short));
				memcpy(puc8Vram,&pc,sizeof(unsigned short));	pc+=sizeof(unsigned short);
				puc8Vram+=sizeof(unsigned short);
				//memcpy(m_pusData,&pc,sizeof(unsigned short));	pc+=sizeof(unsigned short);
				//m_pusData+=1;//sizeof(unsigned short);
			}
			PSPTexMemInitializer::get()->increaseVramAddr(m_width*m_height*sizeof(unsigned short));
			break;
		case 4444:
			m_type=SCEGU_PF4444;
			m_pVram=puc8Vram=PSPTexMemInitializer::get()->getVramAddr();
			for (int i=0;i<m_width*m_height;i++){
				
				memcpy(&usVal,&pc,sizeof(unsigned short));
				memcpy(puc8Vram,&usVal,sizeof(unsigned short)); pc+=sizeof(unsigned short);
				//memcpy(puc8Vram,&pc,sizeof(unsigned short));	pc+=sizeof(unsigned short);
				puc8Vram+=sizeof(unsigned short);
			}
			PSPTexMemInitializer::get()->increaseVramAddr(m_width*m_height*sizeof(unsigned short));
			break;
		case 8888:
			break;
	}
	*/

	//-----------------------------------------------

	sceKernelFreeMemoryBlock(id);
	sceKernelDcacheWritebackInvalidateAll();
	
	
	
	
	
	



	//-------------------------------------------------------------------------------------------
	//			pass the array to the 
	//-------------------------------------------------------------------------------------------

	//_setVramTexture(pix_guard1_1,sizeof(pix_guard1_1));





	//sceGuDrawBuffer(SCEGU_PF8888, SCEGU_VRAM_BP32_0, SCEGU_VRAM_WIDTH);
	//sceGuDispBuffer(SCEGU_SCR_WIDTH, SCEGU_SCR_HEIGHT,
	//				SCEGU_VRAM_BP32_1, SCEGU_VRAM_WIDTH);
	//sceGuDepthBuffer(SCEGU_VRAM_BP32_2, SCEGU_VRAM_WIDTH);


	//sceGuEnable(SCEGU_TEXTURE);
	//sceGuTexFunc(SCEGU_TEX_MODULATE, SCEGU_RGBA);
	//sceGuTexMapMode(SCEGU_UV_MAP, 0, 0);
	//sceGuTexWrap(SCEGU_REPEAT, SCEGU_REPEAT);
	//sceGuTexFilter(SCEGU_LINEAR, SCEGU_LINEAR);

	//sceGuTexMode(SCEGU_PF8888, 0, SCEGU_SINGLE_CLUT, SCEGU_TEXBUF_NORMAL);
	//sceGuTexImage(0, 256, 128, 256, pVram);
	return true;
	//return false;
	//Image image;
	//if (!image.Load(fileName.c_str())) return false;
	
	/*m_name=fileName;
	
	m_sceGuType=SCEGU_TEXTURE;
	m_filter=s_texFilters[filter];
	m_sceTexMode=s_texMode[6];


	sceGuClutMode(SCEGU_PF5551, 0, 0xff, 0);
	sceGuClutLoad(1, clut_tex_pfidx4);
	sceGuTexMode(SCEGU_PFIDX4, 0, SCEGU_SINGLE_CLUT, SCEGU_TEXBUF_NORMAL);
	sceGuTexImage(0, 256, 128, 256, pix_tex_pfidx4);


	apply();
	sceGuTexFunc(SCEGU_TEX_MODULATE, SCEGU_RGBA);
	sceGuTexMapMode(SCEGU_UV_MAP, 0, 0);
	sceGuTexWrap(SCEGU_REPEAT, SCEGU_REPEAT);
	sceGuTexFilter(SCEGU_LINEAR, SCEGU_LINEAR);

	dismiss();
	*/

	/*glGenTextures(1,&m_texId);

	glEnable(m_glType);
	glBindTexture(m_glType,m_texId);

	
	image.gluBuild2DMipmaps();
	
	glTexParameteri(m_glType, GL_TEXTURE_MIN_FILTER, m_glFilter);
	glTexParameteri(m_glType, GL_TEXTURE_MAG_FILTER, m_glFilter);

	glTexParameterf(m_glType, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameterf(m_glType, GL_TEXTURE_WRAP_T, GL_REPEAT );



	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	
	
	image.Free();

	glBindTexture(m_glType,0);
	glDisable(m_glType);
	
	return true;
	*/
}


#endif

#endif