#include <cassert>
#include "input/InputManager.h"

// Always place as last include and only in cpp files!!
#include "foundation/Debug.h"

//--------------------------------------------------------------------------------
InputManagerBase::InputManagerBase()
{

}

//--------------------------------------------------------------------------------
InputManagerBase::~InputManagerBase()
{

}

//--------------------------------------------------------------------------------
bool
InputManagerBase::init(const ConfigItem* conf)
{
	m_input = new InputDevice();

	return m_input->init(conf);
}

//--------------------------------------------------------------------------------
void
InputManagerBase::update()
{
	// Clear the "just" flags
	for(int i=0; i<InputDevice::MAX_CONTROLLERS; i++)
	{
		for(int j=0; j<InputDevice::NUM_BUTTONTYPES; j++)
		{
			m_inputState[i][j].isJustPressed = 0;
			m_inputState[i][j].isJustReleased = 0;
		}
	}

	// Ask the platform to update us
	m_input->update(this);
}

//--------------------------------------------------------------------------------
void
InputManagerBase::cleanUp()
{
	m_input->cleanUp();

	delete m_input;
}

//--------------------------------------------------------------------------------
bool
InputManagerBase::isButtonPressed(unsigned int c, InputDevice::ButtonType b)
{
	assert(c < InputDevice::MAX_CONTROLLERS);
	assert(b < InputDevice::NUM_BUTTONTYPES);
	return m_inputState[c][b].isPressed;
}

//--------------------------------------------------------------------------------
bool
InputManagerBase::isButtonJustPressed(unsigned int c, InputDevice::ButtonType b)
{
	assert(c < InputDevice::MAX_CONTROLLERS);
	assert(b < InputDevice::NUM_BUTTONTYPES);
	return m_inputState[c][b].isJustPressed;
}

//--------------------------------------------------------------------------------
bool
InputManagerBase::isButtonJustReleased(unsigned int c, InputDevice::ButtonType b)
{
	assert(c < InputDevice::MAX_CONTROLLERS);
	assert(b < InputDevice::NUM_BUTTONTYPES);
	return m_inputState[c][b].isJustReleased;
}

//--------------------------------------------------------------------------------
void
InputManagerBase::setButtonState(unsigned int c, InputDevice::ButtonType b, bool pressed)
{
	assert(c < InputDevice::MAX_CONTROLLERS);
	assert(b < InputDevice::NUM_BUTTONTYPES);

	m_inputState[c][b].isJustPressed = pressed && !m_inputState[c][b].isPressed;
	m_inputState[c][b].isJustReleased = !pressed && m_inputState[c][b].isPressed;
	m_inputState[c][b].isPressed = pressed;
}
