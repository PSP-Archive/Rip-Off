#pragma once

#include <cassert>
#include <string>


#include "application/OSIF.h"

//--------------------------------------------------------------------------------
/**
	PSP implementation with the OS
	
	NOTE:
	Always instantiate one OS object per window application as only one windows
	is supported.
*/
class PSPOS : public OSIF
{
public:
	// Ctor
	PSPOS(const char* className);
	
	// Interface methods
	bool init(const ConfigItem* config);
	void preUpdate();
	void postUpdate();
	void cleanUp();
	bool quitRequested() { return m_quitRequest; }

	// Sets the windows size
	void setWindowsSize(int w, int h);

	// Static method to retrieve the window handle
	//static HWND getWindowHandle() { return m_hWnd; }

	// The main message handler for the program
	//static LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

private:
	// Config constants
	static const std::string CFGVAR_FULLSCREEN;
	static const std::string CFGVAR_WINDOWSIZE;
	
	// Activates/deactivates fullscreen
	void setFullscreen(bool f);
	
	// Sets the pixel format
	//BOOL SetPF(HDC hdc);

	// Handles
	//static HWND m_hWnd;
 //   WNDCLASSEX m_wc;
	//HDC m_hdc;

	// Winmain parameters
	//HINSTANCE m_hInstance;
	std::string m_className;
	std::string m_windowName;

	// Quit requested from the os
	bool m_quitRequest;

	// Flag indicating if the app is in fullscreen
	bool m_fullscreen;

	// Previous window rect
	//RECT m_oldRect;

	// Reference to self to allow access from WinProc
	// A BIT DIRTY, FIX THIS!!
	static PSPOS* s_os;
};
