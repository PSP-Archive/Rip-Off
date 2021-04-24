#pragma once
#include "../../ui/WidgetRendererIF.h"
#include "foundation/Vector2f.h"

#include <libgu.h>
#include <libgum.h>
#include <ctrlsvc.h>
#include <kernel.h>
#include <psptypes.h>
#include <displaysvc.h>

class PSPWidgetRenderer:public WidgetRendererIF{
public:
	void initRendering(const Vector2f& position, const Vector3f& color, float scale) const;
	void dismissRendering() const;
};

inline void PSPWidgetRenderer::initRendering(const Vector2f& position, const Vector3f& color, float scale) const{
#ifdef _3D
#ifdef _PC
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();	
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();	
	glLoadIdentity();
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	//IMPORTANT: IF WE ADD OTHER OBJECTS TO BE DRAWN HERE WE MUST DISABLE DEPTH_TEST
	//glDisable(GL_DEPTH_TEST);
	#elif _SPSP

		sceGumMatrixMode(SCEGU_MATRIX_PROJECTION);
		sceGumPushMatrix();
		sceGumLoadIdentity();
		//ScePspFVector3 v;
		//v.x=0; v.y=0; v.z=-1;
		//sceGumTranslate(&v);
		//sceGumOrtho(1, -1, -1, 1, 0, 1);
		//sceGumOrtho(1, -1, -1, 1, -1, 0);
		sceGumMatrixMode(SCEGU_MATRIX_WORLD);
		sceGumPushMatrix();
		sceGumLoadIdentity();
		
		/*

		//sceGuStart(SCEGU_IMMEDIATE, disp_list, sizeof(disp_list));
		sceGuDrawBuffer(SCEGU_PF8888, SCEGU_VRAM_BP32_0, SCEGU_VRAM_WIDTH);
		sceGuDispBuffer(SCEGU_SCR_WIDTH, SCEGU_SCR_HEIGHT,
						SCEGU_VRAM_BP32_1, SCEGU_VRAM_WIDTH);
		sceGuDepthBuffer(SCEGU_VRAM_BP32_2, SCEGU_VRAM_WIDTH);

		sceGuOffset(SCEGU_SCR_OFFSETX, SCEGU_SCR_OFFSETY);
		sceGuViewport(2048, 2048, SCEGU_SCR_WIDTH, SCEGU_SCR_HEIGHT);
		sceGuDepthRange(50000, 10000);

		sceGuScissor(0, 0, SCEGU_SCR_WIDTH, SCEGU_SCR_HEIGHT);
		sceGuEnable(SCEGU_SCISSOR_TEST);

		sceGuBlendFunc(SCEGU_ADD, SCEGU_SRC_ALPHA, SCEGU_ONE_MINUS_SRC_ALPHA, 0, 0);
		sceGuEnable(SCEGU_BLEND);

		sceGuDepthFunc(SCEGU_GEQUAL);
		sceGuEnable(SCEGU_DEPTH_TEST);

		sceGuFrontFace(SCEGU_CW);

		sceGuShadeModel(SCEGU_SMOOTH);

		//sceGumSetMatrixStack(&matrix_stack[0], 8, 8, 32, 0);

		sceGumMatrixMode(SCEGU_MATRIX_PROJECTION);
		sceGumLoadIdentity();
		sceGumPerspective(SCEGU_RAD(45.0f), SCEGU_SCR_ASPECT,
						1.000000f, 100.000000f);

		sceGumMatrixMode(SCEGU_MATRIX_WORLD);

		sceGuClearColor(0xffff4040);
		sceGuClearDepth(0);
		sceGuClearStencil(0);

		sceGuFinish();
		sceGuSync(SCEGU_SYNC_FINISH, SCEGU_SYNC_WAIT);
		sceDisplayWaitVblankStart();

		sceGuDisplay(SCEGU_DISPLAY_ON);*/
	#endif
#else
	sceGumPushMatrix();


	unsigned int number = ((unsigned char)(255)) << 24;
	number |= ((unsigned char)(color[2] * 255)) << 16;
	number |= ((unsigned char)(color[1] * 255)) << 8;
	number |= ((unsigned char)(color[0] * 255));

	
	//// Set the color and width
	sceGuColor(number);


	//glLineWidth(0.6f*scale);

	ScePspFVector3 s = {-1.0f,1.0f,1.0f};
	sceGumScale(&s);
#endif
	ScePspFVector3 vector = {position[0], position[1], 0.0f};
	sceGumTranslate(&vector);

	
}

inline void PSPWidgetRenderer::dismissRendering() const{
	#ifdef _3D
		#ifdef _PC
			glMatrixMode(GL_PROJECTION);
			glPopMatrix();
			glMatrixMode(GL_MODELVIEW);
			glPopMatrix();
		#elif _SPSP
			sceGumMatrixMode(SCEGU_MATRIX_PROJECTION);
			sceGumPopMatrix();
			sceGumMatrixMode(SCEGU_MATRIX_WORLD);
			sceGumPopMatrix();
			//sceGumPopMatrix();
		#endif
	#else
		sceGumPopMatrix();
	#endif
}