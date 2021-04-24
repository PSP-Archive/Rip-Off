#include "Material.h"
#ifdef _3D

Material::Material(): m_ambient(0.0f,0.0f,0.0f,0.0f),
					  m_diffuse(1.0f,1.0f,1.0f,1.0f),
					  m_specular(0.0f,0.0f,0.0f,0.0f),
					  m_emissive(0.0f,0.0f,0.0f,0.0f),
					  m_shininess(0.0f),
					  m_lightOn(1),
					  m_pTexture(NULL)
{}

void Material::setTexture(Texture *pTexture){
	m_pTexture=pTexture;
}

void Material::setName(const std::string& name){
	m_name=name;
}

void Material::setAmbient(const Vector4f& ambient){
	m_ambient=ambient;
}

void Material::setDiffuse(const Vector4f& diffuse){
	m_diffuse=diffuse;
}

void Material::setSpecular(const Vector4f& specular){
	m_specular=specular;
}

void Material::setEmissive(const Vector4f& emissive){
	m_emissive=emissive;
}

void Material::setShininess(float shininess){
	m_shininess=shininess;
}

void Material::setLightOn(int lightOn){
	m_lightOn=lightOn;
}


bool Material::hasName(const std::string& name) const{
	if (!m_name.compare(name)) return true;
	return false;
}


#endif