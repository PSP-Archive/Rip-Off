#pragma once

#ifdef _3D

class ExplosionEffect3DRendererIF{
public:
	virtual void applyTransforms(const Vector3f& pos, float texDelta, int hasDeltaTex=0) const=0;
	virtual void discardTransforms(int hasDeltaTex) const=0;
};

#endif