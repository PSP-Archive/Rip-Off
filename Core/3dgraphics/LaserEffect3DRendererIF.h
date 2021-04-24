#pragma once

#ifdef _3D

class LaserEffect3DRendererIF{
public:
	virtual void applyTransforms(const Vector3f& pos, const Vector3f& camDirection, float angle, float totalOffset, float texDelta, int hasDeltaTex=0) const=0;
	virtual void discardTransforms(int hasDeltaTex) const=0;
};

#endif