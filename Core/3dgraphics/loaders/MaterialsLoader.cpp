#ifdef _3D

#include "MaterialsLoader.h"
#include "../managers/MaterialManager.h"
#include "../managers/TextureManager.h"
#include "foundation/ConfigDataLoader.h"
#include "foundation/PSPHeap.h"

bool MaterialsLoader::load(const ConfigItem& confItem) const{
	string fileName;
	if(confItem.hasString("materialsConfigFile")){
		fileName=confItem.getString("materialsConfigFile");
	}else{ 
		//couldn't find any material config file;
		return false;
	}

	ConfigDataLoader dataLoader;
	ConfigData data;
	if (!dataLoader.load(fileName, data)){
		//failed to load
		return NULL;
	}


	ConfigData::ItemHandle handle = data.getItemHandle("MATERIALS_ITEM");
	if (handle!=ConfigData::INVALID_HANDLE){
		ConfigItem materialsItem = *(data.getItem(handle));
	
		int numMats=0;
		if (materialsItem.hasInteger("numMaterials")){
			numMats=materialsItem.getInteger("numMaterials");
		}

		for(int i=0;i<numMats;i++){
			string attrName="material";
			char num[3];
			itoa(i,num,10);
			//_itoa_s(i,num,3,10);
			attrName.append(num);
			
			if (materialsItem.hasString(attrName)){
				string matName=materialsItem.getString(attrName);
				parseMaterialNode(matName,data);
			}
	
		}
		return true;
	}
	return false;
}



Texture* MaterialsLoader::parseTextureNode(const ConfigItem* pItem) const{
	string attrName;
	Texture *pTex=NULL;

	if (!pItem){
		return NULL;
	}else{

		if (pItem->hasString("path")){
			attrName=pItem->getString("path");

			pTex=TextureManager::get()->hasTexture(attrName);
			if (pTex) return pTex;

			TexFilter filter;
			if (pItem->hasInteger("filter")){
				filter=(TexFilter)pItem->getInteger("filter");
			}else filter=LINEAR_MIPMAP_LINEAR;

			pTex=new Texture();
			if (!pTex->create(attrName,filter)){
				delete pTex;
				return NULL;
			}

			if (pItem->hasInteger("blendOn")){
				pTex->setBlendOn(pItem->getInteger("blendOn"));
			}else pTex->setBlendOn(1);

			TextureManager::get()->addTexture(pTex);
			return pTex;
		}else{
			//texture has no path
			return NULL;
		}
	}
	return pTex;
}

Material* MaterialsLoader::parseMaterialNode(const string& matName, const ConfigData& data) const{
	Texture *pTex;
	string attrName;
	Material *pMat=NULL;

	pMat=MaterialManager::get()->hasMaterial(matName);
	if (pMat) return pMat;


	//get the handle to the material item
	ConfigData::ItemHandle handle = data.getItemHandle(matName);
	if (handle==ConfigData::INVALID_HANDLE){
		//material not found in the config file;
		//assign default material
		pMat=MaterialManager::get()->hasMaterial("defMaterial");
		if (!pMat){
			pMat=new Material();
			pMat->setName("defMaterial");
			MaterialManager::get()->addMaterial(pMat);
			return pMat;
		}
	}else{
		//material found in the config file
		//get the material item
		const ConfigItem *pItem = data.getItem(handle);
		
		pMat=new Material();
		pMat->setName(matName);
		MaterialManager::get()->addMaterial(pMat);
	
		float alpha=1;
		if (pItem->hasVector("diffuse")){
			if (pItem->hasFloat("diffuseAlpha"))
				alpha=pItem->getFloat("diffuseAlpha");
			Vector3f v=pItem->getVector("diffuse");
			pMat->setDiffuse(Vector4f(v.x(),v.y(),v.z(),alpha));
		}

		alpha=1;
		if (pItem->hasVector("ambient")){
			if (pItem->hasFloat("ambientAlpha"))
				alpha=pItem->getFloat("ambientAlpha");
			Vector3f v=pItem->getVector("ambient");
			pMat->setAmbient(Vector4f(v.x(),v.y(),v.z(),alpha));
		}

		alpha=1;
		if (pItem->hasVector("specular")){
			if (pItem->hasFloat("specularAlpha"))
				alpha=pItem->getFloat("specularAlpha");
			Vector3f v=pItem->getVector("specular");
			pMat->setSpecular(Vector4f(v.x(),v.y(),v.z(),alpha));
		}
		alpha=1;
		if (pItem->hasVector("emissive")){
			if (pItem->hasFloat("emissiveAlpha"))
				alpha=pItem->getFloat("emissiveAlpha");
			Vector3f v=pItem->getVector("emissive");
			pMat->setEmissive(Vector4f(v.x(),v.y(),v.z(),alpha));
		}

		if (pItem->hasFloat("shininess")){
			pMat->setShininess(pItem->getFloat("shininess"));
		}
		if (pItem->hasInteger("lightOn")){
			pMat->setLightOn(pItem->getInteger("lightOn"));
		}

		if (pItem->hasString("texture")){
			attrName=pItem->getString("texture");
			//pTex=TextureManager::get()->hasTexture(attrName);
			//if (!pTex){
				pTex=parseTextureNode(getItem(attrName,data));
			//}
			if (pTex){
				pMat->setTexture(pTex);
			}
		}
	}
	return pMat;
}

const ConfigItem* MaterialsLoader::getItem(const string& name, const ConfigData& data) const{
	ConfigData::ItemHandle handle = data.getItemHandle(name);
	if (handle==ConfigData::INVALID_HANDLE) return NULL;
	return data.getItem(handle);
}

#endif