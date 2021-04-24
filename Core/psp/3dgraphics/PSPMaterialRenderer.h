#pragma once

#ifdef _3D
#ifdef _SPSP

#include "../../3dgraphics/MaterialRendererIF.h"

#include <libgu.h>
#include <libgum.h>

class PSPMaterialRenderer:public MaterialRendererIF{
public:
	void applyNoLighting(const Vector4f& color) const;

	void apply(const Vector4f& ambient, 
					   const Vector4f& diffuse,
					   const Vector4f& specular,
					   const Vector4f& emissive,
					   float shininess) const;

	void dismiss() const;
	void dismissNoLighting() const;

};


inline void PSPMaterialRenderer::dismiss() const{
	sceGuColor(0xffffffff);
}

inline void PSPMaterialRenderer::dismissNoLighting() const{
	sceGuColor(0xffffffff);
}

inline void PSPMaterialRenderer::apply(const Vector4f& ambient, 
									   const Vector4f& diffuse,
									   const Vector4f& specular,
									   const Vector4f& emissive,
									   float shininess) const
{
	sceGuColor(diffuse.GetPackedColor());
}

inline void PSPMaterialRenderer::applyNoLighting(const Vector4f& color) const{
	sceGuColor(color.GetPackedColor());
}

#endif
#endif