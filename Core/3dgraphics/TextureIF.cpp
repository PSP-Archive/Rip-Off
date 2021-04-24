#include "TextureIF.h"

#ifdef _3D

TextureIF::TextureIF():m_type(TEXTURE_2D),
					   m_texId(0),
					   m_blendOn(0)
{}

void TextureIF::setBlendOn(int blendOn){
	m_blendOn=blendOn;
}

bool TextureIF::hasName(const std::string& name) const{
	printf("tex name: %s\n",m_name.c_str());
	if (!m_name.compare(name)) return true;
	return false;
}

#endif