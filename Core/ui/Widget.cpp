#include "Widget.h"

Widget::Widget(void)
{
}

Widget::~Widget(void)
{
}

void Widget::setScale(const float scale)
{
	m_scale = scale;
}

void Widget::setColour(const Vector3f& colour)
{
	m_colour = colour;
}

void Widget::setPosition(const Vector2f &position)
{
	m_position = position;
}

void Widget::setType(const int type)
{
	m_type = type;
}

//void Widget::setTextIF(Text *pText)
//{
//	m_pText=pText;
//}

//void Widget::setText(const string& text)
//{
//	m_pText->setText(text);
//}

//const Vector2f& Widget::getPosition()const 
//{
//	return m_position;
//}

const int Widget::getType()
{
	return m_type;
}

const Vector3f& Widget::getColour()const 
{
	return m_colour;
}

