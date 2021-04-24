#pragma once

//every 3d graphics object will hold such an object;
//its role is to receive a Vector2d and a rotation angle,
//and to compute/apply the 3D transforms needed for
//drawing the object in the 3D world.

#ifdef _3D

#include "foundation/Vector2f.h"

class PositionerIF{
public:
	//push matrix and apply the matrices
	virtual void applyTransforms(const Vector2f& position2D, float angleRot) const=0;

	//pop matrix
	virtual void resetTransforms() const=0;
};

#endif