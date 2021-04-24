#pragma once

#ifdef _3D

#include <string.h>
#include <vector>
#include "foundation/Singleton.h"
#include "../Shape3D.h"
#include "foundation/Vector3f.h"


using namespace std;

class BaseMeshManager{
private:
	vector<Shape3D*> m_vpMeshes;

	Vector3f m_cameraRight, m_cameraVup,m_cameraDirection;

	float m_scalingFactor;		//needed to be stored in a singleton; it will be set by the Scene3D
								//and used by the fire jets; the fire jets need to know the real position
								//of the emitter, which is computed using this scaling factor

public:
	BaseMeshManager();
	~BaseMeshManager();

	Shape3D* hasMesh(const string& meshName) const;
	
	void addMesh(Shape3D* pObject);

	void setCameraAlignment(const Vector3f& right, const Vector3f& up, const Vector3f& direction);
	void setScalingFactor(float scalingFactor);

	const Vector3f& getCameraRight() const;
	const Vector3f& getCameraVup() const;
	const Vector3f& getCameraDirection() const;
	float getScalingFactor() const;

};

inline BaseMeshManager::BaseMeshManager():m_cameraRight(1,0,0), 
										  m_cameraVup(0,1,0),
										  m_cameraDirection(0,0,1)
{}

inline const Vector3f& BaseMeshManager::getCameraRight() const{
	return m_cameraRight;
}

inline const Vector3f& BaseMeshManager::getCameraVup() const{
	return m_cameraVup;
}
inline const Vector3f& BaseMeshManager::getCameraDirection() const{
	return m_cameraDirection;
}

inline float BaseMeshManager::getScalingFactor() const{
	return m_scalingFactor;
}

typedef Singleton<BaseMeshManager> MeshManager;

#endif