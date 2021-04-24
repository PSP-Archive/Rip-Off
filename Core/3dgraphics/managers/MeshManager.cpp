#ifdef _3D

#include "MeshManager.h"


BaseMeshManager::~BaseMeshManager(){
	vector<Shape3D*>::iterator it=m_vpMeshes.begin();
	for(;it!=m_vpMeshes.end();it++){
		delete (*it);
	}
	m_vpMeshes.clear();
}

void BaseMeshManager::addMesh(Shape3D *pObject){
	m_vpMeshes.push_back(pObject);
}

Shape3D* BaseMeshManager::hasMesh(const std::string &meshName) const{
	vector<Shape3D*>::const_iterator it=m_vpMeshes.begin();
	for(;it!=m_vpMeshes.end();it++){
		//if (!((*it)->getName().compare(meshName)))
		if ((*it)->hasName(meshName))
			return (*it);
	}
	return NULL;
}

void BaseMeshManager::setScalingFactor(float scalingFactor){
	m_scalingFactor=scalingFactor;
}

void BaseMeshManager::setCameraAlignment(const Vector3f& right, const Vector3f& up, const Vector3f& direction){
	m_cameraRight=right;
	m_cameraVup=up;
	m_cameraDirection=direction;
}

#endif