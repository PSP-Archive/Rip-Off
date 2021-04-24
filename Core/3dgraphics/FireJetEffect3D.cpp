#ifdef _3D

#include "FireJetEffect3D.h"

void FireJetEffect3D::setDuration(float duration){
	m_duration=duration;
}
void FireJetEffect3D::setParticleSystem(ParticleSystem* pParticleSystem){
	m_pParticleSystem=pParticleSystem;
}

#endif