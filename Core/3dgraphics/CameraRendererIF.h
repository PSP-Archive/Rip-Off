#pragma once

#ifdef _3D

#include "foundation/Vector3f.h"


class CameraRendererIF{
public:
	virtual ~CameraRendererIF(){}

	virtual void applyLookAt(const Vector3f& observer, const Vector3f lookAt, const Vector3f& up) const =0;
	virtual void applyProjection(float fov, float aspect, float near, float far) const =0;
	virtual void applyViewport(float width, float height) const =0;
	
	virtual void adjustScaling(float s, const Vector3f& pivot, float zCentre=0) const=0;
	virtual void resetScaling() const=0;
	//virtual void applyScale(float s) const=0;
	//virtual void applyTranslate(float tz) const=0;
};

#endif