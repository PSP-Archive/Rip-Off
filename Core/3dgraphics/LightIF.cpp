#ifdef _3D

#include "LightIF.h"

LightIF::LightIF(int id):m_id(id), 
				  m_type(OMNI),
				  m_position(0,0,0,1),
				  m_direction(0,0,0),
				  m_diffuse(1,1,1,1),
				  m_ambient(0,0,0,0),
				  m_specular(0,0,0,0),
				  m_linearAtt(0),
				  m_quadricAtt(0),
				  m_isEnabled(1)
{}

void LightIF::setAmbient(const Vector4f& ambient){
	m_ambient=ambient;
}

void LightIF::setDiffuse(const Vector4f& diffuse){
	m_diffuse=diffuse;
}

void LightIF::setSpecular(const Vector4f& specular){
	m_specular=specular;
}

void LightIF::setCoordinates(const Vector4f& position, const Vector3f& direction){
	m_position=position;
	m_direction=direction;
}

void LightIF::setAttenuation(float linear, float quadric){
	m_linearAtt=linear;
	m_quadricAtt=quadric;
}

void LightIF::setIsEnabled(int isEnabled){
	m_isEnabled=isEnabled;
}

#endif