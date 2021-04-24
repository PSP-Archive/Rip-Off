#pragma once
#ifdef _3D

#include "../graphics/EffectIF.h"
#include "foundation/Timer.h"

#include "ParticleSystem.h"
#include "Icon3D.h"

class GFXEffect3D:public EffectIF{
public:
	GFXEffect3D():m_pParticleSystem(NULL),
				 m_offset(0)
					{}
	~GFXEffect3D(){ 
		delete m_pParticleSystem; 
		//delete m_pIcon;
	}
	// Renders the effect
	void Start();

	// Renders the effect
	void Render();

	// Updates the effect
	void Update();


	void setDuration(float duration);
	void setParticleSystem(ParticleSystem* pParticleSystem);
	void setOffset(float offset);
	

private:
	float m_duration, m_offset;
	Timer m_timer;
	ParticleSystem *m_pParticleSystem;
	
};


#include "managers/MeshManager.h"

inline void GFXEffect3D::Start(){
	Vector3f pos;
	pos[0]=getPosition().x;
	pos[1]=getPosition().y;
	
	if (m_pParticleSystem){
		float angle=(getRotation())*DegRad;
		Vector3f dir(cosf(angle),sinf(angle),0);
		m_pParticleSystem->setEmitter(pos);
		m_pParticleSystem->setVelocity(0.2f*getVelocity());
		m_pParticleSystem->setParticleVelocity(-1.0f*getVelocity());
		m_pParticleSystem->updateEmitter(dir,m_offset);	
		m_pParticleSystem->setDirection(dir);
		//m_pParticleSystem->setDirection(Vector3f(cosf(angle),sinf(angle),0));
		m_pParticleSystem->update(0);
	}
	
	m_timer.reset();
}


inline void GFXEffect3D::Render(){
	if(m_pParticleSystem && !isFinished()){
		m_pParticleSystem->render();
	}
}
inline void GFXEffect3D::Update(){
	if (!isFinished()){
		float deltaT=m_timer.getFrameTime();
		m_timer.update();
		// Check if time expired
		if(m_timer.getTime() > m_duration)
		{
			terminate();
			return;
		}
		if (m_pParticleSystem)
			m_pParticleSystem->update(deltaT);

	}
}

inline void GFXEffect3D::setOffset(float offset){
	m_offset=offset;
}




#endif