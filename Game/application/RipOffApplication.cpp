#include "application/RipOffApplication.h"
#include "application/GameState.h"
#include "application/MainMenuState.h"
#include "application/HighscoreState.h"
#include "application/GameOverState.h"
#include "application/HostGameState.h"
//#include "application/JoinGameState.h"
#include "application/NetworkGameState.h"

#include <libgu.h>
// Always place as last include and only in cpp files!!
#include "foundation/Debug.h"

//--------------------------------------------------------------------------------
RipOffApplication::RipOffApplication(OS& os) :
	Application(os)
{
	// empty
}

//--------------------------------------------------------------------------------
void
RipOffApplication::onInit()
{
	m_gameState = addState(new GameState(*this));
	m_mainMenuState = addState(new MainMenuState(*this));
	m_highscoreState = addState(new HighscoreState(*this));
	m_gameOverState = addState(new GameOverState(*this));
	m_hostGameState = addState(new HostGameState(*this));
	m_networkGameState = addState(new NetworkGameState(*this));

	setState(m_mainMenuState);

	GameEngine::get()->setAspectRatio(SCEGU_SCR_ASPECT );
	GameEngine::get()->init(&getConfig());
}

//--------------------------------------------------------------------------------
void
RipOffApplication::onCleanUp()
{
	// Clear up the Game class
	GameEngine::release();
}