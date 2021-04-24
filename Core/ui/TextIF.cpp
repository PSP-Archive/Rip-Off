#include "ui/TextIF.h"
#include "foundation/Vector2f.h"

//#ifdef _PC
//	#include <windows.h>
//	#include <gl/gl.h>
//#endif

TextIF::TextIF(void)
{
}

TextIF::~TextIF(void)
{
}

void TextIF::setText(const string& text)
{
	m_text = text;
}

const string& TextIF::getText() const
{
	return m_text;
}

void TextIF::renderGeometry()const
{
	//moved in Widget::render()
	/*
	#ifdef _PC
		glPushMatrix();
			Vector2f pos = getPosition();

		#ifdef _VECTOR
			glTranslatef(pos[0],pos[1],0);
			glColor3f(getColour()[0],getColour()[1], getColour()[2]);	
			glLineWidth(0.6f*getScale());
		#endif
	*/
	
			string textString = getText();
			int i = 0;
			while(textString[i])
			{
				if((textString[i]<91)&&(textString[i]>64)) //convert capital letters to lower case
				{
					textString[i] += 32;
				}
				printChar(textString[i]);
				i++;			
			}
	
		//glPopMatrix();
	//#endif
}