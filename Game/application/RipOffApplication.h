#pragma once

#include "application/Application.h"
#include "engine/game.h"


//--------------------------------------------------------------------------------
/**
	Riopff specific application.
*/
class RipOffApplication : public Application
{
public:
	// Ctor
	RipOffApplication(OS& os);

	// Set specific states
	void gameState() { setState(m_gameState); }
	void highscoreState() { setState(m_highscoreState); }
	void mainMenuState() { setState(m_mainMenuState); }
	void gameOverState()	{ setState(m_gameOverState); }
	void hostGameState() { setState(m_hostGameState); }
	void networkGameState() { setState(m_networkGameState); }
protected:
	void onInit();
	void onCleanUp();

private:
	StateHandle m_gameState;
	StateHandle m_mainMenuState;
	StateHandle m_highscoreState;
	StateHandle m_gameOverState;
	StateHandle m_hostGameState;
	StateHandle m_networkGameState;
};
