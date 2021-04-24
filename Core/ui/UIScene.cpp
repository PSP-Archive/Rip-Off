#include "ui/UIScene.h"
//#ifdef _VECTOR
//	#include "vectorgraphics/VectorText.h"
//#endif
#include "Text.h"
#include "Icon.h"
#include "foundation/PSPHeap.h"

#include <assert.h>

UIScene::UIScene(void)
{
	m_currentItem = 0; //default to item 0;
}

UIScene::~UIScene(void)
{
	for(unsigned int i = 0; i < m_widgetList.size(); i++)
	{
		delete m_widgetList[i];
	}

	for(unsigned int i = 0; i < m_menuItemList.size();i++)
	{
		delete m_menuItemList[i];
	}
}

const int UIScene::addWidget(const string& fileName) //text widget
{
	//IconLoader loader;
	//Widget* pWidget = loader.load(item);
	m_widgetList.push_back(new Icon(fileName));
	return m_widgetList.size()-1;
}
//returns item id
//type refers to when/if the widget should be displayed, 0 = all the time, 1-N when menu item N is selected
const int UIScene::addWidget(Vector2f &position, const string &text,const int type, const float scale, const Vector3f& colour) //text widget
{
	//#ifdef _VECTOR

		/*int widgetId = m_widgetList.size();
		Widget *widgetPtr=new Widget();
		
		widgetPtr->setTextIF(new Text());
		
		widgetPtr->setPosition(position);
		widgetPtr->setText(text);
		widgetPtr->setType(type);
		widgetPtr->setColour(colour);
		widgetPtr->setScale(scale);
		
		

		m_widgetList.push_back(widgetPtr);
		*/
		
		//create new object
		int widgetId = m_widgetList.size();
		m_widgetList.push_back(new Text);
		//create pointer to new object
		Text* widgetPtr = (Text*)m_widgetList[widgetId]; 

		//fill in attributes
		widgetPtr->setPosition(position);
		widgetPtr->setText(text);
		widgetPtr->setType(type);
		widgetPtr->setColour(colour);
		widgetPtr->setScale(scale);
		
		return widgetId;
//#elif _3D
//	return 0;
//	#endif
	
}

//returns item id
const int UIScene::addMenuWidget(Vector2f &position, const string &text, const float scale, const Vector3f& colour, const Vector3f& selectedColour) //text widget
{
//#ifdef _VECTOR
	
	//create new object
	int widgetId = m_widgetList.size();
	m_widgetList.push_back(new Text());
	//create pointer to new object
	Text* widgetPtr = (Text*)m_widgetList[widgetId]; 

	//fill in attributes
	widgetPtr->setPosition(position);
	widgetPtr->setText(text);
	widgetPtr->setType(0);
	widgetPtr->setColour(colour);
	widgetPtr->setScale(scale);
	
//#endif

//todo: delete this test after implementation in _3D
//#ifdef _VECTOR
	if (m_widgetList.size()>0){

		// add it as menu item
		m_menuItemList.push_back(new MenuItem());
		m_menuItemList[m_menuItemList.size()-1]->setWidget(m_widgetList[widgetId]);
		m_menuItemList[m_menuItemList.size()-1]->setSelectedColour(selectedColour);

		if(m_menuItemList.size() == 1)
		{
			m_menuItemList[m_menuItemList.size()-1]->select(); //default to selecting first menu item
		}

	}

	return widgetId;
//#elif _3D
//	return 0;
//#endif
}

const void UIScene::popMenuWidget(){
	Widget *pw=m_widgetList.back();
	m_widgetList.pop_back();
	delete pw;
}

void UIScene::setText(const int widgetId, const string &text)
{	
//#ifdef _VECTOR
	assert((unsigned int)widgetId<m_widgetList.size());
	TextIF* widgetPtr = (TextIF*)m_widgetList[widgetId];
	widgetPtr->setText(text);
	//being extra safe...
	//
	//	m_widgetList[widgetId]->setText(text);
//#endif
}

const int UIScene::getSelectedMenuItem()
{
	return m_currentItem;
}
void UIScene::next()
{
	//deselect old item
	m_menuItemList[m_currentItem]->deselect();

	m_currentItem ++;

	if((unsigned) m_currentItem == m_menuItemList.size())
	{
		m_currentItem = 0;
	}

	//select new item
	m_menuItemList[m_currentItem]->select();
}

void UIScene::previous()
{
	//deselect old item
	m_menuItemList[m_currentItem]->deselect();

	m_currentItem --;

	if(m_currentItem < 0)
	{
		m_currentItem = m_menuItemList.size() - 1;
	}

	//select new item
	m_menuItemList[m_currentItem]->select();
}

void UIScene::render()const
{
	int widgetType;

	for(unsigned int i = 0; i < m_widgetList.size();i++)
	{
		widgetType = m_widgetList[i]->getType();

		if(!widgetType) //if type = 0, render
		{
			m_widgetList[i]->render();
		}
		else if((m_currentItem+1)==widgetType)
		{
			m_widgetList[i]->render();//if menu item is selected, render
		}
	}
}