#ifdef _SPSP

#include <iostream>
#include "psp/PSPDebug.h"

using namespace std;

//--------------------------------------------------------------------------------
PSPDebug::PSPDebug()
{
	// empty
}

//--------------------------------------------------------------------------------
void
PSPDebug::onOutput(const string& text)
{
	cout << text << endl;
}

#endif