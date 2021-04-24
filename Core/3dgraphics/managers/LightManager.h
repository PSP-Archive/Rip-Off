#pragma once
#ifdef _3D

#include <vector>
#include "../Light.h"
#include "foundation/Singleton.h"
using namespace std;

class BaseLightManager{
	
private:
	vector<Light*> m_vpLights;

public:

	BaseLightManager(){}

	BaseLightManager(const BaseLightManager& rhs);
	const BaseLightManager& operator = (const BaseLightManager& rhs);
	
	~BaseLightManager();

	void addLight(Light *pLight);
	
	int hasLights() const;


	void initLightsForRendering() const;
	void renderLights() const;
	

};

typedef Singleton<BaseLightManager> LightManager;

#endif