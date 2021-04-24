#pragma once

#include "foundation/Vector2f.h"
#include "foundation/Vector3f.h"

class WidgetRendererIF{
public:
	virtual void initRendering(const Vector2f& position, const Vector3f& color, float scale) const=0;
	virtual void dismissRendering() const=0;
};