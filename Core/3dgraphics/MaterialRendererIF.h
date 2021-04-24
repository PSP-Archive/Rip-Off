#pragma once

#ifdef _3D

#include "foundation/Vector4f.h"

class MaterialRendererIF{
public:
	virtual ~MaterialRendererIF(){}

	virtual void applyNoLighting(const Vector4f& color) const=0;

	virtual void apply(const Vector4f& ambient, 
					   const Vector4f& diffuse,
					   const Vector4f& specular,
					   const Vector4f& emissive,
					   float shininess) const=0;

	virtual void dismiss() const=0;
	virtual void dismissNoLighting() const=0;
};

#endif