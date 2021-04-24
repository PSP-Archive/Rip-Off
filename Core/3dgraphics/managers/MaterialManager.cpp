#include "MaterialManager.h"
#ifdef _3D

BaseMaterialManager::~BaseMaterialManager(){
	clear();
}
void BaseMaterialManager::addMaterial(Material *pMaterial){
	m_vpMaterials.push_back(pMaterial);
	//m_vpMaterials.add(pMaterial);
}

Material* BaseMaterialManager::hasMaterial(const string& name) const{
	//iterate through all the array and check the name
	vector<Material*>::const_iterator it=m_vpMaterials.begin();
	for (;it!=m_vpMaterials.end();it++){
		if ((*it)->hasName(name)) return *it;
	}
	return NULL;
}

void BaseMaterialManager::clear(){
	vector<Material*>::iterator it=m_vpMaterials.begin();
	for(;it!=m_vpMaterials.end();it++){
		delete (*it);
	}
	m_vpMaterials.clear();
}

#endif