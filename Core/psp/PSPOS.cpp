#ifdef _SPSP

//320x240

#include "psp/PSPOS.h"
#include "foundation/ConfigItem.h"

#include <libgu.h>
#include <libgum.h>
#include <displaysvc.h>
#include <kernel.h>

PSPOS* PSPOS::s_os = NULL;

const std::string PSPOS::CFGVAR_FULLSCREEN("fullscreen");
const std::string PSPOS::CFGVAR_WINDOWSIZE("windowSize");

//this list holds commands to the GU
static char	disp_list[0x10000] __attribute__((aligned(64)));

//define the matrix stack
static ScePspFMatrix4	matrix_stack[8+8+32+8];

// Always place as last include and only in cpp files!!
//#include "foundation/Debug.h"

//--------------------------------------------------------------------------------
PSPOS::PSPOS(const char* className) :
	m_className(className),
	m_fullscreen(false),
	m_quitRequest(false)
{
	assert(!s_os);
	
	s_os = this;

	SetScreenSize(SCEGU_SCR_WIDTH, SCEGU_SCR_HEIGHT);
	//SetScreenSize(320, 240);
	//SetScreenSize(368, 208);
}

//--------------------------------------------------------------------------------
bool
PSPOS::init(const ConfigItem* config)
{
	//Initialize the graphics system
	sceGuInit ();

	//Set the buffer for the rendering commands. Set to render immediately
	sceGuStart(SCEGU_IMMEDIATE, disp_list, sizeof(disp_list));

	//Setup 16-bit draw buffer. Back buffer?
	sceGuDrawBuffer(SCEGU_PF8888, SCEGU_VRAM_BP32_0, SCEGU_VRAM_WIDTH);

	//Setup 16-bit display buffer. This is the screen
	sceGuDispBuffer(SCEGU_SCR_WIDTH, SCEGU_SCR_HEIGHT,
					SCEGU_VRAM_BP32_1, SCEGU_VRAM_WIDTH);

	//Setup the depth buffer
	sceGuDepthBuffer(SCEGU_VRAM_BP32_2, SCEGU_VRAM_WIDTH);

	//Set the offset. PSP will render the centre of the 4096x4096 area
	sceGuOffset(SCEGU_SCR_OFFSETX, SCEGU_SCR_OFFSETY);

	//Set up a viewport of size 480x272 with the centre at the origin
	sceGuViewport(2048, 2048, SCEGU_SCR_WIDTH, SCEGU_SCR_HEIGHT);

	sceGuScissor(0, 0, SCEGU_SCR_WIDTH, SCEGU_SCR_HEIGHT);
	sceGuEnable(SCEGU_SCISSOR_TEST);

	//sceGuAlphaFunc(SCEGU_GREATER, 0x00, 0xff);
	//sceGuEnable(SCEGU_ALPHA_TEST);

	sceGuDepthRange(50000, 10000);

	//Enable the depth buffer
	sceGuDepthFunc(SCEGU_GEQUAL);
	sceGuEnable(SCEGU_DEPTH_TEST);

	//Setup backface culling
	sceGuFrontFace(SCEGU_CW);

	//Enable clipping
	sceGuEnable(SCEGU_CLIP_PLANE);

	//Set the matrix stack to define array
	sceGumSetMatrixStack(&matrix_stack[0], 8, 8, 32, 8);



	//Set the projection matrix to a 45 degree viewing angle
	sceGumMatrixMode(SCEGU_MATRIX_PROJECTION);
	sceGumLoadIdentity();
	sceGumOrtho(1, -1, -1, 1, 0, 1);

		/*sceGumPerspective(SCEGU_RAD(45.0f), SCEGU_SCR_ASPECT,
					1.000000f, 100.000000f);*/
	//sceGumOrtho(0, SCEGU_SCR_WIDTH, 0, SCEGU_SCR_HEIGHT, -1.0f, 1.0f);


		//ScePspFVector3 eye = {0,0,-2.5};
		//ScePspFVector3 centre = {0,0,0};
		//ScePspFVector3 up = {0,1,0};

		//sceGumLookAt(&eye, &centre, &up);

	//Switch to the world matrix
	sceGumMatrixMode(SCEGU_MATRIX_WORLD);
	sceGumLoadIdentity();
	
	sceGuClearColor(0x00000000);

	//clear the depth buffer
	sceGuClearDepth(0);
	sceGuClearStencil(0);

	//Disable lighting
	sceGuDisable(SCEGU_LIGHTING);

	//Disable texture
	sceGuDisable(SCEGU_TEXTURE);
	
	//Smooth
	sceGuShadeModel(SCEGU_SMOOTH);



	//finish with this context
	sceGuFinish();
	sceGuSync(SCEGU_SYNC_FINISH, SCEGU_SYNC_WAIT);
	sceDisplayWaitVblankStart();

	//turn the display on
	sceGuDisplay(SCEGU_DISPLAY_ON);

	//// Find the window size
	//if(config && config->hasVector(CFGVAR_WINDOWSIZE))
	//{
	//	Vector3f v = config->getVector(CFGVAR_WINDOWSIZE);
	//	SetScreenSize(int(v.x()), int(v.y()));
	//}
	//
	//// Clear out the window class for use
 //   ZeroMemory(&m_wc, sizeof(WNDCLASSEX));

 //   // Fill in the struct with the needed information
 //   m_wc.cbSize = sizeof(WNDCLASSEX);
 //   m_wc.style = CS_HREDRAW | CS_VREDRAW;
 //   m_wc.lpfnWndProc = WindowProc;
 //   m_wc.hInstance = m_hInstance;
 //   m_wc.hCursor = LoadCursor(NULL, IDC_ARROW);
 //   m_wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	//m_wc.lpszClassName = m_className.c_str();

 //   // register the window class
 //   RegisterClassEx(&m_wc);

	//// create the window and use the result as the handle
 //   m_hWnd = CreateWindowEx(NULL, m_className.c_str(), m_windowName.c_str(),
	//	WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
	//	0, 0, GetScreenWidth(), GetScreenHeight(), NULL, NULL, m_hInstance, NULL);

 //   // display the window on the screen
	//ShowWindow(m_hWnd, SW_SHOW);

 //   // enter the main loop:
	//m_hdc = GetDC(m_hWnd);
	//if(m_hdc == NULL)
	//{
	//	return false;
	//}

	//if(!SetPF(m_hdc))
	//{
	//	return false;
	//}

	////get an openGL context
	//HGLRC hglrc = wglCreateContext(m_hdc);

	////make context current
	//wglMakeCurrent(m_hdc, hglrc);

	//// Hide the cursor
	//ShowCursor(FALSE);

	//// Check for fullscreen and set it
	//if(config && config->hasInteger(CFGVAR_FULLSCREEN) &&
	//	config->getInteger(CFGVAR_FULLSCREEN) != 0)
	//{
	//	setFullscreen(true);
	//}

	return true;
}

//--------------------------------------------------------------------------------


//--------------------------------------------------------------------------------
void
PSPOS::preUpdate()
{
	sceGuStart(SCEGU_IMMEDIATE, disp_list, sizeof(disp_list));
	sceGuClear(SCEGU_CLEAR_ALL);
	sceGumLoadIdentity();
}

//--------------------------------------------------------------------------------
void
PSPOS::postUpdate()
{
	//sceGuFinish();
	int size = sceGuFinish() ;
	sceKernelDcacheWritebackRange( disp_list, size ) ;

	sceGuSync(SCEGU_SYNC_FINISH, SCEGU_SYNC_WAIT);
	sceDisplayWaitVblankStart();
	sceGuSwapBuffers();		
}

//--------------------------------------------------------------------------------
void
PSPOS::cleanUp()
{
	sceGuTerm();
}

//--------------------------------------------------------------------------------
void
PSPOS::setFullscreen(bool f)
{
	
}

#endif
