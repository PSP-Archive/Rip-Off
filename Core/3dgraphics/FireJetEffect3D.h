#pragma once

#pragma once
#ifdef _3D

#include "../graphics/EffectIF.h"
#include "foundation/Timer.h"
#include "managers/MeshManager.h"

#include "ParticleSystem.h"

class FireJetEffect3D:public EffectIF{
public:
	FireJetEffect3D():m_pParticleSystem(NULL),
				 m_offset(0)
					{}
	~FireJetEffect3D(){ 
		delete m_pParticleSystem; 
	}
	// Renders the effect
	void Start();

	// Renders the effect
	void Render();

	// Updates the effect
	void Update();

	void Kill();


	void setDuration(float duration);
	void setParticleSystem(ParticleSystem* pParticleSystem);
	void setOffset(float offset);
	

private:
	float m_duration, m_offset;
	Timer m_timer;
	ParticleSystem *m_pParticleSystem;
	float m_scalingFactor;
};


inline void FireJetEffect3D::Kill(){
	m_pBody=NULL;
	m_pParticleSystem->setEmissionRate(0);
}

inline void FireJetEffect3D::Start(){
	//m_scalingFactor=MeshManager::get()->getScalingFactor();;
	Vector3f pos;
	pos[0]=getPosition().x;//*m_scalingFactor;
	pos[1]=getPosition().y;//*m_scalingFactor;
	pos[2]=0.001f;
	if (m_pParticleSystem){
		m_pParticleSystem->setAligned(true);
		float angle=(getRotation())*DegRad;
		Vector3f dir(cosf(angle),sinf(angle),0);
		m_pParticleSystem->setEmitter(pos);
		//m_pParticleSystem->setVelocity(Vector2f(0,0));
		//m_pParticleSystem->setParticleVelocity(-getVelocity());
		m_pParticleSystem->updateEmitter(dir,m_offset);	
		m_pParticleSystem->setDirection(-dir);
		//m_pParticleSystem->setDirection(Vector3f(cosf(angle),sinf(angle),0));
		m_pParticleSystem->update(0);

	}
	
	m_timer.reset();
}


inline void FireJetEffect3D::Render(){
	if(m_pParticleSystem && !isFinished()){
		m_pParticleSystem->render();
	}
}
inline void FireJetEffect3D::Update(){
	if (!isFinished()){
		float deltaT=m_timer.getFrameTime();
		m_timer.update();
		// Check if time expired
		if(m_timer.getTime() > m_duration)
		{
			//m_pBody->setEffect(NULL);
			//m_pBody=NULL;
			terminate();
			return;
		}

		//------------------------------------------------
		if (m_pBody){
			Vector3f pos;
			pos[0]=m_pBody->getPosition().x;//*0.9f;//m_scalingFactor;
			pos[1]=m_pBody->getPosition().y;//*0.9f;//m_scalingFactor;
			pos[2]=0.001f;
			float angle=(m_pBody->getRotation())*DegRad;
			Vector3f dir(cosf(angle),sinf(angle),0);
			m_pParticleSystem->setDirection(-dir);
			m_pParticleSystem->setEmitter(pos);
			//m_pParticleSystem->setVelocity(-m_pBody->getVelocity());
			//m_pParticleSystem->setParticleVelocity(-m_pBody->getVelocity());
		}
		//------------------------------------------------
		if (m_pParticleSystem)
			m_pParticleSystem->update(deltaT);
		
	}
}

inline void FireJetEffect3D::setOffset(float offset){
	m_offset=offset;
}




#endif