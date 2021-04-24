#ifdef _3D

#include "TextureManager.h"

BaseTextureManager::~BaseTextureManager(){
	clear();
}
void BaseTextureManager::addTexture(Texture *pTexture){
	m_vpTextures.push_back(pTexture);
}

Texture* BaseTextureManager::hasTexture(const std::string& name) const{
	//iterate through all the array and check the name
	std::vector<Texture*>::const_iterator it=m_vpTextures.begin();
	for (;it!=m_vpTextures.end();it++){
		if ((*it)->hasName(name)) {
			return *it;
		}
	}
	return NULL;
}

void BaseTextureManager::clear(){
	std::vector<Texture*>::iterator it=m_vpTextures.begin();
	for(;it!=m_vpTextures.end();it++){
		delete (*it);
	}
	m_vpTextures.clear();
}

#endif