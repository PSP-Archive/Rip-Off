#ifdef _3D

#include "LaserEffect3D.h"

void LaserEffect3D::setDuration(float duration){
	m_duration=duration;
}
void LaserEffect3D::addIcon(Icon3D* pIcon){
	m_vpIcons.push_back(pIcon);
}

#endif