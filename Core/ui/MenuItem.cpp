#include "MenuItem.h"

MenuItem::MenuItem(void)
{
	m_menuWidget = NULL;
	m_isSelected = false;
}

MenuItem::~MenuItem(void)
{
}

void MenuItem::setSelectedColour(const Vector3f& colour)
{
	m_colour = colour;
}

void MenuItem::select()
{
	//switch text colour
	Vector3f tempColour = m_menuWidget->getColour();
	m_menuWidget->setColour(m_colour);
	m_colour = tempColour;

	m_isSelected = true;
}

void MenuItem::deselect()
{
	//switch text colour
	Vector3f tempColour = m_menuWidget->getColour();
	m_menuWidget->setColour(m_colour);
	m_colour = tempColour;
	m_isSelected = false;
}

void MenuItem::setWidget(Widget* newWidget)
{
	if(m_menuWidget == NULL)
	{
		m_menuWidget = newWidget;
	}
}