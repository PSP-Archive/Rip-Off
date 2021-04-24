#ifdef _PC

#ifdef _VECTOR

#include "PCVectorRenderer.h"

// Always place as last include and only in cpp files!!
#include "foundation/Debug.h"

//--------------------------------------------------------------------------------
void
PCVectorRenderer::Render(LinePrimitive& primitive, const Vector4f& color, float lineWidth,
	const Vector2f& position, float angle, float scale)
{
	// Set the color and width
	glColor4f(color[0], color[1], color[2], color[3]);
	glLineWidth(lineWidth);
	
	// Apply transforms
	glPushMatrix();

		// Apply transformations
		glScalef(1.0f/getAspectRatio(), 1.0f, 1.0f);
		glTranslatef(position.x, position.y, 0.0f);
		glRotatef(angle, 0.0f, 0.0f, 1.0f);
		glScalef(scale, scale, 1.0f);

		// Begin rendering
		if(primitive.GetLPType() == LinePrimitive::LIST)
			glBegin(GL_LINES);
		else if(primitive.GetLPType() == LinePrimitive::STRIP)
			glBegin(GL_LINE_STRIP);
		else
		{
			assert	(!"Primitive type not supported");
		}

			// Draw
			std::list<Vector2f>::const_iterator it;
			for(it = primitive.GetList().begin(); it != primitive.GetList().end(); it++)
			{
				glVertex3f(it->x, it->y, 0.0f);
			}

		// End rendering
		glEnd();
	
	glPopMatrix();

	glLineWidth(1);
}

//--------------------------------------------------------------------------------
void
PCVectorRenderer::init()
{
	// Set up antialiasing
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
}

//--------------------------------------------------------------------------------
void
PCVectorRenderer::cleanUp()
{
	//glDisable(GL_BLEND);
}

//--------------------------------------------------------------------------------
void
PCVectorRenderer::startRender()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

//--------------------------------------------------------------------------------
void
PCVectorRenderer::endRender()
{

}


#endif

#endif