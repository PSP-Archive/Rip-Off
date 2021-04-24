#pragma once

#ifdef _3D

#include "CameraRenderer.h"

class Camera{
private:
	//input::InputManager m_input;
	//CameraKeyboardListener m_pCameraListener;

	Vector3f m_observer;
	Vector3f m_direction;
	Vector3f m_lookAt;
	Vector3f m_vup;
	Vector3f m_right;


	float m_fov, m_speed;
	
	float m_far, m_near;
	float m_aspect;
	int m_width, m_height;		//for orthogonal proj and viewport
	
	//float m_angleOx, m_angleOy, m_angleOz;
	float m_angleR, m_angleDir, m_angleUp;
	float m_step, m_angleStep;
	bool m_changed;

	CameraRenderer m_renderer;

private:
	void setRight();
	void setDirection();		//having the observer and look at point we compute the normalized direction of the camera
	void setLookAt();			//having the observer and direction we compute the look at point
	

public:
	Camera();
	~Camera();

	//void setObserver(const Vector3f& observer);

	void moveOnYOZOrbit(float angle);
	void moveOnXOYOrbit(float angle);
	
	void setAspect(int width, int height);
	void setAngleStep(float value);
	void setStep(float value);

	//the original game has the logic computed in the square [(-w2,w2), (-h2,h2)]
	//the camera will display the ships in the plane xOy, but scaled to fit the view frustum
	//the frustum is given by near, far, fov and aspect.
	//the scaling factor s, such that h=sH, w=SW (where H=2, the original height "from gameplay", w=a*H)
	//is: d*tg(fov/2). This scaling factor will be applied to all objects displayed in xOy plane.
	//if d==0 we get the standard scaling factor for xOy plane, using d=m_observer.z;
	//otherwise we return the scaling corresponding to the distance d
	float getScalingFactor(float d=0.0f) const;

	float getAspect() const;

	void adjustScale(const Vector3f& pivot, float zCentre=0) const;
	void resetScale() const;
	
	void applyProjection() const;
	void applyLookAt() const;
	void applyViewport() const;


	void moveForward(float orientation=1.0f);		//if orientation is -1 camera will move backwards
	void turnRight(float orientation=1.0f);
	void lookUp(float orientation=1.0f);
	void strifeRight(float orientation=1.0f);
	void shiftUp(float orientation=1.0f);
	void moveDown(float orientation=1.0f);
	
	//void update();
};


inline void Camera::resetScale() const{
	
	m_renderer.resetScaling();
	//float d=fabs(z-m_observer.z());
	//float s=getScalingFactor(d);
	//s=getScalingFactor(d)/s;
	//m_renderer.applyScale(1/s);
}

inline void Camera::applyProjection() const{
	m_renderer.applyProjection(m_fov,m_aspect,m_near,m_far);
}

inline void Camera::applyLookAt() const{
	m_renderer.applyLookAt(m_observer, m_lookAt,m_vup);
	//m_renderer.applyScale(getScalingFactor());
}

inline void Camera::applyViewport() const{
	m_renderer.applyViewport(m_width,m_height);
}

#endif