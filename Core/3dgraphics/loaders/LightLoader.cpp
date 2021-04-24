#ifdef _3D
#include "LightLoader.h"
#include "../managers/LightManager.h"


Light* LightLoader::load(const ConfigItem& item, int lightId){
	Light *pLight=new Light(lightId);

	float omni=1;
	if (item.hasVector("position")){
		Vector3f v=item.getVector("position");
		if (item.hasFloat("omni")){
			omni=item.getFloat("omni");		//place 0 here if you wish directional light
		}
		pLight->setCoordinates(Vector4f(v.x(),v.y(),v.z(),omni));
	}

	if (item.hasVector("diffuse")){
		Vector3f v=item.getVector("diffuse");
		pLight->setDiffuse(Vector4f(v.x(),v.y(),v.z(),1));
	}
	if (item.hasVector("ambient")){
		Vector3f v=item.getVector("ambient");
		pLight->setAmbient(Vector4f(v.x(),v.y(),v.z(),1));
	}
	if (item.hasVector("specular")){
		Vector3f v=item.getVector("specular");
		pLight->setSpecular(Vector4f(v.x(),v.y(),v.z(),1));
	}
	if (item.hasInteger("isEnabled")){
		pLight->setIsEnabled(item.getInteger("isEnabled"));
	}

	if (pLight) LightManager::get()->addLight(pLight);

	return pLight;
}

#endif