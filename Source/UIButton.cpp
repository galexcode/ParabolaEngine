#include <ParabolaCore/UIButton.h>
#include <ParabolaCore/Text.h>

#include <iostream>
using namespace std;

PARABOLA_NAMESPACE_BEGIN

/// Constructs the button
UIButton::UIButton() : UIControl(), m_color(0,0,0) , hover(false){

};

/// Constructs the button from a label text
UIButton::UIButton(const String& title) : UIControl(), m_color(0,0,0), m_label(title), hover(false){

};

/// Callback to handle an event
bool UIButton::onEventNotification(Event& event){
	if(event.type == Event::MouseButtonPressed){
		if(m_bounds.contains(event.mouseButton.x, event.mouseButton.y)){
			// drag test
			if(getContext())
			{
				getContext()->m_dragControl = this->clone();
				getContext()->m_dragOffset = Vec2f(event.mouseButton.x - m_bounds.left, event.mouseButton.y - m_bounds.top);
			}
		}
	}

	if(event.type == Event::MouseButtonReleased){
		if(m_bounds.contains(event.mouseButton.x, event.mouseButton.y)){
			onClick();
		}

		// drag test
		if(getContext())
		{
			getContext()->m_dragControl = NULL;
		}
	}

	if(event.type == Event::MouseMoved)
	{
		if(m_bounds.contains(event.mouseMove.x, event.mouseMove.y)){	
			setProperty<Color>("background-color", Color::White);
		}
		else
		{
			setProperty<Color>("background-color", Color(91,91,91));
		}
	}
	return true;
}

UIControl* UIButton::clone()
{
	return new UIButton(*this);
};


/// Callback to render itself, renders children
void UIButton::draw(Renderer* renderer){
	
	Text t;
	t.setString(m_label);
	t.setColor(m_color);
	t.setPosition(m_bounds.left, m_bounds.top);
	renderer->draw(t);
};

PARABOLA_NAMESPACE_END
