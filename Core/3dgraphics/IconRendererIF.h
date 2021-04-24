#pragma once

#ifdef _3D

#include "foundation/Vector3f.h"

class IconRendererIF{
public:
	virtual ~IconRendererIF(){}

	virtual void enableRendering(const Vector3f& centre, float angle, const Vector3f& axis) const=0;
	virtual void disableRendering() const=0;
	virtual void setNextIconDisplacement(float d) const=0;
};

#endif