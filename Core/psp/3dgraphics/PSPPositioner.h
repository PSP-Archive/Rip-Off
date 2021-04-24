#pragma once

#ifdef _3D
#ifdef _SPSP

#include "../../3dgraphics/PositionerIF.h"

class PSPPositioner: public PositionerIF{
public:
	void applyTransforms(const Vector2f& position2D, float angleRot) const;
	void resetTransforms() const;

};

#endif
#endif