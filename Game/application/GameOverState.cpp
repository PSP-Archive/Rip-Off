#include "application/GameOverState.h"
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
GameOverState::GameOverState(Application& app) :
AppState(app)
{
	//Vector2f uiPosition = Vector2f(-0.17f,0.7f);
	Vector2f uiPosition = Vector2f(-0.27f,0.7f);
	Vector3f uiColor = Vector3f(1.0f,0.5f,0.0f);

	m_uiScene.addWidget(uiPosition,"rip off",0,3.0f,uiColor);

	//menu items
	//uiPosition = Vector2f(-0.175f,0.45f);
	uiPosition = Vector2f(-0.275f,0.45f);
	m_uiScene.addMenuWidget(uiPosition,"GAMEOVER!",2.0f,uiColor,uiColor);
	uiPosition[1] -= 0.15f;
	uiPosition[0] += 0.1f;
	//m_uiScene.addMenuWidget(uiPosition,"FAIL!",3.0f,uiColor,uiColor);
	uiPosition[1] -= 0.15f;
	uiPosition[0] -= 0.075f;
	//m_uiScene.addMenuWidget(uiPosition,"OH DEAR!",2.0f,uiColor,uiColor);
}

//--------------------------------------------------------------------------------
template <class T>
bool from_string(T& t, 
                 const std::string& s, 
                 std::ios_base& (*f)(std::ios_base&))
{
  std::istringstream iss(s);
  return !(iss >> f >> t).fail();
}

void
GameOverState::onEnter()
{
	//	Convert score to a string for PCFile
	string str = toString (GameEngine::get()->getScore());
	string strFromFile;
	File file;
	//	Check if this is a new highscore
	file.open ("host0:assets/Highscore.txt");
	file.readLine (strFromFile);
	file.close ();

	//	If score is new highscore write to the file
	int highscoreFromFile;
	from_string<int>(highscoreFromFile, std::string(strFromFile), std::dec);
	if (GameEngine::get()->getScore() > highscoreFromFile)
	{
		GameEngine::get()->updateHighScore();
		file.writeLineToFile ("host0:assets/Highscore.txt", str);
	}

	//	Add score to GameOver screen
	//Vector2f uiPosition = Vector2f(-0.2f, -0.15f);
	Vector2f uiPosition = Vector2f(-0.3f, -0.15f);
	Vector3f uiColor = Vector3f(1.0f,0.5f,0.0f);

	m_uiScene.addMenuWidget(uiPosition,"YOUR SCORE : ",2.0f,uiColor,uiColor);
	uiPosition[1] -= 0.15f;
	uiPosition[0] += 0.175f;
	m_uiScene.addMenuWidget(uiPosition, str, 2.0f, uiColor, uiColor);
	uiPosition[1] -= 0.15f;
	uiPosition[0] -= 0.225f;
	m_uiScene.addMenuWidget(uiPosition,"THE HIGHSCORE : ",2.0f,uiColor,uiColor);
	uiPosition[1] -= 0.15f;
	uiPosition[0] += 0.225f;
	m_uiScene.addMenuWidget(uiPosition,strFromFile,2.0f,uiColor,uiColor);

#ifdef _3D
	GameEngine::get()->spawnGameoverExplosion(Vector2f(0,0),0);
	GameEngine::get()->spawnGameoverExplosion1(Vector2f(0,0),0);
	Game::ShipList list=GameEngine::get()->getPlayerList();
	for (Game::ShipList::iterator it=list.begin();it!=list.end();it++){
		(*it)->kill();
	}
	list=GameEngine::get()->getThiefList();
	for (Game::ShipList::iterator it=list.begin();it!=list.end();it++){
		(*it)->kill();
	}
#endif

}
//--------------------------------------------------------------------------------
void GameOverState::onUpdate()
{
#ifdef _PC
	glClear(GL_COLOR_BUFFER_BIT);
#elif _SPSP
	sceGuClear(SCEGU_CLEAR_ALL);
#endif

	GameEngine::get()->postUpdate();
	GameEngine::get()->render();

	m_uiScene.render();

#ifdef _SPSP
	if(InputManager::get()->isButtonJustPressed(0, InputDevice::START) || 
		InputManager::get()->isButtonJustPressed(0, InputDevice::BUTTON3))
	{
		// play menu button selection sound
		GameEngine::get()->getSelectButtonSound()->stop();
		GameEngine::get()->getSelectButtonSound()->play();
	
		static_cast<RipOffApplication&>(getApp()).mainMenuState();
	}
#elif _PC
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

}

//--------------------------------------------------------------------------------
void
GameOverState::onLeave()
{
	m_uiScene.popMenuWidget();
	m_uiScene.popMenuWidget();
	m_uiScene.popMenuWidget();
	m_uiScene.popMenuWidget();
	GameEngine::get()->end();
}