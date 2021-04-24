#pragma once
//#include "ui/Widget.h"
#include <string>

using namespace std;

#include "Widget.h"
#include "WidgetRenderer.h"

class TextIF : public Widget
{
private:
	string m_text;
public:
	void setText(const string& text);
	const string& getText() const;

	void renderGeometry()const;
	virtual void printChar(const char character)const = 0;

	TextIF(void);
	virtual ~TextIF(void);
};

