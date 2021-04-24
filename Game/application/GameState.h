#pragma once

#include "application/AppState.h"
#include "sound/Sound.h"
#include "graphics/GFXObject.h"
#include "graphics/Scene.h"
#include "graphics/GFXObjectLoader.h"
#include "ui/UIScene.h"

//--------------------------------------------------------------------------------
/**
	Ripoff game state.
*/
class GameState : public AppState
{
public:
	// Ctor
	GameState(Application& app);

	// State events
	void onEnter();
	void onUpdate();
	void onLeave();

private:
	UIScene m_uiScene;
	Sound* m_bgSound;
	Sound* m_engineSound;
	Sound* m_shootSound;

	GFXObject* m_object;
	//Scene* m_scene;
	GFXObjectLoader m_loader;
};
