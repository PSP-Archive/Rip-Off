#pragma once
#include "foundation/Vector2f.h"
#include "foundation/Vector3f.h"

//#include "Text.h"
#include "WidgetRenderer.h"

class Widget
{
private:
	Vector2f m_position;
	int m_type;
	float m_scale;
	Vector3f m_colour;

	//Text *m_pText;		//can either be a vector text or a 3d one
	WidgetRenderer m_renderer;
public:
	//virtual void render()const = 0;
	void render()const;
	virtual void renderGeometry() const=0;

	void setPosition(const Vector2f &position);
	void setType(const int type);
	void setScale(const float scale);
	void setColour(const Vector3f& colour);
	//void setTextIF(Text *pText);
	//void setText(const string& text);

	const float getScale() const;
	const Vector3f& getColour()const;
	const Vector2f& getPosition()const;
	const int getType();

	Widget(void);
	virtual ~Widget(void);
};

inline void Widget::render() const{
	m_renderer.initRendering(m_position, m_colour, m_scale);
	renderGeometry();
	m_renderer.dismissRendering();
}
inline const float Widget::getScale()const
{
	return m_scale;
}
inline const Vector2f& Widget::getPosition()const
{
	return m_position;
}