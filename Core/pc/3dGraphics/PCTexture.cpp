#ifdef _PC

#include "PCTexture.h"
#include "gxbase/Image.h"
using namespace gxbase;



#ifdef _3D

GLuint PCTexture::s_texTypes[2]={GL_TEXTURE_2D, GL_TEXTURE_3D};
GLuint PCTexture::s_texFilters[6]={GL_LINEAR,
									GL_NEAREST,
									GL_LINEAR_MIPMAP_LINEAR,
									GL_LINEAR_MIPMAP_NEAREST,
									GL_NEAREST_MIPMAP_LINEAR,
									GL_NEAREST_MIPMAP_NEAREST};

PCTexture::PCTexture(){}

PCTexture::~PCTexture(){
	if (m_texId>0)
		glDeleteTextures(1,&m_texId);
}

bool PCTexture::create(const string& fileName, TexFilter filter){
	Image image;
	if (!image.Load(fileName.c_str())) return false;
	
	m_name=fileName;
	//m_format=texFormat;
	//m_type=texType;
	//m_filter=filter;
	m_glType=s_texTypes[m_type];
	m_glFilter=s_texFilters[filter];

	glGenTextures(1,&m_texId);

	//m_pGlex->glActiveTextureARB(GL_TEXTURE0_ARB+m_layer);
	glEnable(m_glType);
	glBindTexture(m_glType,m_texId);

	
	//if (texFormat==Image::ALPHA) image.SetFormat(Image::ALPHA);		//otherwise don't force image format to be 
																	//smth else than the format from the loaded file
	image.gluBuild2DMipmaps();
	
	glTexParameteri(m_glType, GL_TEXTURE_MIN_FILTER, m_glFilter);
	glTexParameteri(m_glType, GL_TEXTURE_MAG_FILTER, m_glFilter);

	glTexParameterf(m_glType, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameterf(m_glType, GL_TEXTURE_WRAP_T, GL_REPEAT );



	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	
	//m_format=image.GetFormat();
	
	image.Free();

	glBindTexture(m_glType,0);
	glDisable(m_glType);
	return true;
}


#endif

#endif