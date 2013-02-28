#include <ParabolaCore/UISoftwareKeyboard.h>
#include <ParabolaCore/Text.h>
#include <ParabolaCore/UIButton.h>

#include <iostream>
using namespace std;

PARABOLA_NAMESPACE_BEGIN

/// Constructs the button
UISoftwareKeyboard::UISoftwareKeyboard() : UIControl(), m_color(0,0,0) , hover(false){
	UIButton* eraseButton = new UIButton("<-");
	eraseButton->setPosition(1600, 700);
	eraseButton->setSize(200,50);
	eraseButton->onClick.connect(MAKE_SLOT_LOCAL(UISoftwareKeyboard, emitErase));
	addControl(eraseButton);
};

void UISoftwareKeyboard::emitErase()
{
	onErase();
}


/// Constructs the button from a label text
UISoftwareKeyboard::UISoftwareKeyboard(const String& title) : UIControl(), m_color(0,0,0), m_label(title), hover(false){

};

/// Callback to handle an event
bool UISoftwareKeyboard::onEventNotification(Event& event){
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

	if(event.type == Event::TextEntered)
	{
		//onTextEntered(event.text.unicode);
	}

	return UIControl::onEventNotification(event);
}

/// Callback to render itself, renders children
void UISoftwareKeyboard::draw(Renderer* renderer){

	Text t;
	t.setString(m_label);
	t.setColor(m_color);
	t.setPosition(m_bounds.left, m_bounds.top);
	renderer->draw(t);
};

PARABOLA_NAMESPACE_END
