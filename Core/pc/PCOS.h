#pragma once

#include <cassert>
#include <string>

#include <windows.h>
#include <windowsx.h>
#include <gl/gl.h>

#pragma comment (lib, "opengl32.lib")

#include "application/OSIF.h"

//--------------------------------------------------------------------------------
/**
	PC implementation with the OS (Windows API).
	
	NOTE:
	Always instantiate one OS object per window application as only one windows
	is supported.
*/
class PCOS : public OSIF
{
public:
	// Ctor
	PCOS(const char* className, const char* windowName);
	
	// Interface methods
	bool init(const ConfigItem* config);
	void preUpdate();
	void postUpdate();
	void cleanUp();
	bool quitRequested() { return m_quitRequest; }

	// Sets the windows size
	void setWindowsSize(int w, int h);

	// Static method to retrieve the window handle
	static HWND getWindowHandle() { return m_hWnd; }

	// The main message handler for the program
	static LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

private:
	// Config constants
	static const std::string CFGVAR_FULLSCREEN;
	static const std::string CFGVAR_WINDOWSIZE;
	
	// Activates/deactivates fullscreen
	void setFullscreen(bool f);
	
	// Sets the pixel format
	BOOL SetPF(HDC hdc);

	// Handles
	static HWND m_hWnd;
    WNDCLASSEX m_wc;
	HDC m_hdc;

	// Winmain parameters
	HINSTANCE m_hInstance;
	std::string m_className;
	std::string m_windowName;

	// Quit requested from the os
	bool m_quitRequest;

	// Flag indicating if the app is in fullscreen
	bool m_fullscreen;

	// Previous window rect
	RECT m_oldRect;

	// Reference to self to allow access from WinProc
	// A BIT DIRTY, FIX THIS!!
	static PCOS* s_os;
};
