#ifdef _3D

#include "ExplosionEffect3D.h"

void ExplosionEffect3D::setDuration(float duration){
	m_duration=duration;
}
void ExplosionEffect3D::addIcon(Icon3D* pIcon){
	m_vpIcons.push_back(pIcon);
}

#endif