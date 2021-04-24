#pragma once

#include "application/AppState.h"
#include "ui/UIScene.h"
#include "foundation/File.h"

//--------------------------------------------------------------------------------
/**
	Ripoff Highscore state.
*/
class HighscoreState : public AppState
{
private:
	UIScene m_uiScene;
	File m_file;

public:
	// Ctor
	HighscoreState(Application& app);

	// State events
	void onEnter();
	void onUpdate();
	void onLeave();
};
