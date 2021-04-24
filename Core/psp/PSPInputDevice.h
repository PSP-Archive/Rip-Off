/* VERSION HISTORY

25/02/2010 - Ewe Yee Seong - setup input parsing

*/

#pragma once

#include "input/InputDeviceIF.h"
#include <ctrlsvc.h>
#include <string>
#include <sstream>

/*	=====================================================================
		PSP implementation of input
	=====================================================================	*/
class PSPInputDevice : public InputDeviceIF
{
public:
	PSPInputDevice();
	bool init(const ConfigItem* conf);
	void update(InputManagerBase* input);
	void cleanUp();

private:
	// Sets the default bindings
	void standardBindings();

	// Sets the default bindings
	void loadBindings(const ConfigItem* conf);

	// Returns the suffix of config buttons
	_STL::string getButtonSuffix(unsigned int button);

	// Sets the default bindings
	unsigned int resolveGamepadButton(const _STL::string& name);

	// Processes a controller
	void processGamepadInput(InputManagerBase* input, SceCtrlData buf);


	unsigned int m_numGamepads;

	// Store current pressed button
	static unsigned int m_button;
	// Store previous pressed button
	static unsigned int m_prevButton;

	// Store gamepad binding data
	unsigned int m_gamepadBindings[MAX_CONTROLLERS][NUM_BUTTONTYPES];
};
