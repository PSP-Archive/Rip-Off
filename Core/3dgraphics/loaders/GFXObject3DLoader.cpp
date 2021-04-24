#include "GFXObject3DLoader.h"

#ifdef _3D

#include "Model3DLoader.h"
#include "SphereLoader.h"
#include "Icon3DLoader.h"
#include "../managers/MaterialManager.h"
#include "../GFXObject3D.h"

GFXObject* GFXObject3DLoader::load(const ConfigItem& item) const{
	GFXObject* pGFXObject=NULL;
	Vector3f centre(0.0f,0.0f,0.0f);

	if(item.hasString("model")){
		//the shape will be a model
		
		string fileName=item.getString("model");
		float radius=0.1;
		if (item.hasFloat("radius")){
			radius=item.getFloat("radius");
		}
		if (item.hasVector("centre")){
			centre=item.getVector("centre");
		}

		Model3DLoader modelLoader;
		Material **ppMat=new Material* ();
		Shape3D *pShape=(Shape3D*)modelLoader.load(fileName,radius,ppMat);
		if (!pShape) return NULL;

		pGFXObject=new GFXObject3D();
		((GFXObject3D*)pGFXObject)->setShape(pShape);
		
		if (pGFXObject && item.hasString("material")){
			*ppMat=MaterialManager::get()->hasMaterial(item.getString("material"));
			if (!(*ppMat))
				(*ppMat)=MaterialManager::get()->hasMaterial("defMaterial");
			if (!(*ppMat)){
				(*ppMat)=new Material();
				(*ppMat)->setName("defMaterial");
				MaterialManager::get()->addMaterial(*ppMat);
			}
		}

		if (*ppMat) ((GFXObject3D*)pGFXObject)->setMaterial(*ppMat);
		delete ppMat;

	}else{
		string type;
		if (item.hasString("type")){
			type=item.getString("type");
		}else return NULL;
		
		if (!type.compare("sphere")){
			SphereLoader sphereLoader;

			if (item.hasVector("centre")){
				centre=item.getVector("centre");
			}

			Material **ppMat = new Material * ();
			(*ppMat)=NULL;
			pGFXObject=new GFXObject3D();

			Shape3D *pShape=(Shape3D*)sphereLoader.load(item,ppMat);
			if (!pShape) {
				delete (*ppMat);
				delete ppMat;
				delete pGFXObject;
				return NULL;
			}
			
			((GFXObject3D*)pGFXObject)->setShape(pShape);
			if (*ppMat) ((GFXObject3D*)pGFXObject)->setMaterial(*ppMat);
			delete ppMat;
		}
	}

	//if object not created exit (otherwise look for icons on the shapes)
	if (pGFXObject){
		((GFXObject3D*)pGFXObject)->setCentre(centre);
	}else{
		pGFXObject=new GFXObject3D();
	}
	//if (!pGFXObject) return NULL;
	//((GFXObject3D*)pGFXObject)->setCentre(centre);


	Icon3D *pIcon=NULL;
	if (item.hasString("iconMaterial")){
		Icon3DLoader iconLoader;
		pIcon=iconLoader.load(item);
		((GFXObject3D*)pGFXObject)->setIcon(pIcon);
	}

	if (item.hasString("iconMaterialBack")){
		Icon3DLoader iconLoader;
		pIcon=iconLoader.load(item,0,true);
		((GFXObject3D*)pGFXObject)->setIconBack(pIcon);
	}
	
	return pGFXObject;
}

Material* GFXObject3DLoader::loadMaterial(const ConfigItem& item) const{
	Material *pMat=MaterialManager::get()->hasMaterial("defMaterial");
	if (!pMat){
		pMat=new Material();
		pMat->setName("defMaterial");
		MaterialManager::get()->addMaterial(pMat);
	}
	return pMat;
}
Texture* GFXObject3DLoader::loadTexture(const ConfigItem& item) const{
	return NULL;
}

#endif