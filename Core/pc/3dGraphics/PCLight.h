#pragma once
#include "../../3dgraphics/LightIF.h"

#ifdef _3D

#ifdef _PC

class PCLight: public LightIF{
public:
	PCLight(int id):LightIF(id){}
	~PCLight(){}

	void applyLightParameters() const;
	void applyCoordinates() const;
	void enable() const;
	void disable() const;

	//void enableLighting() const;
	//void disableLighting() const;
};

#endif

#endif
