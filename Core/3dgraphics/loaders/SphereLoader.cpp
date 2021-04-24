#ifdef _3D

#include "SphereLoader.h"
#include "../managers/MaterialManager.h"
#include "../managers/MeshManager.h"


Shape3D* SphereLoader::load(const ConfigItem& item, Material **ppMaterial) const{
	Sphere *pSphere=new Sphere();

	if (item.hasString("name")){
		string name=item.getString("name");
		pSphere->setName(item.getString("name"));
	}

	if (item.hasFloat("radius")){
		pSphere->setRadius(item.getFloat("radius"));
	}
	
	if (item.hasInteger("stacks")){
		pSphere->setStacks(item.getInteger("stacks"));
	}
	if (item.hasInteger("slices")){
		pSphere->setSlices(item.getInteger("slices"));
	}
	if (!pSphere->create()){
		delete pSphere;
		return NULL;
	}

	string matName;
	if (item.hasString("material")){
		matName=item.getString("material");
	}
	(*ppMaterial)=MaterialManager::get()->hasMaterial(matName);
	if (!(*ppMaterial)){
		(*ppMaterial)=MaterialManager::get()->hasMaterial("defMaterial");
		if (!(*ppMaterial)) {
			(*ppMaterial)=new Material();
			(*ppMaterial)->setName("defMaterial");
			MaterialManager::get()->addMaterial((*ppMaterial));
		}
	}
	//pSphere->setMaterial(pMat);

	MeshManager::get()->addMesh(pSphere);

	return pSphere;
}

#endif