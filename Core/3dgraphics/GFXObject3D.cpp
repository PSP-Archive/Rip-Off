#include "GFXObject3D.h"

#ifdef _3D

GFXObject3D::GFXObject3D():m_pMaterial(NULL),
							m_pIcon(NULL),
							m_pIconBack(NULL)
{}

GFXObject3D::~GFXObject3D(){
	delete m_pIcon;
	delete m_pIconBack;
}

void GFXObject3D::setMaterial(const Material* pMaterial){
	m_pMaterial=pMaterial;
}

void GFXObject3D::render(const Vector2f& position, float angle) const{
	
	//if (!m_pShape) return;
	
	if (m_pIconBack)
		m_pIconBack->renderGeometry(Vector3f(position.x,position.y,getCentre().z()),angle);

	/*if (m_pMaterial) 
		m_pMaterial->apply();
	
	m_positioner.applyTransforms(position,angle);
	m_pShape->renderGeometry();
	m_positioner.resetTransforms();

	if (m_pMaterial) 
		m_pMaterial->dismiss();
	*/
	if (m_pIcon)
		m_pIcon->renderGeometry(Vector3f(position.x,position.y,getCentre().z()),angle);

	
}

void GFXObject3D::setCentre(const Vector3f& centre){
	m_centre=centre;
	//m_positioner.setZ(m_centre.z());
}

void GFXObject3D::setShape(Shape3D* pShape){
	m_pShape=pShape;
}

void GFXObject3D::setIcon(Icon3D *pIcon){
	m_pIcon=pIcon;
}

void GFXObject3D::setIconBack(Icon3D *pIcon){
	m_pIconBack=pIcon;
}


const Vector3f& GFXObject3D::getCentre() const{
	return m_centre;
}



#endif




