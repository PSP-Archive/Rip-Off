#pragma once
#ifdef _3D


#include "../foundation/Vector3f.h"
#include "../foundation/Vector2f.h"
#include "../foundation/PSPHeap.h"
#include <vector>
#include "Particle.h"

#include "Material.h"
#include "VAObject.h"

class ParticleSystem{




public:
	ParticleSystem();
	~ParticleSystem();

	void initialize();	
	void update(float deltaT);
	void render() const;


	void setEmitter(const Vector3f& emitter);
	//the current velocity of the ship when the effect has been spawned (for updating the emitter)
	void setVelocity(const Vector2f& velocity);
	//set the velocity component of the particles resulted from the motion of the object
	void setParticleVelocity(const Vector2f& velocity);

	void updateEmitter(const Vector3f& dir, float offset);
	void setDirection(const Vector3f& direction);
	void setEmissionRate(unsigned int emissionRate);
	void setVelocityX(float velocityXMin, float velocityXMax);
	void setVelocityY(float velocityYMin, float velocityYMax);
	void setVelocityZ(float velocityZMin, float velocityZMax);
	void setSizeMinMaxX(float minX, float maxX);
	void setSizeMinMaxY(float minY, float maxY);
	void setLife(float lifeMin, float lifeMax);
	void setForce(const Vector3f& force);
	void setMaterial(Material* pMaterial);
	void setBitsShifted(int bitsShifted);
	void setNumSamples(int numSamples);
	void setAligned(bool bAligned);

private:
	//at each frame, the particle system will emit new particles, and update the 
	//internal structures containing the positions/tex coords
	void updateArrays(float deltaT);
	void emitParticles(float deltaT);

	ParticleSystem(const ParticleSystem& rhs);
	ParticleSystem& operator = (const ParticleSystem& rhs);


private:
	Vector3f m_emitterDisplacement;
	Vector3f m_emitter;
	Vector3f m_velocity;			//the velocity of the emitter
	Vector3f m_particleVelocity;	//the motion velocity component of the particles

	Vector3f m_direction;		//the direction of emission; velocityMin/Max of a particle will
								//deviate from this direction with the amount specified
	Vector3f m_force;
	Vector2f m_sizeMinMaxX;
	Vector2f m_sizeMinMaxY;

	float m_accum;

	unsigned int m_numParticles;		//maxLife*emissionRate
	unsigned int m_emissionRate;
	float m_lifeMin, m_lifeMax;
	float m_velocityXMin, m_velocityXMax;
	float m_velocityYMin, m_velocityYMax;
	float m_velocityZMin, m_velocityZMax;
	int m_bitsShifted, m_numSamples;
	bool m_aligned;

	Material *m_pMaterial;
	std::vector<Particle> m_particles;
	

	float *m_vfArray;//, *m_gfxVfArray;
	int m_vfSize;
	unsigned short *m_indicesArray;

	VAObject m_vaObject;


};


inline void ParticleSystem::setAligned(bool bAligned){
	m_aligned=bAligned;
}

inline void ParticleSystem::update(float deltaT){
	m_accum+=deltaT;
	if (m_accum>0.015f){
		emitParticles(0.015f);
		updateArrays(0.015f);
		m_accum=0.0f;
	}
}

inline void ParticleSystem::setVelocity(const Vector2f& velocity){
	m_velocity[0]=velocity.x;
	m_velocity[1]=velocity.y;
	m_velocity[2]=0.0f;
}

inline void ParticleSystem::setParticleVelocity(const Vector2f& velocity){
	m_particleVelocity[0]=velocity.x;
	m_particleVelocity[1]=velocity.y;
	m_particleVelocity[2]=0.0f;
}

#include <libgu.h>
#include <libgum.h>
#include <kernel.h>

inline void ParticleSystem::render() const{
	if (m_pMaterial) m_pMaterial->apply();
	sceGuBlendFunc(SCEGU_ADD,SCEGU_SRC_ALPHA, SCEGU_FIX_VALUE,0x00000000,0xffffffff);
	//sceGuDisable(SCEGU_DEPTH_TEST);
	sceGuDepthMask(1);
	sceGuDisable(SCEGU_CULL_FACE);
	
	
	
	unsigned int m_size=20*m_particles.size()*sizeof(float);
	float* pGfxVff=(float*)sceGuGetMemory(m_size);
	memcpy(pGfxVff,m_vfArray,m_size);
	m_vaObject.render(pGfxVff,m_indicesArray,6*m_particles.size(),0,TRIANGLES);

	
	sceGuBlendFunc(SCEGU_ADD,SCEGU_SRC_ALPHA, SCEGU_ONE_MINUS_SRC_ALPHA,0x00000000,0x00000000);
	if (m_pMaterial) m_pMaterial->dismiss();
	sceGuEnable(SCEGU_DEPTH_TEST);
	sceGuDepthMask(0);
}

//------------------------------------------------------------------------------------
//setters
//------------------------------------------------------------------------------------


inline void ParticleSystem::setMaterial(Material* pMaterial){
	m_pMaterial=pMaterial;
}

inline void ParticleSystem::setEmitter(const Vector3f& emitter){
	m_emitter=emitter;
}

inline void ParticleSystem::updateEmitter(const Vector3f& dir, float offset){
	m_emitter+=dir*offset;
}

inline void ParticleSystem::setDirection(const Vector3f& direction){
	m_direction=direction;
}
inline void ParticleSystem::setEmissionRate(unsigned int emissionRate){
	m_emissionRate=emissionRate;
	//m_minEmissionRate=m_emissionRate>>1;
}
inline void ParticleSystem::setVelocityX(float velocityXMin, float velocityXMax){
	m_velocityXMin=velocityXMin;
	m_velocityXMax=velocityXMax;
}
inline void ParticleSystem::setVelocityY(float velocityYMin, float velocityYMax){
	m_velocityYMin=velocityYMin;
	m_velocityYMax=velocityYMax;
}
inline void ParticleSystem::setVelocityZ(float velocityZMin, float velocityZMax){
	m_velocityZMin=velocityZMin;
	m_velocityZMax=velocityZMax;
}

inline void ParticleSystem::setSizeMinMaxX(float minX, float maxX){
	m_sizeMinMaxX=Vector2f(minX,maxX);
}
inline void ParticleSystem::setSizeMinMaxY(float minY, float maxY){
	m_sizeMinMaxY=Vector2f(minY,maxY);
}
	

inline void ParticleSystem::setLife(float lifeMin, float lifeMax){
	m_lifeMin=lifeMin;
	m_lifeMax=lifeMax;
}
inline void ParticleSystem::setForce(const Vector3f& force){
	m_force=force;
}

inline void ParticleSystem::setBitsShifted(int bitsShifted){
	m_bitsShifted=bitsShifted;
}
inline void ParticleSystem::setNumSamples(int numSamples){
	m_numSamples=numSamples;
}

#endif