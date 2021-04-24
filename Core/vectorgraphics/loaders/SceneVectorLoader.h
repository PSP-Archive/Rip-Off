#pragma once

#include "graphics/SceneLoaderIF.h"

//--------------------------------------------------------------------------------
class SceneVectorLoader : public SceneLoaderIF
{
public:
	// Just returns a new scene
	Scene* load(const ConfigItem& confItem) { return new Scene; }
};