#include <ParabolaCore/UILineEdit.h>

#include <iostream>
using namespace std;


PARABOLA_NAMESPACE_BEGIN

bool UILineEdit::onEventNotification(Event& event){
	if(event.type == Event::TextEntered){
		s += event.text.unicode;
		t.setString(s);
	}
	return true;
};

void UILineEdit::setText(const String& text){
	s = text;
	t.setString(s);
};


void UILineEdit::draw(Renderer* renderer){
	t.setPosition(300,500);
	renderer->draw(t);
};


PARABOLA_NAMESPACE_END