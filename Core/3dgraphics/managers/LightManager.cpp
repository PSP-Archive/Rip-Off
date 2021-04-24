#ifdef _3D
#include "LightManager.h"


BaseLightManager::BaseLightManager(const BaseLightManager& rhs){
	m_vpLights.clear();
	vector<Light*>::const_iterator it=rhs.m_vpLights.begin();
	for (;it!=rhs.m_vpLights.end();it++){
		addLight(*it);
	}
}
const BaseLightManager& BaseLightManager::operator = (const BaseLightManager& rhs){
	m_vpLights.clear();
	vector<Light*>::const_iterator it=rhs.m_vpLights.begin();
	for (;it!=rhs.m_vpLights.end();it++){
		addLight(*it);
	}
	return *this;
}

void BaseLightManager::addLight(Light *pLight){
	m_vpLights.push_back(pLight);
}

BaseLightManager::~BaseLightManager(){
	vector<Light*>::iterator it=m_vpLights.begin();
	for (;it!=m_vpLights.end();it++){
		delete *it;
		//Light *pLight=*it;
		//delete pLight;
	}
	m_vpLights.clear();
}


int BaseLightManager::hasLights() const{
	return (int)m_vpLights.size();
}

void BaseLightManager::renderLights() const{
	vector<Light*>::const_iterator it=m_vpLights.begin();
	for (;it!=m_vpLights.end();it++){
		(*it)->applyCoordinates();
	}
}

void BaseLightManager::initLightsForRendering() const{
	if (m_vpLights.size()==0) return;

	vector<Light*>::const_iterator it=m_vpLights.begin();
	for (;it!=m_vpLights.end();it++){
		(*it)->enable();
		(*it)->applyLightParameters();
	}
}


#endif