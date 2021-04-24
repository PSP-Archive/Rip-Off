#pragma once

#ifdef _3D

#include "foundation/Singleton.h"
//#include "foundation/Array.h"
#include <vector>
#include "foundation/PSPHeap.h"
//using namespace std;

#include "../Texture.h"


//this class will hold references to all the allocated textures from the game.
//
//USAGE:
//	at loading time: every time a texture needs to be created,
//		check if it is already in the array with hasTexture(name).
//		If there is another texture with the same name, the loader
//		must take the reference to the existing texture, and not create it again.
//			pTex=TextureManager::get()->hasTexture("texName");
//			if (!pTex){
//				pTex=new Texture();
//				TextureManager::get()->addTexture(pTex);
//			}
//
//	at deletion time:
// this class is responsable with textures destruction.
// the materials that have a reference to a texture won't delete it, as it might be shared


class BaseTextureManager{
private:
	std::vector<Texture*> m_vpTextures;
	//Array<Texture*> m_vpTextures;
public:
	~BaseTextureManager();
	//returns the address of the material with name "name", or NULL if the material does not
	//exist in the array
	Texture* hasTexture(const std::string& name) const;
	void addTexture(Texture* pTexture);

	void clear();
};


typedef Singleton<BaseTextureManager> TextureManager;

#endif