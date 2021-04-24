#include "Scene3DLoader.h"

#ifdef _3D

#include "foundation/ConfigData.h"
#include "foundation/ConfigDataLoader.h"
#include "GFXObject3DLoader.h"
#include "../managers/MaterialManager.h"
#include "../managers/TextureManager.h"

#include "LightLoader.h"

#include "../../graphics/Scene.h"
#include "foundation/PSPHeap.h"

Scene* Scene3DLoader::load(const ConfigItem& confItem) const{
	string fileName, attrName;
	if(confItem.hasString("sceneGeometry")){
		fileName=confItem.getString("sceneGeometry");
	}else{ 
		//couldn't find any scene config file; return null 
		return NULL;
	}

	ConfigDataLoader dataLoader;
	ConfigData data;
	if (!dataLoader.load(fileName, data)){
		//failed to load
		return NULL;
	}

	Scene *pScene=new Scene();

	ConfigData::ItemHandle handle = data.getItemHandle("SCENE_CONF");
	if (handle==ConfigData::INVALID_HANDLE){
		delete pScene;
		return NULL;
	}
	ConfigItem item = *(data.getItem(handle));

	//---------------------------------------------------------------------------
	//parse background objects
	//---------------------------------------------------------------------------
	int i=1;

	if(item.hasInteger("bgr")){
		i=item.getInteger("bgr");
	}else{
		delete pScene;
		return NULL;
	}

	Material *pMaterials[6];

	if (item.hasString("bgrMaterial")){
		//get the material's name
		attrName=item.getString("bgrMaterial");

		for (int i=0;i<6;i++){
			string attrName1=attrName;
			char num[2];
			itoa(i,num,10);
			//_itoa_s(i,num,2,10);
			attrName1.append(num);
			pMaterials[i]=MaterialManager::get()->hasMaterial(attrName1);
			if (!pMaterials[i])
				pMaterials[i]=MaterialManager::get()->hasMaterial("defMaterial");
			if (!pMaterials[i]){
				pMaterials[i]=new Material();
				pMaterials[i]->setName("defMaterial");
				MaterialManager::get()->addMaterial(pMaterials[i]);
			}
		}

	}else{
		//the config file doesn't give any background material name
		//we will assume the background is the default material
		for (int i=0;i<6;i++){
			pMaterials[i]=MaterialManager::get()->hasMaterial("defMaterial");
			if (!pMaterials[i]){
				pMaterials[i]=new Material();
				pMaterials[i]->setName("defMaterial");
				MaterialManager::get()->addMaterial(pMaterials[i]);
			}
		}
	}

	
	//pScene->setBackground(i,&pMat);
	pScene->setBackground(i,pMaterials);

	int numBgrObnjects=0;
	if (item.hasInteger("numBgrObjects")){
		numBgrObnjects=item.getInteger("numBgrObjects");
	}

	GFXObject3D *pGfxObj;
	for (int i=0;i<numBgrObnjects;i++){
		string objName="BGR_OBJECT";
		char num[2];
		itoa(i,num,10);
		//_itoa_s(i,num,2,10);
		objName.append(num);

		handle = data.getItemHandle(objName);
		if (handle==ConfigData::INVALID_HANDLE){
			//bgr object not found
			continue;
		}
		ConfigItem bgrObjItem = *(data.getItem(handle));
		GFXObject3DLoader loader;
		pGfxObj=(GFXObject3D*)loader.load(bgrObjItem);
		if (pGfxObj){
			pScene->addGFXObject(pGfxObj);
		}
		

	}

	//---------------------------------------------------------------------------
	//parse lights
	//---------------------------------------------------------------------------

	int maxLights=8;		//not needed in the config file now; we'll probably have less lights

	LightLoader lightLoader;

	for (int i=0;i<maxLights;i++){
		string lightName="LIGHT";
		char num[2];
		itoa(i,num,10);
		//_itoa_s(i,num,2,10);
		lightName.append(num);

		handle = data.getItemHandle(lightName);

		if (handle!=ConfigData::INVALID_HANDLE){
			//light item found
			ConfigItem lightItem = *(data.getItem(handle));
			lightLoader.load(lightItem,i);	//light is loaded and added to the manager
		}
	}

	
	return pScene;
}

#endif