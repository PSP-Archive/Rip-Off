#pragma once
#ifdef _3D
#ifdef _SPSP
#include "../foundation/PSPHeap.h"
#endif

#include "../foundation/Matrix44f.h"

class Particle{
	private:
	Vector3f m_position;
	Vector3f m_velocity;
	
	float m_sizeX, m_sizeY;
	float m_life, m_totalLife, m_t, m_changeTexTime, m_incChangeTime;											//m_totalLife decreases over time until it reaches 0; 
																		//m_life is a counter to store how much time this particle has to live 
	Vector3f m_right, m_vup;

public:
	Particle():m_right(0.5f,0.0f,0.0f), m_vup(0.0f,0.0f,0.5f), m_t(0.0f){}
	~Particle(){}
	
	void setSize(float sizeX, float sizeY);
	void setVelocity(const Matrix44f& transform, Vector3f& v);
	void setPosition(Vector3f& emitterPos);

	//float* GetVelocity();
	void setLife(float life);
	bool decreaseLife();
	bool decreaseLifeT();
	void applyForce(const Vector3f& force);
	
	//methods used for updating a particle and storing its new info in the array
	//received in the list of arguments. The array will be the vf buffer used for
	//rendering; the first method updates the texture coordinates and the vertices positions,
	//while the second updates only the positions of the vertices
	void updatePosition(float deltaT, const Vector3f& vup, const Vector3f& right, float** ppArray, bool updateTex);
	void updatePosition(float deltaT, const Vector3f& vup, const Vector3f& right, float** ppArray);

	
	//void updatePosition(float deltaT, const Vector3f& vup, const Vector3f& right, float** ppArray);
	//void updatePosition(float deltaT, const Vector3f& vup, const Vector3f& right, float** ppArray, float **ppTex);
	
};

//inline float* Particle::GetVelocity(){
//	return m_velocity.getArray();
//}

/*
inline void Particle::updatePosition(float deltaT, const Vector3f& vup, const Vector3f& right, float** ppArray){
	m_position+=m_velocity*deltaT;
	memcpy((*ppArray),(m_position-right*m_sizeX-vup*m_sizeY).GetArray(),3*sizeof(float)); (*ppArray)+=3; 
	memcpy((*ppArray),(m_position+right*m_sizeX-vup*m_sizeY).GetArray(),3*sizeof(float)); (*ppArray)+=3; 
	memcpy((*ppArray),(m_position+right*m_sizeX+vup*m_sizeY).GetArray(),3*sizeof(float)); (*ppArray)+=3; 
	memcpy((*ppArray),(m_position-right*m_sizeX+vup*m_sizeY).GetArray(),3*sizeof(float)); (*ppArray)+=3; 
}

inline void Particle::updatePosition(float deltaT, const Vector3f& vup, const Vector3f& right, float** ppArray, float **ppTex){
	m_position+=m_velocity*deltaT;
	

	memcpy((*ppArray),(m_position-right*m_sizeX-vup*m_sizeY).GetArray(),3*sizeof(float)); (*ppArray)+=3; 
	memcpy((*ppArray),(m_position+right*m_sizeX-vup*m_sizeY).GetArray(),3*sizeof(float)); (*ppArray)+=3; 
	memcpy((*ppArray),(m_position+right*m_sizeX+vup*m_sizeY).GetArray(),3*sizeof(float)); (*ppArray)+=3; 
	memcpy((*ppArray),(m_position-right*m_sizeX+vup*m_sizeY).GetArray(),3*sizeof(float)); (*ppArray)+=3; 

	(**ppTex)=m_t;         (*ppTex)++; (**ppTex)=0; (*ppTex)++; 
	(**ppTex)=m_t+0.0625f; (*ppTex)++; (**ppTex)=0; (*ppTex)++; 
	(**ppTex)=m_t+0.0625f; (*ppTex)++; (**ppTex)=1; (*ppTex)++; 
	(**ppTex)=m_t;		   (*ppTex)++; (**ppTex)=1; (*ppTex)++; 
	
}*/

