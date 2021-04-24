#pragma once
#ifdef _3D

#include "foundation/Vector4f.h"
#include "MaterialRenderer.h"
#include "Texture.h"
#include <string>
//the class contains material data like colours and texture;
//it has a renderer who applies the colors according to the
//platform that is used.
//
//It will also have a m_texture member which is also platform dependent.

class Material{
private:
	std::string m_name;

	Vector4f m_ambient;
	Vector4f m_diffuse;
	Vector4f m_specular;
	Vector4f m_emissive;
	float m_shininess;
	
	int m_lightOn;

	Texture *m_pTexture;			//material will not delete or copy the contents of the texture;
									//the copy constr and destructor are left on default
	MaterialRenderer m_renderer;
	

public:
	Material();

	void setTexture(Texture *pTexture);
	void setName(const std::string& name);
	void setAmbient(const Vector4f& ambient);
	void setDiffuse(const Vector4f& diffuse);
	void setSpecular(const Vector4f& specular);
	void setEmissive(const Vector4f& emissive);
	void setShininess(float shininess);
	void setLightOn(int lightOn);

	//returnes true if it has the name given as input param.
	bool hasName(const std::string& name) const;

	void apply() const;
	void dismiss() const;
};

inline void Material::apply() const{
	if (m_lightOn)
		m_renderer.apply(m_ambient, m_diffuse, m_specular, m_emissive, m_shininess);
	else
		m_renderer.applyNoLighting(m_diffuse);
	if (m_pTexture)
		m_pTexture->apply();

}

inline void Material::dismiss() const{
	if (m_lightOn)
		m_renderer.dismiss();
	else m_renderer.dismissNoLighting();
	if (m_pTexture)
		m_pTexture->dismiss();
}

#endif