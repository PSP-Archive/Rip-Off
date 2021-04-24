#pragma once
#include "ui/MenuAction.h"
#include "ui/Widget.h"
#include <vector>
#include "foundation/Vector3f.h"

class MenuItem
{
public:
	MenuItem(void);
	~MenuItem(void);

	void select();
	void deselect();
	void setSelectedColour(const Vector3f& colour);
	void setWidget(Widget* newWidget);//this function should only be called from UIScene

private:
	MenuAction m_menuAction;
	bool m_isSelected;
	Widget* m_menuWidget;
	Vector3f m_colour;
};
