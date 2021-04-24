#pragma once
#include <vector>
#include "foundation/Vector2f.h"
#include "ui/Widget.h"
#include "ui/MenuItem.h"

using namespace std;

class UIScene
{
private:
	vector <Widget*> m_widgetList;
	vector <MenuItem*> m_menuItemList;
	int m_currentItem;
public:

	const int addMenuWidget(Vector2f &Position,const string &text, const float scale, const Vector3f& colour, const Vector3f& selectedColour ); //add a text item
	const void popMenuWidget();
	const int getSelectedMenuItem();

	const int addWidget(const string& filename);
	const int addWidget(Vector2f &Position,const string &text, const int type, const float scale, const Vector3f& colour); //add a text item

	
	void setText(const int widgetId, const string &text);


	void render()const;

	void next(); //cycle to the next menu item
	void previous(); //cycle to the previous menu item

	UIScene(void);
	~UIScene(void);
};



