#pragma once
#include "../../ui/WidgetRendererIF.h"
#include "foundation/Vector2f.h"
#include <windows.h>
#include <gl/gl.h>

class PCWidgetRenderer:public WidgetRendererIF{
public:
	void initRendering(const Vector2f& position, const Vector3f& color, float scale) const;
	void dismissRendering() const;
};

inline void PCWidgetRenderer::initRendering(const Vector2f& position, const Vector3f& color, float scale) const{
#ifdef _3D
	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();	
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();	
	glLoadIdentity();
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	//IMPORTANT: IF WE ADD OTHER OBJECTS TO BE DRAWN HERE WE MUST DISABLE DEPTH_TEST
	//glDisable(GL_DEPTH_TEST);

#else
	glPushMatrix();	
	glColor3f(color[0],color[1], color[2]);	
	glLineWidth(0.6f*scale);
#endif	
	
	glTranslatef(position[0],position[1],0);
}

inline void PCWidgetRenderer::dismissRendering() const{
	#ifdef _3D
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
	#else
		glPopMatrix();	
	#endif
}