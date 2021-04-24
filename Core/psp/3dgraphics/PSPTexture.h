#pragma once

#ifdef _3D
#ifdef _SPSP

#include "../../3dgraphics/TextureIF.h"
#include <libgu.h>
#include <libgum.h>

#include "PSPTexture.h"



class PSPTexture:public TextureIF{

public:
	PSPTexture();
	~PSPTexture();

	bool create(const std::string& filename, TexFilter filter);
	
	void enable() const;
	void disable() const;

	void apply() const;
	void dismiss() const;


private:
	//block the copy constructor and the assignment operator
	PSPTexture(const PSPTexture& rhs){}
	PSPTexture& operator = (const PSPTexture& rhs){ return *this; }

	//places the whole buffer from pTexData in Vram Texture
	void _setVramTexture(const unsigned short *pTexData, unsigned int texSize);

	void _parseToVram(const char* buffer);

private:
	static int s_texMode[16];
	static int s_texFilters[6];
	
	int m_filter;
	int m_sceGuType; //only SCEGU_TEXTURE for the moment;
					 //in OpenGL could have been TEXTURE_2D or 3D
					 //parameter kept for interface symmetry
	int m_sceTexMode;

	int m_width, m_height;
	int m_type;

	void *m_pVram;

};

inline void PSPTexture::enable() const{
	sceGuEnable(m_sceGuType);
}

inline void PSPTexture::disable() const{
	sceGuDisable(m_sceGuType);
}

inline void PSPTexture::apply() const{
	
	sceGuEnable(SCEGU_TEXTURE);
	sceGuTexFunc(SCEGU_BLEND, SCEGU_RGBA);	// Set texture function
	sceGuTexEnvColor(0x00808080);
	sceGuTexFunc(SCEGU_TEX_MODULATE, SCEGU_RGBA);
	sceGuTexMapMode(SCEGU_UV_MAP, 0, 0);
	sceGuTexWrap(SCEGU_REPEAT, SCEGU_REPEAT);
	sceGuTexFilter(SCEGU_LINEAR, SCEGU_LINEAR);


	sceGuTexMode(m_type, 0, SCEGU_SINGLE_CLUT, SCEGU_TEXBUF_NORMAL);
	sceGuTexImage(0, m_width, m_height, m_width, m_pVram);

}

inline void PSPTexture::dismiss() const{
	sceGuDisable(m_sceGuType);
}

#endif
#endif