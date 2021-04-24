#pragma once

//class used to render an explosion effect
//The EffectLoader can create such an effect from the
//config file, by specifying the type to "explosion".
//It represents a growing quad.
//The quad can also have inertia, if m_velocity (from EffectIF)
//is set.

#ifdef _3D

#include "../graphics/EffectIF.h"
#include "Icon3D.h"
#include "foundation/Timer.h"
#include "ExplosionEffect3DRenderer.h"

#include <vector>
using namespace std;

class ExplosionEffect3D: public EffectIF {
public:

	ExplosionEffect3D();
	~ExplosionEffect3D();

	// Renders the effect
	void Start();

	// Renders the effect
	void Render();

	// Updates the effect
	void Update();


	void setDuration(float duration);
	void addIcon(Icon3D* pIcon);

	void setWidth2(float maxWidth2);
	void setHeight2(float maxHeight2);

private:
	float m_duration, m_delta, m_maxWidth2, m_maxHeight2;
	Timer m_timer;
	vector<Icon3D*> m_vpIcons;
	Vector3f m_pos;
	Vector3f m_velocity3D;

	ExplosionEffect3DRenderer m_renderer;
};



//-----------------------------------------------------------------------------------------------





inline ExplosionEffect3D::ExplosionEffect3D():m_pos(0,0,0),
									  m_duration(2)
{
	//todo: delete the contents of this ctor; place it in the loader
	m_delta=0.3f;
}

inline ExplosionEffect3D::~ExplosionEffect3D(){
	vector<Icon3D*>::iterator it;
	for (it=m_vpIcons.begin(); it!=m_vpIcons.end();it++){
		delete (*it);
	}
	m_vpIcons.clear();
}


inline void ExplosionEffect3D::setWidth2(float maxWidth2){
	m_maxWidth2=maxWidth2;
}
inline void ExplosionEffect3D::setHeight2(float maxHeight2){
	m_maxHeight2=maxHeight2;
}

inline void ExplosionEffect3D::Start(){
	//m_pParticleSystem->initialize();
	
	m_pos[0]=getPosition().x;
	m_pos[1]=getPosition().y;
	m_velocity3D[0]=m_velocity.x/16.0f;
	m_velocity3D[1]=m_velocity.y/16.0f;
	m_velocity3D[2]=0.0f;
	
	m_timer.reset();
	//m_duration=2;
}


inline void ExplosionEffect3D::Render(){
	if(!isFinished()){
		
		const Vector3f v=MeshManager::get()->getCameraDirection();

		//draw the lightning
		assert(m_vpIcons.size()>0);
		m_renderer.applyTransforms(m_pos,m_delta,0);
		m_vpIcons[0]->renderGeometry(Vector3f(0,0,0));
		m_renderer.discardTransforms(0);

		//draw the spots
		/*vector<Icon3D*>::const_iterator it=m_vpIcons.begin();
		it++; int i=0;
		for(;it!=m_vpIcons.end();it++,i+=2){
			m_renderer.applyTransforms(m_pos,v,-getRotation(),0.2f+i*m_maxWidth2,0.0f,0);
			(*it)->renderGeometry(Vector3f(0,0,0));
			m_renderer.discardTransforms(0);
		}*/
		
	}
}

inline void ExplosionEffect3D::Update(){
	if (!isFinished()){
		float deltaT=m_timer.getFrameTime();
		m_timer.update();
		// Check if time expired
		if(m_timer.getTime() > m_duration)
		{
			terminate();
			return;
		}

		//std::vector<Icon3D>::iterator it=m_vpIcons.begin();
		//for (;it!=m_vpIcons.end();it++){
		//	it->se
		//}
		m_pos+=deltaT*m_velocity3D;
		m_delta+=m_maxWidth2*deltaT/m_duration;//0.01f;
		if (m_delta>1) m_delta=1;
	}
}


#endif