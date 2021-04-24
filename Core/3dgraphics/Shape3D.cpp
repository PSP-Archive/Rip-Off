#ifdef _3D

#include "Shape3D.h"

void Shape3D::setName(const string& meshName){
	m_name=meshName;
}

bool Shape3D::hasName(const string& meshName) const{
	if (!m_name.compare(meshName)) return true;
	return false;
}

//const string& GFXObject3D::getName() const{
//	return m_name;
//}

#endif