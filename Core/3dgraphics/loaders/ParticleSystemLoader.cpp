#ifdef _3D

#include "ParticleSystemLoader.h"
#include "../managers/MaterialManager.h"


ParticleSystem* ParticleSystemLoader::load(const ConfigItem& item) const{
	ParticleSystem *pParticleSystem=new ParticleSystem();
	
	if (item.hasVector("direction")){
		pParticleSystem->setDirection(item.getVector("direction"));
	}

	if (item.hasFloat("emissionRate")){
		pParticleSystem->setEmissionRate(item.getFloat("emissionRate"));
	}
	Vector3f vMin, vMax;
	if (item.hasVector("maxVelocity")){
		vMax=item.getVector("maxVelocity");
	}
	if (item.hasVector("minVelocity")){
		vMin=item.getVector("minVelocity");
	}
	
	pParticleSystem->setVelocityX(vMin.x(),vMax.x());
	pParticleSystem->setVelocityY(vMin.y(),vMax.y());
	pParticleSystem->setVelocityZ(vMin.z(),vMax.z());

	if (item.hasVector("lifeMinMax")){
		Vector3f v=item.getVector("lifeMinMax");
		pParticleSystem->setLife(v.x(),v.y());
	}

	if (item.hasVector("sizeMinMaxX")){
		Vector3f v=item.getVector("sizeMinMaxX");
		pParticleSystem->setSizeMinMaxX(v.x(),v.y());	
	}
	if (item.hasVector("sizeMinMaxY")){
		Vector3f v=item.getVector("sizeMinMaxY");
		pParticleSystem->setSizeMinMaxY(v.x(),v.y());	
	}
	
	if (item.hasString("material")){
		//string name=item.getString("material");
		Material *pMat=MaterialManager::get()->hasMaterial(item.getString("material"));
		if (!pMat)
			pMat=MaterialManager::get()->hasMaterial("defMaterial");
		if (!pMat){
			pMat=new Material();
			pMat->setName("defMaterial");
			MaterialManager::get()->addMaterial(pMat);
		}
		pParticleSystem->setMaterial(pMat);
	}

	if (item.hasInteger("bitsShifted")){
		pParticleSystem->setBitsShifted(item.getInteger("bitsShifted"));
	}
	if (item.hasInteger("numSamples")){
		pParticleSystem->setNumSamples(item.getInteger("numSamples"));
	}

	pParticleSystem->initialize();//createParticles();
	
	return pParticleSystem;
}

#endif