inline void Particle::updatePosition(float deltaT, const Vector3f& vup, const Vector3f& right, float** ppArray, bool updateTex){
	//m_position+=m_velocity*deltaT;
	m_position+=m_velocity*deltaT;

/*	(**ppArray)=m_t;		   (*ppArray)++; (**ppArray)=1; (*ppArray)++; 
	memcpy((*ppArray),(m_position-right*m_sizeX+vup*m_sizeY).GetArray(),3*sizeof(float)); (*ppArray)+=3;

	(**ppArray)=m_t;         (*ppArray)++; (**ppArray)=0; (*ppArray)++;
	memcpy((*ppArray),(m_position-right*m_sizeX-vup*m_sizeY).GetArray(),3*sizeof(float)); (*ppArray)+=3; 

	(**ppArray)=m_t+0.0625f; (*ppArray)++; (**ppArray)=1; (*ppArray)++; 
	memcpy((*ppArray),(m_position+right*m_sizeX+vup*m_sizeY).GetArray(),3*sizeof(float)); (*ppArray)+=3;

	(**ppArray)=m_t+0.0625f; (*ppArray)++; (**ppArray)=0; (*ppArray)++; 
	memcpy((*ppArray),(m_position+right*m_sizeX-vup*m_sizeY).GetArray(),3*sizeof(float)); (*ppArray)+=3; 
*/

	(**ppArray)=m_t;         (*ppArray)++; (**ppArray)=0; (*ppArray)++;
	memcpy((*ppArray),(m_position-right*m_sizeX-vup*m_sizeY).GetArray(),3*sizeof(float)); (*ppArray)+=3; 

	(**ppArray)=m_t+0.0625f; (*ppArray)++; (**ppArray)=0; (*ppArray)++; 
	memcpy((*ppArray),(m_position+right*m_sizeX-vup*m_sizeY).GetArray(),3*sizeof(float)); (*ppArray)+=3; 

	(**ppArray)=m_t+0.0625f; (*ppArray)++; (**ppArray)=1; (*ppArray)++; 
	memcpy((*ppArray),(m_position+right*m_sizeX+vup*m_sizeY).GetArray(),3*sizeof(float)); (*ppArray)+=3;

	(**ppArray)=m_t;		   (*ppArray)++; (**ppArray)=1; (*ppArray)++; 
	memcpy((*ppArray),(m_position-right*m_sizeX+vup*m_sizeY).GetArray(),3*sizeof(float)); (*ppArray)+=3;

	
	
	

}

inline void Particle::updatePosition(float deltaT, const Vector3f& vup, const Vector3f& right, float** ppArray){
	m_position+=m_velocity*deltaT;

	
	/*(*ppArray)+=2; 
	memcpy((*ppArray),(m_position-right*m_sizeX+vup*m_sizeY).GetArray(),3*sizeof(float)); (*ppArray)+=5;

	memcpy((*ppArray),(m_position-right*m_sizeX-vup*m_sizeY).GetArray(),3*sizeof(float)); (*ppArray)+=5; 

	memcpy((*ppArray),(m_position+right*m_sizeX+vup*m_sizeY).GetArray(),3*sizeof(float)); (*ppArray)+=5;
 
	memcpy((*ppArray),(m_position+right*m_sizeX-vup*m_sizeY).GetArray(),3*sizeof(float)); (*ppArray)+=3;
	*/

	//quads
	/*(*ppArray)+=2; 

	memcpy((*ppArray),(m_position-right*m_sizeX-vup*m_sizeY).GetArray(),3*sizeof(float)); (*ppArray)+=5;

	memcpy((*ppArray),(m_position+right*m_sizeX-vup*m_sizeY).GetArray(),3*sizeof(float)); (*ppArray)+=5;

	memcpy((*ppArray),(m_position+right*m_sizeX+vup*m_sizeY).GetArray(),3*sizeof(float)); (*ppArray)+=5;

	memcpy((*ppArray),(m_position-right*m_sizeX+vup*m_sizeY).GetArray(),3*sizeof(float)); (*ppArray)+=3;

*/

	//---------------------------------------------------------------------------------------

	(*ppArray)+=2; 

	Vector3f v=m_position-right*m_sizeX-vup*m_sizeY;
	(**ppArray)=v.x(); (*ppArray)++;
	(**ppArray)=v.y(); (*ppArray)++;
	(**ppArray)=v.z(); (*ppArray)+=3;


	v=m_position+right*m_sizeX-vup*m_sizeY;
	(**ppArray)=v.x(); (*ppArray)++;
	(**ppArray)=v.y(); (*ppArray)++;
	(**ppArray)=v.z(); (*ppArray)+=3;


	v=m_position+right*m_sizeX+vup*m_sizeY;
	(**ppArray)=v.x(); (*ppArray)++;
	(**ppArray)=v.y(); (*ppArray)++;
	(**ppArray)=v.z(); (*ppArray)+=3;


	v=m_position-right*m_sizeX+vup*m_sizeY;
	(**ppArray)=v.x(); (*ppArray)++;
	(**ppArray)=v.y(); (*ppArray)++;
	(**ppArray)=v.z(); (*ppArray)++;


	

}



inline void Particle::setSize(float sizeX, float sizeY){
	m_sizeX=sizeX;
	m_sizeY=sizeY;
}
inline void Particle::setVelocity(const Matrix44f& transform, Vector3f& v){
	m_velocity=(transform*v).xyz();										//the initial velocity of the particle
}
inline void Particle::setPosition(Vector3f& emitterPos){//, const Matrix44f& objModelview){
	m_position=emitterPos;
	//m_position=(objModelview*emitterPos).xyz();
	//m_position+=objModelview.Vector(3);
}

inline void Particle::setLife(float life){
	m_life=m_totalLife=life;
	m_incChangeTime=m_totalLife/16.0f;
	m_changeTexTime=m_totalLife-m_incChangeTime;
	//m_t=0.0f;
	//m_t=0.9374f;
	//m_t=16*0.0625f;
}
inline bool Particle::decreaseLife(){
	m_life-=0.1f;
	if (m_life<0) return false;
	return true;
}

inline bool Particle::decreaseLifeT(){
	m_life-=0.1f;
	if (m_life<0) return false;
	if (m_life<m_changeTexTime){
		m_t+=0.0625f;
		m_changeTexTime-=m_incChangeTime;
	}
	return true;
}

inline void Particle::applyForce(const Vector3f& force){
	m_velocity+=force;
}

#endif