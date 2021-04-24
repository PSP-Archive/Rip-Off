#pragma once
#ifdef _3D

#include "foundation/Vector4f.h"



enum LightType{
	OMNI=0,
	DIRECTIONAL,
	SPOT
};

class LightIF{
protected:
	LightType m_type;
	int m_id;
	int m_isEnabled;

	Vector4f m_ambient;
	Vector4f m_diffuse;
	Vector4f m_specular;

	Vector4f m_position;		//the last coordinate indicates if it is a directional light or not
								//0=is directional, 1=is omni in openGL
	Vector3f m_direction;

	float m_linearAtt;		//attenuation params
	float m_quadricAtt;

public:

	LightIF(int id);
	virtual ~LightIF(){};

	//------------------------------------------------------------------------------------------
	//setters
	void setType(LightType type);

	void setAmbient(const Vector4f& ambient);
	
	void setDiffuse(const Vector4f& diffuse);
	
	void setSpecular(const Vector4f& specular);

	//position is a vec4f: if w=0 light is directional, if w=1 is omnidirectional;
	void setCoordinates(const Vector4f& position, const Vector3f& direction=Vector3f(0,0,0));
	
	void setAttenuation(float linear, float quadric);

	void setIsEnabled(int isEnabled);
	//------------------------------------------------------------------------------------------
	
	//apply position or direction at each frame, after the camera transforms
	virtual void applyCoordinates() const=0;

	//apply parameters like color, attenuation, at initialization time
	virtual void applyLightParameters() const=0;

	//enable/disable this light
	virtual void enable() const=0;
	virtual void disable() const=0;

};

#endif