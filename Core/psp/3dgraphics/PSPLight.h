#pragma once
#include "../../3dgraphics/LightIF.h"

#ifdef _3D

#ifdef _SPSP

class PSPLight: public LightIF{
public:
	PSPLight(int id):LightIF(id){}
	~PSPLight(){}

	void applyLightParameters() const;
	void applyCoordinates() const;
	void enable() const;
	void disable() const;

	//void enableLighting() const;
	//void disableLighting() const;
};

#endif

#endif