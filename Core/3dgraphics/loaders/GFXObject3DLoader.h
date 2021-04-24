#pragma once

#ifdef _3D

#include "../../graphics/GFXObjectLoaderIF.h"
//#include "foundation/ConfigItem.h"
#include "../Material.h"
#include "../Texture.h"

class GFXObject3DLoader:public GFXObjectLoaderIF{
public:
	~GFXObject3DLoader(){}

	virtual GFXObject* load(const ConfigItem& confItem) const;

	Material* loadMaterial(const ConfigItem& item) const;
	Texture* loadTexture(const ConfigItem& item) const;
};

#endif