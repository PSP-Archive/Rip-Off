#pragma once

#include <dinput.h>

#include "input/InputDeviceIF.h"

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

//--------------------------------------------------------------------------------
class PCInputDevice : public InputDeviceIF
{
public:
	PCInputDevice();
	bool init(const ConfigItem* conf);
	void update(InputManagerBase* input);
	void cleanUp();

	// Check is the device with the specified device id is a valid gamepad and
	// adds it if it is valid. Returns whether the device list is full.
	bool evaluateDevice(GUID deviceGUID);

private:
	// Sets up the keyboard
	bool setupKeyboard();

	// Check for gamepads and sets them up if available
	bool setupGamepads();

	// Sets the default bindings
	void standardBindings();

	// Sets the default bindings
	void loadBindings(const ConfigItem* conf);

	// Returns the suffix of config buttons
	std::string getButtonSuffix(unsigned int button);

	// Sets the default bindings
	DWORD resolveKey(const std::string& keyName);

	// Sets the default bindings
	DWORD resolveGamepadButton(const std::string& name);

	// Processes the keyboard input
	void processKeyboardInput(InputManagerBase* input, DWORD key, DWORD state);

	// Processes a controller
	void processGamepadInput(InputManagerBase* input, unsigned int index, DWORD key, DWORD state);

	// Max size of the keyboard buffer
	static const int DEVICE_BUFFER_SIZE = 32;
	DIDEVICEOBJECTDATA m_deviceBuffer[DEVICE_BUFFER_SIZE];

	// Direct input object
	LPDIRECTINPUT8 m_directInput;

	// Keyboard stuff
	LPDIRECTINPUTDEVICE8 m_keyboardDevice;

	static BOOL CALLBACK gamepadCallback(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef);

	// Gamepads
	LPDIRECTINPUTDEVICE8 m_gamepads[MAX_CONTROLLERS];
	unsigned int m_numGamepads;

	DWORD m_keyboardBindings[MAX_CONTROLLERS][NUM_BUTTONTYPES];
	DWORD m_gamepadBindings[MAX_CONTROLLERS][NUM_BUTTONTYPES];
};
