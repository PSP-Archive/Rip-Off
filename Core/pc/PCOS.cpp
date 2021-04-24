#ifdef _PC

#include "pc/PCOS.h"
#include "foundation/ConfigItem.h"

HWND PCOS::m_hWnd = NULL;
PCOS* PCOS::s_os = NULL;

const std::string PCOS::CFGVAR_FULLSCREEN("fullscreen");
const std::string PCOS::CFGVAR_WINDOWSIZE("windowSize");

// Always place as last include and only in cpp files!!
#include "foundation/Debug.h"

//--------------------------------------------------------------------------------
PCOS::PCOS(const char* className, const char* windowName) :
	m_className(className),
	m_windowName(windowName),
	m_fullscreen(false),
	m_quitRequest(false)
{
	assert(!s_os);
	
	s_os = this;
	m_hInstance = GetModuleHandle(NULL);

	SetScreenSize(400, 300);
}

//--------------------------------------------------------------------------------
bool
PCOS::init(const ConfigItem* config)
{
	// Find the window size
	if(config && config->hasVector(CFGVAR_WINDOWSIZE))
	{
		Vector3f v = config->getVector(CFGVAR_WINDOWSIZE);
		SetScreenSize(int(v.x()), int(v.y()));
	}
	
	// Clear out the window class for use
    ZeroMemory(&m_wc, sizeof(WNDCLASSEX));

    // Fill in the struct with the needed information
    m_wc.cbSize = sizeof(WNDCLASSEX);
    m_wc.style = CS_HREDRAW | CS_VREDRAW;
    m_wc.lpfnWndProc = WindowProc;
    m_wc.hInstance = m_hInstance;
    m_wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    m_wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	m_wc.lpszClassName = m_className.c_str();

    // register the window class
    RegisterClassEx(&m_wc);

	// create the window and use the result as the handle
    m_hWnd = CreateWindowEx(NULL, m_className.c_str(), m_windowName.c_str(),
		WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
		0, 0, GetScreenWidth(), GetScreenHeight(), NULL, NULL, m_hInstance, NULL);

    // display the window on the screen
	ShowWindow(m_hWnd, SW_SHOW);

    // enter the main loop:
	m_hdc = GetDC(m_hWnd);
	if(m_hdc == NULL)
	{
		return false;
	}

	if(!SetPF(m_hdc))
	{
		return false;
	}

	//get an openGL context
	HGLRC hglrc = wglCreateContext(m_hdc);

	//make context current
	wglMakeCurrent(m_hdc, hglrc);

	// Hide the cursor
	ShowCursor(FALSE);

	// Check for fullscreen and set it
	if(config && config->hasInteger(CFGVAR_FULLSCREEN) &&
		config->getInteger(CFGVAR_FULLSCREEN) != 0)
	{
		setFullscreen(true);
	}

	return true;
}

//--------------------------------------------------------------------------------
BOOL
PCOS::SetPF(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
 
	pfd.cAccumBits = 0;
	pfd.cAccumAlphaBits = 0;
	pfd.cAccumBlueBits = 0;
	pfd.cAccumGreenBits = 0;
	pfd.cAccumRedBits = 0;
	pfd.cAlphaBits = 8;
	pfd.cAuxBuffers = 0;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;
	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
 
	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	return SetPixelFormat(hdc, n, &pfd);
}

//--------------------------------------------------------------------------------
LRESULT
CALLBACK
PCOS::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // sort through and find what code to run for the message given
    switch(message)
    {
		// Window is being resized
		case WM_SIZE:
			glViewport(0, 0, LOWORD(lParam), HIWORD(lParam));
		return 0;
		
		// Window is closed
		case WM_DESTROY:
			PostQuitMessage(0);
		return 0;

		// Check for keys
		case WM_KEYDOWN:
			switch(wParam)
			{
				// Os specific exit key
				case VK_ESCAPE:
					s_os->m_quitRequest = true;
				break;

				// Os specific fullscreen key
				case VK_RETURN:
					if(GetAsyncKeyState(VK_LCONTROL) != 0)
					{
						s_os->setFullscreen(!s_os->m_fullscreen);
					}
				break;
			}
		return 0;
    }

    // Handle any messages the switch statement didn't
    return DefWindowProc(hWnd, message, wParam, lParam);
} 

//--------------------------------------------------------------------------------
void
PCOS::preUpdate()
{
    MSG msg;
	// Process all messages in the queue
	while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		// Check if quit
		if(msg.message == WM_QUIT)
		{
			m_quitRequest = true;
		}

		// Translate keystroke messages into the right format
		TranslateMessage(&msg);

		// Send the message to the WindowProc function
		DispatchMessage(&msg);
	}
}

//--------------------------------------------------------------------------------
void
PCOS::postUpdate()
{
	SwapBuffers(m_hdc);
}

//--------------------------------------------------------------------------------
void
PCOS::cleanUp()
{
	PostMessage(m_hWnd, WM_CLOSE, 0, 0);
	PostQuitMessage(0);
}

//--------------------------------------------------------------------------------
void
PCOS::setFullscreen(bool f)
{
	// anything to do?
	if(f == m_fullscreen)
	{
		return;
	}

	// get current window style, so we can modify it
	DWORD dwStyle = GetWindowLong(m_hWnd, GWL_STYLE);
	
	// Enter fullscreen
	if(f)
	{
		DEVMODE dm;

		// query display settings
		if (!EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm))
		{
			return;
		}

		// window size: fill screen
		int width  = dm.dmPelsWidth;
		int height = dm.dmPelsHeight;

		// save window rect.
		if (!GetWindowRect(m_hWnd, &m_oldRect))
		{
			return;
		}

		// remove caption, border and sizing frame
		dwStyle &= ~(WS_CAPTION | WS_SIZEBOX);

		// apply new style
		if (!SetWindowLong(m_hWnd, GWL_STYLE, dwStyle))
		{
			//dbg_W32LastError("SetWindowLong(GWL_STYLE) failed");
		}

		// resize window and bring to top
		if (!SetWindowPos (m_hWnd, HWND_TOP, 0,0, width, height, 0))
		{
			//dbg_W32LastError("SetWindowPos failed");
		}

		m_fullscreen = true;
		SetScreenSize(width, height);
	}
	// Leave fullscreen
	else
	{
		// restore original window size
		int x = m_oldRect.left;
		int y = m_oldRect.top;
		int width = m_oldRect.right  - m_oldRect.left;
		int height= m_oldRect.bottom - m_oldRect.top;

		// add overlapped window attributes
		dwStyle |= WS_OVERLAPPEDWINDOW;

		// apply new style
		if (!SetWindowLong(m_hWnd, GWL_STYLE, dwStyle))
		{
			return;
		}

		// resize window and bring to top
		if (!SetWindowPos(m_hWnd, 0, x,y, width,height, SWP_NOZORDER))
		{
			return;
		}

		m_fullscreen = false;
		SetScreenSize(width, height);
	}
}

#endif
