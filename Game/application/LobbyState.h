#pragma once

#include "application/AppState.h"
#include "ui/UIScene.h"

//--------------------------------------------------------------------------------
/**
Ripoff MainMenu state.
*/
class LobbyState : public AppState
{
private:
	UIScene m_uiScene;
public:
	// Ctor
	LobbyState(Application& app);

	// State events
	void onEnter();
	void onUpdate();
	void onLeave();
};
