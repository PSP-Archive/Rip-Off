#pragma once
#ifdef _3D


//class used by the 3D Graphics layer for loading a scene

#include "../../graphics/SceneLoaderIF.h"
#include <string>
using namespace std;

#include "../Texture.h"
#include "../Material.h"
#include "foundation/ConfigData.h"
#include "foundation/ConfigItem.h"

class Scene3DLoader: public SceneLoaderIF{
public:
	Scene* load(const ConfigItem& confItem) const;


};

#endif