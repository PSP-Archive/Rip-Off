#pragma once

#ifdef _3D
#ifdef _PC

#include "../../3dgraphics/PositionerIF.h"

class PCPositioner: public PositionerIF{
public:
	void applyTransforms(const Vector2f& position2D, float angleRot) const;
	void resetTransforms() const;

	//void setZ(float z);
};

#endif
#endif