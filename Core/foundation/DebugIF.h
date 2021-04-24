#pragma once

#include <string>

//--------------------------------------------------------------------------------
/**
	Replace the default new with the debug one.
*/
#ifdef _DEBUG
	#include <iostream>

#if _PC
	#include <crtdbg.h>
	// Disabled as this conflicts with some STL stuff
	#define new new(_NORMAL_BLOCK,__FILE__, __LINE__)
#endif


#endif

//--------------------------------------------------------------------------------
/**
	Generic Debug interface. Contains all debug related functions. The platform
	specific ones will be implemented in the platform specific versions.

	NOTE:
	Memory leask detection might not be compatible with all platforms. If it is
	not gotta move the Visual Studio code to the PC implementaion.
*/
class DebugIF
{
public:
	DebugIF();

	// Outputs debug text. Override the protected method and NOT this one as it
	// takes of compiling only in debug configuration. 
	void output(const std::string& text);

	// Activates memory leak detection for visual studio
	void ActivateMemoryLeakCheck();

protected:
	// Outputs debug text. Should be implemented by outputting to the console
	// or some sort of debug log file. Each text string should be outputted to
	// to a different line. 
	virtual void onOutput(const std::string& text) = 0;
};


//--------------------------------------------------------------------------------
inline
void
DebugIF::output(const std::string& text)
{
	#ifdef _DEBUG
		onOutput(text);
	#endif
}

//--------------------------------------------------------------------------------
inline
void
DebugIF::ActivateMemoryLeakCheck()
{
	#ifdef _DEBUG
		//int flag = _CrtSetDbgFlag( _CRTDBG_REPORT_FLAG );
		//flag |= _CRTDBG_LEAK_CHECK_DF;
		//flag |= _CRTDBG_CHECK_ALWAYS_DF;	
		//flag &= ~_CRTDBG_DELAY_FREE_MEM_DF;
		//_CrtSetDbgFlag(flag);
	#endif
}
