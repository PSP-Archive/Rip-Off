#ifdef _3D

#include "ParticleSystem.h"
#include "managers/MeshManager.h"
#include "managers/RandomHashTable.h"



ParticleSystem::ParticleSystem():m_lifeMin(0.5f),
								m_lifeMax(1),
								m_direction(1,0,0),
								m_emitter(0,0,0), 
								m_force(0,0,-0.01),
								m_velocityXMin(-0.5f),
								m_velocityXMax(0.5f),
								m_velocityYMin(-0.5f),
								m_velocityYMax(0.5f),
								m_velocityZMin(-0.5f),
								m_velocityZMax(0.5f),
								m_emissionRate(10),
								m_sizeMinMaxX(0.02f,0.07f),
								m_sizeMinMaxY(0.02f,0.07f),
								m_indicesArray(NULL),
								m_vfArray(NULL),
								m_bitsShifted(0),
								m_numSamples(1),
								m_accum(0),
								m_aligned(false)
{}

ParticleSystem::~ParticleSystem(){
	m_particles.clear();
	delete [] m_vfArray;
}


ParticleSystem::ParticleSystem(const ParticleSystem& rhs){}
ParticleSystem& ParticleSystem::operator = (const ParticleSystem& rhs){ return *this; }


void ParticleSystem::initialize(){
	m_emitter[2]+=0.1f;
	m_numParticles=((unsigned int)(10*m_lifeMax)+1)*m_emissionRate;
	if (m_numParticles>1000){
		m_lifeMax=m_lifeMin=1.0f;
		m_emissionRate=10;
		m_numParticles=((unsigned int)(10*m_lifeMax)+1)*m_emissionRate;
	}

	m_vfArray=new float[(20*m_numParticles)];	//24 floats from vertices, 8 floats from tex coords
	m_vfSize=5;
	
	
	float *pVf=m_vfArray; int offset=m_vfSize-1;
	for(unsigned int i=0;i<m_numParticles;i++){
		//quads
		(*pVf)=0; pVf++; (*pVf)=0; pVf+=offset;
		(*pVf)=1; pVf++; (*pVf)=0; pVf+=offset;
		(*pVf)=1; pVf++; (*pVf)=1; pVf+=offset;
		(*pVf)=0; pVf++; (*pVf)=1; pVf+=offset;

	}

	//setup maximum index buffer
	m_indicesArray=new unsigned short [6*m_numParticles];
	
	unsigned short *uip=m_indicesArray;
	unsigned short index;
	for(unsigned short i=0;i<(unsigned short)m_numParticles;i++){
		//for each particle there will be 2 triangles
		//first triangle
		index=i<<2;
		(*uip)=index; uip++; (*uip)=index+1; uip++; (*uip)=index+2; uip++;   
		//second triangle
		(*uip)=index; uip++; (*uip)=index+2; uip++; (*uip)=index+3; uip++; 
	}

	m_vaObject.setFlags(VFF_TEX2|VFF_VERTEX3|VFF_INDEX_USHORT);

	
}



void ParticleSystem::updateArrays(float deltaT){
	float *pVf=m_vfArray;
	
	const Vector3f right=MeshManager::get()->getCameraRight();
	const Vector3f vup=MeshManager::get()->getCameraVup();
	
	vector<Particle>::iterator it=m_particles.begin();
	if (m_numSamples>1){
		for (;it!=m_particles.end();){
			if (!(*it).decreaseLifeT()){
				it=m_particles.erase(it);
				continue;
			}
			//update position and modify texture coordinates
			(*it).updatePosition(deltaT,vup,right,&pVf,true);
			it++;
		}
	}else{
		for (;it!=m_particles.end();){
			if (!(*it).decreaseLife()){
				it=m_particles.erase(it);
				continue;
			}
			(*it).updatePosition(deltaT,vup,right,&pVf);
			it++;
		}
	}
}



void ParticleSystem::emitParticles(float deltaT){
	int index=m_particles.size();
	m_emitter+=deltaT*m_velocity;
	
	Matrix44f localAlign;
	
	if (m_aligned)
		localAlign.AlignOxToD(m_direction);

	for (unsigned int i=0;i<m_emissionRate;i++){
		Particle p;

		float s=RandomHashTable::get()->randomMinMaxf(m_sizeMinMaxX.x,m_sizeMinMaxX.y);
		p.setSize(s,s);
		p.setLife(RandomHashTable::get()->randomMinMaxf(m_lifeMin,m_lifeMax));
		p.setPosition(m_emitter);
		
		Vector3f v;
		v[0]=RandomHashTable::get()->randomMinMaxf(m_velocityXMin, m_velocityXMax);
		v[1]=RandomHashTable::get()->randomMinMaxf(m_velocityYMin, m_velocityYMax);
		v[2]=RandomHashTable::get()->randomMinMaxf(m_velocityZMin, m_velocityZMax);
		p.setVelocity(localAlign,v+m_particleVelocity);
		m_particles.push_back(p);
		
	}

}

#endif