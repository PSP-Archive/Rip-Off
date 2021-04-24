#pragma once

#ifdef _3D
#ifdef _PC

#include "../../3dgraphics/TextureIF.h"

#include "GL/glut.h"
#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glut32.lib")

class PCTexture:public TextureIF{
private:
	static GLuint s_texTypes[2];
	static GLuint s_texFilters[6];
	
	GLuint m_glType;
	GLuint m_glFilter;
	
	//GLuint m_texId;
	//GLuint m_type;
	//GLint m_filter;				//minification/magnification filter; it usually is GL_LINEAR_MIPMAP_LINEAR
	int m_width, m_height;
	//Image::Format m_format;

private:
	//block the copy constructor and the assignment operator
	PCTexture(const PCTexture& rhs){}
	PCTexture& operator = (const PCTexture& rhs){}

public:
	PCTexture();
	~PCTexture();

	bool create(const string& filename, TexFilter filter);
	
	void enable() const;
	void disable() const;

	void apply() const;
	void dismiss() const;
};

inline void PCTexture::enable() const{
	glEnable(m_glType);
}

inline void PCTexture::disable() const{
	glDisable(m_glType);
}

inline void PCTexture::apply() const{
	//if (m_format==Image::RGBA || m_format==Image::ALPHA){
	//	glEnable(GL_BLEND);
	//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//}
	//m_pGlex->glActiveTextureARB(GL_TEXTURE0_ARB+m_layer);
	if (m_blendOn) {
		glEnable(GL_BLEND);
		glDepthMask(GL_FALSE);
	}
	glEnable(m_glType);
	glBindTexture(m_glType,m_texId);
}

inline void PCTexture::dismiss() const{
	glBindTexture(m_glType,0);
	glDisable(m_glType);		//??disable texture2D or leave it as default??
	if (m_blendOn) {
		glDisable(GL_BLEND);
		glDepthMask(GL_TRUE);
	}
}
#endif
#endif