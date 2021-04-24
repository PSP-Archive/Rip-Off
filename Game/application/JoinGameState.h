#pragma once

#include "application/AppState.h"
#include "ui/UIScene.h"


//--------------------------------------------------------------------------------
/**
Ripoff MainMenu state.
*/
class JoinGameState : public AppState
{
private:
	UIScene m_uiScene;

public:
	// Ctor
	JoinGameState(Application& app);

	// State events
	void onEnter();
	void onUpdate();
	void onLeave();
};
