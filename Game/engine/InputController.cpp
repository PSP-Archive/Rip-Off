#include "InputController.h"
#include "input/InputManager.h"
#include "engine/ship.h"

// Always place as last include and only in cpp files!!
#include "foundation/Debug.h"

InputController::InputController(int playerNo)
{
	m_playerNo = playerNo;
}

InputController::~InputController(void)
{
}

void InputController::Update(float frameTime)
{
#ifndef _SPSP
	if(InputManager::get()->isButtonPressed(m_playerNo, InputDevice::UP))
	{
		mp_ship->throttle(1.0f);
	}
	if(InputManager::get()->isButtonPressed(m_playerNo, InputDevice::LEFT))
	{
		mp_ship->steer(frameTime);
	}
	else if(InputManager::get()->isButtonPressed(m_playerNo, InputDevice::RIGHT))
	{
		mp_ship->steer(-frameTime);
	}
#else
	if(InputManager::get()->isButtonPressed(m_playerNo, InputDevice::MOVEUP))
	{
		mp_ship->throttle(1.0f);
	}
	if(InputManager::get()->isButtonPressed(m_playerNo, InputDevice::TURNLEFT))
	{
		mp_ship->steer(frameTime);
	}
	else if(InputManager::get()->isButtonPressed(m_playerNo, InputDevice::TURNRIGHT))
	{
		mp_ship->steer(-frameTime);
	}
#endif

	if(InputManager::get()->isButtonJustPressed(m_playerNo, InputDevice::BUTTON1))
	{
		mp_ship->shoot();
	}
}

void InputController::Init()
{
}

void InputController::Cleanup()
{
}
