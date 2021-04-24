#include "application/HighscoreState.h"
#include "application/RipOffApplication.h"
#include "input/InputManager.h"
#include "foundation/Vector2f.h"
#include "foundation/ToString.h"

#ifdef _PC
#include <windows.h>
#include <gl/gl.h>
#endif

// Always place as last include and only in cpp files!!
#include "foundation/Debug.h"

//--------------------------------------------------------------------------------
HighscoreState::HighscoreState(Application& app) :
AppState(app)
{
	Vector2f uiPosition = Vector2f(-0.17f,0.7f);
	Vector3f uiColor = Vector3f(1.0f,0.5f,0.0f);

	m_uiScene.addWidget(uiPosition,"rip off",0,4.0f,uiColor);

	//menu items
	uiPosition = Vector2f(-0.2f,0.3f);
	m_uiScene.addMenuWidget(uiPosition,"highscore",3.0f,uiColor,uiColor);

	string highScore = "0";
	//	Load in the score from the Highscore.txt file
	if (m_file.open ("host0:assets/Highscore.txt"))	{
		m_file.readLine (highScore);
		m_file.close ();

		GameEngine::get()->setHighScore(atoi(highScore.c_str()));
	}

	//	Add score in widget to the UIScene
	uiPosition = Vector2f(-0.1f, 0.0f);
	uiColor = Vector3f(1.0f,0.5f,0.0f);
	m_uiScene.addMenuWidget(uiPosition, highScore,3.0f,uiColor,uiColor);
}

//--------------------------------------------------------------------------------
void
HighscoreState::onEnter()
{	
	char* highScore = new char[sizeof(int)];
	
	itoa(GameEngine::get()->getHighScore(), highScore, 10);
	
	m_uiScene.setText(2, highScore);

	delete [] highScore;
}
//--------------------------------------------------------------------------------
void HighscoreState::onUpdate()
{
#ifndef _SPSP
	glClear(GL_COLOR_BUFFER_BIT);
#else
	sceGuClear(SCEGU_CLEAR_ALL);
#endif

	m_uiScene.render();

#ifdef _PC
	if(InputManager::get()->isButtonJustPressed(0, InputDevice::UP) ||
		InputManager::get()->isButtonJustPressed(1, InputDevice::UP) ||
		InputManager::get()->isButtonJustPressed(0, InputDevice::START) ||
		InputManager::get()->isButtonJustPressed(1, InputDevice::START) ||
		InputManager::get()->isButtonJustPressed(0, InputDevice::DOWN) ||
		InputManager::get()->isButtonJustPressed(1, InputDevice::DOWN))
	{
		static_cast<RipOffApplication&>(getApp()).mainMenuState();
	}
#endif

if(InputManager::get()->isButtonJustPressed(0, InputDevice::START) || 
		InputManager::get()->isButtonJustPressed(0, InputDevice::BUTTON4))
	{
		static_cast<RipOffApplication&>(getApp()).mainMenuState();
	}

}

//--------------------------------------------------------------------------------
void
HighscoreState::onLeave()
{

}

