#pragma once

#include "foundation/DebugIF.h"
#include <string>

//--------------------------------------------------------------------------------
/**
	PC specific Debug functionalities.
*/
class PSPDebug : public DebugIF
{
public:
	PSPDebug();

protected:
	void onOutput(const std::string& text);
};

