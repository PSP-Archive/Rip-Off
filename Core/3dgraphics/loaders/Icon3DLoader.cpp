#ifdef _3D

#include "Icon3DLoader.h"
#include "foundation/PSPHeap.h"
#include "../managers/MaterialManager.h"
#include "../Icon3D.h"
#include <stdlib.h>


Icon3D* Icon3DLoader::load(const ConfigItem& item, int id, bool isBack) const{
	Icon3D *pIcon;

	string attrName("iconMaterial");
	if (id){
		char num[3];
		itoa(id,num,10);
		//_itoa_s(id,num,3,10);
		attrName.append("_");
		attrName.append(num);
	}

	string matName;
	if (item.hasString(attrName) && !isBack){
		matName=item.getString(attrName);
	}else if (item.hasString("iconMaterialBack")){
		matName=item.getString("iconMaterialBack");
	}
	
	
	
	pIcon=new Icon3D();

	Material* pMat=MaterialManager::get()->hasMaterial(matName);
	if (!pMat)
		pMat=MaterialManager::get()->hasMaterial("defMaterial");
	if (!pMat){
		pMat=new Material();
		pMat->setName("defMaterial");
		MaterialManager::get()->addMaterial(pMat);
	}

	pIcon->setMaterial(pMat);
	

	string w2("iconWidth2"),h2("iconHeight2");
	if (isBack) {
		w2.append("_b");
		h2.append("_b");
	}
	if (id){
		char num[3];
		itoa(id,num,10);
		//_itoa_s(id,num,3,10);
		w2.append("_");
		w2.append(num);

		h2.append("_");
		h2.append(num);
	}

	if (item.hasFloat(w2))
		pIcon->setWidth2(item.getFloat(w2));
	if (item.hasFloat(h2))
		pIcon->setHeight2(item.getFloat(h2));

	pIcon->create(Vector3f(1,0,0),Vector3f(0,1,0),VFF_VERTEX3|VFF_TEX2);
	
	return pIcon;
}

#endif