#pragma once

#include "foundation/Singleton.h"
#include "foundation/ConfigData.h"
#include "input/InputDevice.h"

//--------------------------------------------------------------------------------
/**
	Manager for input state. Implemented as a singleton. The Manager defines
	a ButtonType enumeration that represents the buttons in our 4 virtual gamepads.
	The actual implementation is done thought the InputIF interface.

	TODO:
	Implement analog axes.
*/
class InputManagerBase
{
public:
	// Ctor
	InputManagerBase();

	// Dtor
	~InputManagerBase();

	// Initializes input.
	bool init(const ConfigItem* conf);

	// Updates the input status.
	void update();

	// Cleans up.
	void cleanUp();

	// Returns whether a button is currently pressed.
	bool isButtonPressed(unsigned int, InputDevice::ButtonType);

	// Returns whether a button has been pressed this frame.
	bool isButtonJustPressed(unsigned int, InputDevice::ButtonType);

	// Returns whether a button has been released this frame.
	bool isButtonJustReleased(unsigned int, InputDevice::ButtonType);

	// Tells the state that a button was pressed this frame. The bool param is
	// true for pressed and false for released.
	void setButtonState(unsigned int, InputDevice::ButtonType, bool);

private:
	// Data structure describing the state of a button.
	struct ButtonStatus
	{
		ButtonStatus();
		
		bool isPressed;
		bool isJustPressed;
		bool isJustReleased;
	};

	// Input state data structure
	ButtonStatus m_inputState[InputDevice::MAX_CONTROLLERS][InputDevice::NUM_BUTTONTYPES];

	// The platform input implementation
	InputDevice* m_input;
};

// Singleton implementation
typedef Singleton<InputManagerBase> InputManager;

//--------------------------------------------------------------------------------
inline
InputManagerBase::ButtonStatus::ButtonStatus() :
	isPressed(false),
	isJustPressed(false),
	isJustReleased(false)
{
	// empty
}
