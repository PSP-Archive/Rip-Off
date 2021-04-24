#pragma once

#include <cassert>

class InputManagerBase;
class ConfigItem;

// Disable warning for unreferenced formal parameters as this is an interface
#pragma warning( disable: 4100 )

//--------------------------------------------------------------------------------
class InputDeviceIF
{
public:
	// Enumeration for implemented buttons
	enum ButtonType
	{
		BUTTON1 = 0,
		BUTTON2,
		BUTTON3,
		BUTTON4,
		UP,
		DOWN,
		LEFT,
		RIGHT,
		START,

#ifdef _SPSP
		SELECT,
		MOVEUP,
		TURNLEFT,
		TURNRIGHT,
#endif

		NUM_BUTTONTYPES,
	};
	
	// Max number of controller supported
	static const int MAX_CONTROLLERS = 4;

	// Called when input should be initialized.
	bool init(const ConfigItem*) { assert(!"Interface not implemented"); }

	// Implement to update the status of the input manager passed as parameter.
	void update(InputManagerBase* input) { assert(!"Interface not implemented"); }

	// Called when input should be cleaned up.
	void cleanUp() { assert(!"Interface not implemented"); }
};
