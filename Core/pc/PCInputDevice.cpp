#ifdef _PC

#include <iostream>
#include <sstream>

#include "pc/PCInputDevice.h"
#include "pc/PCOS.h"
#include "input/InputManager.h"

// Always place as last include and only in cpp files!!
#include "foundation/Debug.h"

// Always place as last include and only in cpp files!!
#include "foundation/Debug.h"

//--------------------------------------------------------------------------------
PCInputDevice::PCInputDevice() :
	m_directInput(NULL),
	m_numGamepads(0)
{
	// Standard bindings
	standardBindings();
}

//--------------------------------------------------------------------------------
bool 
PCInputDevice::init(const ConfigItem* conf)
{
	// Create direct input object
	if(FAILED(DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void**)&m_directInput, NULL)))
	{
		m_directInput = NULL;
		return false;
	}

	// Init the keyboard
	if(!setupKeyboard())
	{
		cleanUp();
		return false;
	}

	// Search and init any gamepads
	if(!setupGamepads())
	{
		cleanUp();
		return false;
	}

	// Load the bindings
	loadBindings(conf);
	
	return true;
}

//--------------------------------------------------------------------------------
void
PCInputDevice::update(InputManagerBase* input)
{
	DWORD items;
	
	// Retrieve the buffered data from the keyboard
	items = DEVICE_BUFFER_SIZE;
	m_keyboardDevice->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), m_deviceBuffer, &items, 0);

	// Parse the output
	for(DWORD i=0; i<items; i++)
	{
		processKeyboardInput(input, m_deviceBuffer[i].dwOfs, m_deviceBuffer[i].dwData);
	}  

	// Retrieve the buffered data from the gamepads
	for(unsigned int i=0; i<m_numGamepads; i++)
	{
		items = DEVICE_BUFFER_SIZE;
		m_gamepads[i]->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), m_deviceBuffer, &items, 0);

		// Parse the output
		for(DWORD j=0; j<items; j++)
		{
			processGamepadInput(input, i, m_deviceBuffer[j].dwOfs, m_deviceBuffer[j].dwData);
		}
	}
}

//--------------------------------------------------------------------------------
void
PCInputDevice::cleanUp()
{
	for(unsigned int i=0; i<m_numGamepads; i++)
	{
		m_gamepads[i]->Unacquire();
		m_gamepads[i]->Release();
	}
	m_numGamepads = 0;

	if(m_keyboardDevice != NULL)
	{
		m_keyboardDevice->Unacquire();
		m_keyboardDevice->Release();
		m_keyboardDevice = NULL;
	}

	if(m_directInput != NULL)
	{
		m_directInput->Release();
		m_directInput = NULL;
	}
}

