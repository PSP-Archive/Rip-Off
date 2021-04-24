#pragma once

#include "application/AppState.h"
#include "ui/UIScene.h"
#include "foundation/File.h"

//--------------------------------------------------------------------------------
/**
	Ripoff GameOver state.
*/
class GameOverState : public AppState
{
private:
	UIScene m_uiScene;

public:
	// Ctor
	GameOverState(Application& app);

	// State events
	void onEnter();
	void onUpdate();
	void onLeave();
};
