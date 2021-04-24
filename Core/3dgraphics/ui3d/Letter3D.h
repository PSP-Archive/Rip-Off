#pragma once

#ifdef _3D

#include "../Icon3D.h"
#include "foundation/Vector3f.h"

class Letter3D{

public:
	Letter3D();

	void setTexCoords(float texCoords[]);
	void setScale(float scale) const;	//hack to fit in a const function
	void setWidth(float width);
	void setHeight(float height);
	void setMaterial(Material* pMat);
	void create();

	void render() const;

private:
	mutable Icon3D m_icon;
	float m_width, m_height;
	mutable float m_scale; //hack to fit in a const function (tex3D render)


};

inline void Letter3D::create(){
	m_icon.setWidth2(m_width*m_scale);
	m_icon.setHeight2(m_height*m_scale);
	m_icon.create(Vector3f(1,0,0),Vector3f(0,1,0),VFF_VERTEX3|VFF_TEX2);

}

inline void Letter3D::setTexCoords(float texCoords[]){
	m_icon.setTextureCoordinates(texCoords);
}

inline void Letter3D::setScale(float scale) const{
	m_scale=scale;
}

inline void Letter3D::setWidth(float width){
	m_width=width;
}

inline void Letter3D::setHeight(float height){
	m_height=height;
}

inline void Letter3D::setMaterial(Material* pMat){
	m_icon.setMaterial(pMat);
}

inline void Letter3D::render() const{
	m_icon.setNextIconDisplacement(m_width*m_scale);
	m_icon.setWidth2(m_width*m_scale);
	m_icon.setHeight2(m_height*m_scale);
	m_icon.resetMeshNoTexCoords();
	m_icon.renderGeometry(Vector3f(0,0,0));
	m_icon.setNextIconDisplacement(m_width*m_scale); //+0.01);
}

#endif