#pragma once
#ifdef _3D

#include "../Texture.h"
#include "../Material.h"
#include "foundation/ConfigData.h"
#include "foundation/ConfigItem.h"

class MaterialsLoader{
public:
	bool load(const ConfigItem& item) const;

private:
	Texture* parseTextureNode(const ConfigItem* confItem) const;
	Material* parseMaterialNode(const std::string& matName, const ConfigData& data) const;
	const ConfigItem* getItem(const std::string& name, const ConfigData& data) const;
};

#endif