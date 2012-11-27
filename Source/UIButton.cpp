#include <ParabolaCore/UIButton.h>
#include <ParabolaCore/Text.h>

#include <iostream>
using namespace std;

PARABOLA_NAMESPACE_BEGIN

/// Constructs the button
UIButton::UIButton(){

};

/// Constructs the button from a label text
UIButton::UIButton(const String& title) : m_label(title){
	m_color = Color(30,20,10);
};

/// Callback to handle an event
bool UIButton::onEventNotification(Event& event){
	if(event.type == Event::MouseButtonReleased){
		if(m_bounds.contains(event.mouseButton.x, event.mouseButton.y)){
			onClick();
		}
	}
	return true;
}

/// Callback to render itself, renders children
void UIButton::draw(Renderer* renderer){
	renderer->drawDebugQuad(m_bounds.left + m_bounds.width/2, m_bounds.top + m_bounds.height/2, 0,m_bounds.width, m_bounds.height, m_color );
	Text t;
	t.setString(m_label);
	t.setPosition(m_bounds.left, m_bounds.top);
	renderer->draw(t);
};

PARABOLA_NAMESPACE_END
