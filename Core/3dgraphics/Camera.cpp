#include "Camera.h"

#ifdef _3D

#include "Camera.h"
#include "foundation/Matrix44f.h"

//include the manager to inform the meshes about m_right and m_vup
#include "managers/MeshManager.h"

Camera::Camera(): m_observer(0.0f,0.0f,-10.0f),
				  m_lookAt(0.0f,0.0f,0.0f),
				  m_direction(0.0f,0.0f,1.0f),
				  m_right(-1.0f,0.0f,0.0f),
				  m_vup(0.0f, 1.0f, 0.0f),
				  m_fov(45),
				  m_angleR(0.0f), m_angleDir(0.0f), m_angleUp(0.0f),
				  m_angleStep(0.1f), m_step(1.0f), m_speed(5.0f),
				  m_changed(true),
				  m_near(1.0f), m_far(1000.0f)
{
	MeshManager::get()->setCameraAlignment(m_right,m_vup,m_direction);
}

/*Camera::Camera(): m_observer(0.0f,0.0f,10.0f),
				  m_lookAt(0.0f,0.0f,0.0f),
				  m_direction(0.0f,0.0f,-1.0f),
				  m_right(1.0f,0.0f,0.0f),
				  m_vup(0.0f, 1.0f, 0.0f),
				  m_fov(45),
				  m_angleR(0.0f), m_angleDir(0.0f), m_angleUp(0.0f),
				  m_angleStep(0.1f), m_step(1.0f), m_speed(5.0f),
				  m_changed(true),
				  m_near(1.0f), m_far(1000.0f)
{
	MeshManager::get()->setCameraAlignment(m_right,m_vup,m_direction);
}*/

Camera::~Camera(){}


//-----------------------------------------------------------
//		camera setters
//-----------------------------------------------------------
void Camera::setRight(){
	m_right.Cross(m_vup,m_direction);
}
void Camera::setDirection(){
	m_direction.Subtract(m_lookAt,m_observer);
	m_direction.Normalise();
}
void Camera::setLookAt(){
	m_lookAt=m_observer+m_direction;
}
/*void Camera::setObserver(const Vector3f& observer){
	m_observer=observer;
	setDirection();
	m_vup.Cross(m_right,m_direction);
	m_vup.Normalise();
}*/

void Camera::moveOnYOZOrbit(float angle){
	//angle is given in degrees
	Matrix44f rot;
	rot.MakeRotateX(angle*DegRad);
	m_observer=(rot*m_observer).xyz();
	m_vup=(rot*m_vup).xyz();
	m_direction=-m_observer;
	m_direction.Normalise();
	m_right=m_direction.Cross(m_vup);
	m_right.Normalise();
	MeshManager::get()->setCameraAlignment(m_right,m_vup,m_direction);

}
void Camera::moveOnXOYOrbit(float angle){
	Matrix44f rot;
	rot.MakeRotateZ(angle*DegRad);
	m_observer=(rot*m_observer).xyz();
	m_vup=(rot*m_vup).xyz();
	m_direction=-m_observer;
	m_direction.Normalise();
	m_right=m_direction.Cross(m_vup);
	m_right.Normalise();
	MeshManager::get()->setCameraAlignment(m_right,m_vup,m_direction);
}


void Camera::setAngleStep(float value){
	m_angleStep=value;
}
void Camera::setStep(float value){
	m_step=value;
}
void Camera::setAspect(int width, int height){
	m_width=width;
	m_height=height;
	m_aspect=(float)m_width/(float)m_height;
}



float Camera::getScalingFactor(float d) const{
	if (d==0) d=m_observer.z();
	return d*tanf(m_fov/2.0f*DegRad);
}

float Camera::getAspect() const{
	return m_aspect;
}

void Camera::adjustScale(const Vector3f& pivot, float zCentre) const{
	
	float d=fabs(pivot.z()-m_observer.z());
	float s=getScalingFactor(d);
	MeshManager::get()->setScalingFactor(s);
	//s=getScalingFactor(d)/s;
	m_renderer.adjustScaling(s,pivot,zCentre);
}


//-----------------------------------------------------------
//		camera modifiers
//-----------------------------------------------------------
void Camera::moveDown(float orientation){
	m_observer[1]+=orientation*m_step;
	setLookAt();
}

void Camera::moveForward(float orientation){
	m_observer +=m_direction*(orientation*m_step);
	m_changed=true;
}

void Camera::turnRight(float orientation){
	m_angleUp+=orientation*m_angleStep;
	if (m_angleUp>=2*PI)
		m_angleUp=0;
	m_changed=true;
}

void Camera::lookUp(float orientation){
	m_angleR-=orientation*m_angleStep;
	if (m_angleR>=2*PI)
		m_angleR=0;
	m_changed=true;
}

void Camera::strifeRight(float orientation){
	m_observer-=orientation*m_step*m_right;
	m_changed=true;
}
void Camera::shiftUp(float orientation){
	m_observer+=orientation*m_step*m_vup;
	m_changed=true;
}




/*
void Camera::update(){
	//m_input.Update();
	if (m_changed){
		m_changed=false;
/*
		Matrix44f mOx; mOx.MakeRotate(m_angleR,m_right);
		//Matrix44f mOy; mOy.MakeRotate(m_angleUp,m_vup);
		Matrix44f mOy; mOy.MakeRotateY(m_angleUp);
		Matrix44f mOz; mOz.MakeRotate(m_angleDir,m_direction);
		
		//Matrix44f mOx; mOx.MakeRotateX(m_angleOx);
		//Matrix44f mOy; mOy.MakeRotateZ(m_angleOy);
		//Matrix44f mOz; mOz.MakeRotateY(m_angleOz);
		
		mOx*=mOy; mOz*=mOx;

		//m_right=(mOz*m_right).xyz();
		m_vup=(mOz*m_vup).xyz();
		m_direction=(mOz*m_direction).xyz();
		//m_direction.Cross(m_vup,m_right);
		//m_vup.Cross(m_right,m_direction);
		m_right=m_direction.Cross(m_vup);
		m_vup.Cross(m_right,m_direction);

		m_right.Normalise();
		m_vup.Normalise();
		m_direction.Normalise();

		setLookAt();
		m_angleR=0; m_angleUp=0; m_angleDir=0;
* /
	}
}*/


#endif