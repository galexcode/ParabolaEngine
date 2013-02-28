#include <ParabolaCore/UILabel.h>
#include <ParabolaCore/Text.h>

#include <iostream>
using namespace std;

PARABOLA_NAMESPACE_BEGIN

/// Constructs the button
UILabel::UILabel() : UIControl(), m_color(0,0,0) , hover(false){

};

/// Constructs the button from a label text
UILabel::UILabel(const String& title) : UIControl(), m_color(0,0,0), m_label(title), hover(false){

};

/// Callback to handle an event
bool UILabel::onEventNotification(Event& event){
	if(event.type == Event::MouseButtonReleased){
		if(m_bounds.contains(event.mouseButton.x, event.mouseButton.y)){
			onClick();
		}
}	

	if(event.type == Event::MouseMoved)
	{
		if(m_bounds.contains(event.mouseMove.x, event.mouseMove.y)){	
			//setProperty<Color>("background-color", Color::White);
		}
		else
		{
			//setProperty<Color>("background-color", Color(91,91,91));
		}
	}
	return true;
}

/// Callback to render itself, renders children
void UILabel::draw(Renderer* renderer){

	Text t;
	t.setString(m_label);
	t.setColor(m_color);
	t.setPosition(m_bounds.left, m_bounds.top);
	renderer->draw(t);
};

PARABOLA_NAMESPACE_END