//--------------------------------------------------------------------------------
bool
PCInputDevice::setupKeyboard()
{
	// Setup the keyboard
	if(FAILED(m_directInput->CreateDevice(GUID_SysKeyboard, &m_keyboardDevice, NULL)))
	{
		m_keyboardDevice = NULL;
		return false;
	}
	if(FAILED(m_keyboardDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return false;
	}
	if(FAILED(m_keyboardDevice->SetCooperativeLevel(PCOS::getWindowHandle(),
		DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
	{
		return false;
	}

	// Setup the event buffer
	DIPROPDWORD dipdw;
	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = DEVICE_BUFFER_SIZE;
	if(FAILED(m_keyboardDevice->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph)))
	{
		return false;
	}

	// Acquire the keyboard device
	if(FAILED(m_keyboardDevice->Acquire()))
	{
		return false;
	}

	return true;
}

//--------------------------------------------------------------------------------
bool
PCInputDevice::setupGamepads()
{
	// Enumerate all the devices
	if(FAILED(m_directInput->EnumDevices(DI8DEVCLASS_GAMECTRL,
		gamepadCallback, this, DIEDFL_ATTACHEDONLY)))
	{		
		return false;
	}

	return true;
}

//--------------------------------------------------------------------------------
BOOL
CALLBACK
PCInputDevice::gamepadCallback(LPCDIDEVICEINSTANCE devInstance, LPVOID ref)
{
	if(static_cast<PCInputDevice*>(ref)->evaluateDevice(devInstance->guidInstance))
	{
		return DIENUM_STOP;
	}

	return DIENUM_CONTINUE;
}

//--------------------------------------------------------------------------------
bool
PCInputDevice::evaluateDevice(GUID deviceGUID)
{
	if(m_numGamepads == MAX_CONTROLLERS)
	{
		return true;
	}
	
	// Create the device
	LPDIRECTINPUTDEVICE8 tempDevice; 
	if(FAILED(m_directInput->CreateDevice(deviceGUID, &tempDevice, NULL)))
	{
		return false;
	}
	
	// Get the device caps
	DIDEVCAPS devCaps;
	devCaps.dwSize = sizeof(DIDEVCAPS); 
	if(FAILED(tempDevice->GetCapabilities(&devCaps)))
	{
		return false;
	}

	// The device must have at least two axes
	if(devCaps.dwPOVs > 0)
	{
		// Setup the device
		if(FAILED(tempDevice->SetDataFormat(&c_dfDIJoystick)))
		{
			tempDevice->Release();
			return false;
		}
		if(FAILED(tempDevice->SetCooperativeLevel(PCOS::getWindowHandle(),
			DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
		{
			tempDevice->Release();
			return false;
		}

		// Setup the event buffer
		DIPROPDWORD dipdw;
		dipdw.diph.dwSize = sizeof(DIPROPDWORD);
		dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
		dipdw.diph.dwObj = 0;
		dipdw.diph.dwHow = DIPH_DEVICE;
		dipdw.dwData = DEVICE_BUFFER_SIZE;
		if(FAILED(tempDevice->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph)))
		{
			return false;
		}

		// Acquire the keyboard device
		if(FAILED(tempDevice->Acquire()))
		{
			return false;
		}

		// Add the device to the list and return whether it is full
		m_gamepads[m_numGamepads] = tempDevice;
		m_numGamepads++;

		return m_numGamepads == MAX_CONTROLLERS;
	}
	else
	{
		// Device not capable, close it
		tempDevice->Release();
	}

	return false;
}

//--------------------------------------------------------------------------------
void
PCInputDevice::processKeyboardInput(InputManagerBase* input, DWORD key, DWORD state)
{
	bool pressed = ((state & 0x80) != 0);
	
	// Check all players
	for(unsigned int i=0; i<MAX_CONTROLLERS; i++)
	{
		for(unsigned int j=0; j<NUM_BUTTONTYPES; j++)
		{
			if(key == m_keyboardBindings[i][j])
			{
				input->setButtonState(i, static_cast<ButtonType>(j), pressed);
				return;
			}
		}
	}
}

//--------------------------------------------------------------------------------
void
PCInputDevice::processGamepadInput(InputManagerBase* input, unsigned int index, DWORD button, DWORD state)
{
	// Directions are implemented on the pov hat
	if(button == DIJOFS_POV(0))
	{
		// Release pov buttons
		input->setButtonState(index, UP, false);
		input->setButtonState(index, DOWN, false);
		input->setButtonState(index, LEFT, false);
		input->setButtonState(index, RIGHT, false);

		// Find new state if any
		switch(state)
		{
			case 0:
				input->setButtonState(index, UP, true);
			break;

			case 4500:
				input->setButtonState(index, UP, true);
				input->setButtonState(index, RIGHT, true);
			break;

			case 9000:
				input->setButtonState(index, RIGHT, true);
			break;

			case 13500:
				input->setButtonState(index, RIGHT, true);
				input->setButtonState(index, DOWN, true);
			break;

			case 18000:
				input->setButtonState(index, DOWN, true);
			break;

			case 22500:
				input->setButtonState(index, LEFT, true);
				input->setButtonState(index, DOWN, true);
			break;

			case 27000:
				input->setButtonState(index, LEFT, true);
			break;

			case 31500:
				input->setButtonState(index, UP, true);
				input->setButtonState(index, LEFT, true);
			break;
		}

		return;
	}

	//if(button == DIJOFS_X)
	//{
	//	if(state < 30000)
	//	{
	//		input->setButtonState(index, LEFT, true);
	//	}
	//	else if(state > 34000)
	//	{
	//		input->setButtonState(index, RIGHT, true);
	//	}
	//	else
	//	{
	//		input->setButtonState(index, LEFT, false);
	//		input->setButtonState(index, RIGHT, false);
	//	}
	//}

	//if(button == DIJOFS_Y)
	//{
	//	if(state < 30000)
	//	{
	//		input->setButtonState(index, UP, true);
	//	}
	//	else if(state > 34000)
	//	{
	//		input->setButtonState(index, DOWN, true);
	//	}
	//	else
	//	{
	//		input->setButtonState(index, UP, false);
	//		input->setButtonState(index, DOWN, false);
	//	}
	//}

	bool pressed = ((state & 0x80) != 0);
	
	// Check all players
	for(unsigned int j=0; j<NUM_BUTTONTYPES; j++)
	{
		if(button == m_gamepadBindings[index][j])
		{
			input->setButtonState(index, static_cast<ButtonType>(j), pressed);
			return;
		}
	}
}

//--------------------------------------------------------------------------------
void
PCInputDevice::standardBindings()
{
	// Always bind first controller
	m_keyboardBindings[0][UP] = DIK_W;
	m_keyboardBindings[0][DOWN] = DIK_S;
	m_keyboardBindings[0][LEFT] = DIK_A;
	m_keyboardBindings[0][RIGHT] = DIK_D;
	m_keyboardBindings[0][BUTTON1] = DIK_SPACE;
	m_keyboardBindings[0][BUTTON2] = DIK_1;
	m_keyboardBindings[0][BUTTON3] = DIK_2;
	m_keyboardBindings[0][BUTTON4] = DIK_3;
	m_keyboardBindings[0][START] = DIK_TAB;

	// Bind any other controllers to nothing
	for(unsigned int i=1; i<MAX_CONTROLLERS; i++)
	{
		for(unsigned int j=0; j<NUM_BUTTONTYPES; j++)
		{
			m_keyboardBindings[i][j] = 0;
		}
	}

	// Standard gamepad controls for all
	for(unsigned int i=0; i<MAX_CONTROLLERS; i++)
	{
		m_gamepadBindings[i][UP] = 0;
		m_gamepadBindings[i][DOWN] = 0;
		m_gamepadBindings[i][LEFT] = 0;
		m_gamepadBindings[i][RIGHT] = 0;
		m_gamepadBindings[i][BUTTON1] = DIJOFS_BUTTON0;
		m_gamepadBindings[i][BUTTON2] = DIJOFS_BUTTON1;
		m_gamepadBindings[i][BUTTON3] = DIJOFS_BUTTON2;
		m_gamepadBindings[i][BUTTON4] = DIJOFS_BUTTON3;
		m_gamepadBindings[i][START] = DIJOFS_BUTTON4;
	}
}

//--------------------------------------------------------------------------------
void
PCInputDevice::loadBindings(const ConfigItem* conf)
{
	// Keyboard
	for(unsigned int i=0; i<MAX_CONTROLLERS; i++)
	{
		std::ostringstream prefix;
		prefix << "keyboard" << i+1 << "_";

		for(unsigned int j=0; j<NUM_BUTTONTYPES; j++)
		{
			if(conf->hasString(prefix.str().append(getButtonSuffix(j))))
			{
				m_keyboardBindings[i][j] = resolveKey(
					conf->getString(prefix.str().append(getButtonSuffix(j))));
			}
		}
	}

	// Gamepads
	for(unsigned int i=0; i<MAX_CONTROLLERS; i++)
	{
		std::ostringstream prefix;
		prefix << "gamepad" << i+1 << "_";

		for(unsigned int j=0; j<NUM_BUTTONTYPES; j++)
		{
			if(conf->hasString(prefix.str().append(getButtonSuffix(j))))
			{
				m_gamepadBindings[i][j] = resolveGamepadButton(
					conf->getString(prefix.str().append(getButtonSuffix(j))));
			}
		}
	}
}

//--------------------------------------------------------------------------------
DWORD
PCInputDevice::resolveKey(const std::string& keyName)
{
	if(!keyName.compare("none")) return 0;
	if(!keyName.compare("q")) return DIK_Q;
	if(!keyName.compare("w")) return DIK_W;
	if(!keyName.compare("e")) return DIK_E;
	if(!keyName.compare("r")) return DIK_R;
	if(!keyName.compare("t")) return DIK_T;
	if(!keyName.compare("y")) return DIK_Y;
	if(!keyName.compare("u")) return DIK_U;
	if(!keyName.compare("i")) return DIK_I;
	if(!keyName.compare("o")) return DIK_O;
	if(!keyName.compare("p")) return DIK_P;
	if(!keyName.compare("a")) return DIK_A;
	if(!keyName.compare("s")) return DIK_S;
	if(!keyName.compare("d")) return DIK_D;
	if(!keyName.compare("f")) return DIK_F;
	if(!keyName.compare("g")) return DIK_G;
	if(!keyName.compare("h")) return DIK_H;
	if(!keyName.compare("j")) return DIK_J;
	if(!keyName.compare("k")) return DIK_K;
	if(!keyName.compare("l")) return DIK_L;
	if(!keyName.compare("z")) return DIK_Z;
	if(!keyName.compare("x")) return DIK_X;
	if(!keyName.compare("c")) return DIK_C;
	if(!keyName.compare("v")) return DIK_V;
	if(!keyName.compare("b")) return DIK_B;
	if(!keyName.compare("n")) return DIK_N;
	if(!keyName.compare("m")) return DIK_M;
	if(!keyName.compare("space")) return DIK_SPACE;
	if(!keyName.compare("tab")) return DIK_TAB;
	if(!keyName.compare("return")) return DIK_RETURN;
	if(!keyName.compare("leftControl")) return DIK_LCONTROL;
	if(!keyName.compare("rightControl")) return DIK_RCONTROL;
	if(!keyName.compare("up")) return DIK_UPARROW;
	if(!keyName.compare("down")) return DIK_DOWNARROW;
	if(!keyName.compare("left")) return DIK_LEFTARROW;
	if(!keyName.compare("right")) return DIK_RIGHTARROW;
	if(!keyName.compare("0")) return DIK_0;
	if(!keyName.compare("1")) return DIK_1;
	if(!keyName.compare("2")) return DIK_2;
	if(!keyName.compare("3")) return DIK_3;
	if(!keyName.compare("4")) return DIK_4;
	if(!keyName.compare("5")) return DIK_5;
	if(!keyName.compare("6")) return DIK_6;
	if(!keyName.compare("7")) return DIK_7;
	if(!keyName.compare("8")) return DIK_8;
	if(!keyName.compare("9")) return DIK_9;
	if(!keyName.compare("backspace")) return DIK_BACKSPACE;
	if(!keyName.compare("num0")) return DIK_NUMPAD0;
	if(!keyName.compare("num1")) return DIK_NUMPAD1;
	if(!keyName.compare("num2")) return DIK_NUMPAD2;
	if(!keyName.compare("num3")) return DIK_NUMPAD3;
	if(!keyName.compare("num4")) return DIK_NUMPAD4;
	if(!keyName.compare("num5")) return DIK_NUMPAD5;
	if(!keyName.compare("num6")) return DIK_NUMPAD6;
	if(!keyName.compare("num7")) return DIK_NUMPAD7;
	if(!keyName.compare("num8")) return DIK_NUMPAD8;
	if(!keyName.compare("num9")) return DIK_NUMPAD9;
	if(!keyName.compare("leftShift")) return DIK_LSHIFT;
	if(!keyName.compare("rightShift")) return DIK_RSHIFT;
	if(!keyName.compare("delete")) return DIK_DELETE;
	if(!keyName.compare("ins")) return DIK_INSERT;
	if(!keyName.compare("pgup")) return DIK_PGUP;
	if(!keyName.compare("pgdn")) return DIK_PGDN;
	if(!keyName.compare("home")) return DIK_HOME;
	if(!keyName.compare("end")) return DIK_END;

	return 0;
}

//--------------------------------------------------------------------------------
DWORD
PCInputDevice::resolveGamepadButton(const std::string& name)
{
	if(!name.compare("none")) return 0;
	if(!name.compare("button1")) return DIJOFS_BUTTON0;
	if(!name.compare("button2")) return DIJOFS_BUTTON1;
	if(!name.compare("button3")) return DIJOFS_BUTTON2;
	if(!name.compare("button4")) return DIJOFS_BUTTON3;
	if(!name.compare("button5")) return DIJOFS_BUTTON4;
	if(!name.compare("button6")) return DIJOFS_BUTTON5;
	if(!name.compare("button7")) return DIJOFS_BUTTON6;
	if(!name.compare("button8")) return DIJOFS_BUTTON7;
	if(!name.compare("button9")) return DIJOFS_BUTTON8;
	if(!name.compare("button10")) return DIJOFS_BUTTON9;
	if(!name.compare("button11")) return DIJOFS_BUTTON10;
	if(!name.compare("button12")) return DIJOFS_BUTTON11;
	if(!name.compare("button13")) return DIJOFS_BUTTON12;
	if(!name.compare("button14")) return DIJOFS_BUTTON13;
	if(!name.compare("button15")) return DIJOFS_BUTTON14;
	if(!name.compare("button16")) return DIJOFS_BUTTON15;

	return 0;
}

//--------------------------------------------------------------------------------
std::string
PCInputDevice::getButtonSuffix(unsigned int button)
{
	switch(static_cast<ButtonType>(button))
	{
		case UP:
			return "UP";
		case DOWN:
			return "DOWN";
		case LEFT:
			return "LEFT";
		case RIGHT:
			return "RIGHT";
		case BUTTON1:
			return "BTN1";
		case BUTTON2:
			return "BTN2";
		case BUTTON3:
			return "BTN3";
		case BUTTON4:
			return "BTN4";
		case START:
			return "START";
	}

	return "";
}

#endif

