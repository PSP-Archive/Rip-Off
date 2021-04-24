#include "PSPGfx3DInitializer.h"

#ifdef _3D
#ifdef _SPSP

static ScePspFMatrix4	matrix_stack[8+8+32+0];

void PSPGfx3DInitializer::initializeForRendering(int *pWidth, int *pHeight, int lightOn) const{
	
	//-------------------------------------------------------

	//sceGuDrawBuffer(SCEGU_PF8888, SCEGU_VRAM_BP32_0, SCEGU_VRAM_WIDTH);
	//sceGuDispBuffer(SCEGU_SCR_WIDTH, SCEGU_SCR_HEIGHT,
	//				SCEGU_VRAM_BP32_1, SCEGU_VRAM_WIDTH);
	//sceGuDepthBuffer(SCEGU_VRAM_BP32_2, SCEGU_VRAM_WIDTH);

	sceGuOffset(SCEGU_SCR_OFFSETX, SCEGU_SCR_OFFSETY);
	sceGuViewport(2048, 2048, SCEGU_SCR_WIDTH, SCEGU_SCR_HEIGHT);
	sceGuDepthRange(50000, 10000);

	sceGuScissor(0, 0, SCEGU_SCR_WIDTH, SCEGU_SCR_HEIGHT);
	sceGuEnable(SCEGU_SCISSOR_TEST);

	//-------------------------------------------------------

	sceGuDepthFunc(SCEGU_GEQUAL);
	sceGuEnable(SCEGU_DEPTH_TEST);

	sceGuFrontFace(SCEGU_CW);

	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

	getScreenSize(pWidth,pHeight);

	//if (lightOn){
	//	glEnable(GL_LIGHTING);
	//	glShadeModel(GL_SMOOTH);
	//	glEnable(GL_NORMALIZE);
	//}

	sceGuShadeModel(SCEGU_SMOOTH);
	sceGuColor(0xffffffff);

	sceGuBlendFunc(SCEGU_ADD, SCEGU_SRC_ALPHA, SCEGU_ONE_MINUS_SRC_ALPHA, 0, 0);
	//sceGuBlendFunc(SCEGU_ADD, SCEGU_SRC_ALPHA, SCEGU_ONE, 0, 0);
	sceGuEnable(SCEGU_BLEND);
	
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	//sceGuStart(SCEGU_IMMEDIATE, disp_list, sizeof(disp_list));
	sceGuClear(SCEGU_CLEAR_ALL);

	//sceGumSetMatrixStack(&matrix_stack[0], 8, 8, 32, 8);

	sceGumMatrixMode(SCEGU_MATRIX_PROJECTION);
	sceGumLoadIdentity();
	sceGumPerspective(SCEGU_RAD(45.0f), SCEGU_SCR_ASPECT,
					1.000000f, 100.000000f);

	sceGumMatrixMode(SCEGU_MATRIX_WORLD);

}

void PSPGfx3DInitializer::startRendering() const{
	sceGuClearColor(0x00000000);
	sceGuClearDepth(0);
	sceGuClearStencil(0);
	
	sceGuDisplay(SCEGU_DISPLAY_ON);
	//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

}

void PSPGfx3DInitializer::getScreenSize(int *pWidth, int *pHeight) const{
	*pWidth=SCEGU_SCR_WIDTH;
	*pHeight=SCEGU_SCR_HEIGHT;
}

#endif
#endif