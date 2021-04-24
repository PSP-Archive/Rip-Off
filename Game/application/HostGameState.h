#pragma once

#include "application/AppState.h"
#include "ui/UIScene.h"


//--------------------------------------------------------------------------------
/**
Ripoff MainMenu state.
*/
class HostGameState : public AppState
{
private:
	UIScene m_uiScene;

public:
	// Ctor
	HostGameState(Application& app);

	// State events
	void onEnter();
	void onUpdate();
	void onLeave();
};
