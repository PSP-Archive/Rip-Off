#ifdef _3D

#include "GFXEffect3D.h"

void GFXEffect3D::setDuration(float duration){
	m_duration=duration;
}
void GFXEffect3D::setParticleSystem(ParticleSystem* pParticleSystem){
	m_pParticleSystem=pParticleSystem;
}

#endif