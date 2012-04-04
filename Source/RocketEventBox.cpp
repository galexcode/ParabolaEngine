#include "ParabolaCore/RocketEventBox.h"
#include "ParabolaCore/Events.h"
#include "ParabolaCore/RocketPlugin.h"

#include <iostream>
using namespace std;

PARABOLA_NAMESPACE_BEGIN
	Event convertRocketToEvent(Rocket::Core::Event &event){
		Event sevent;		

		if(event == "keydown"){
			Rocket::Core::Input::KeyIdentifier key_identifier = (Rocket::Core::Input::KeyIdentifier) event.GetParameter< int >("key_identifier", 0);

			sevent.type = (sf::Event::EventType)Event::KeyPressed;
			sevent.key.code = (sf::Keyboard::Key)EventDispatcher::translateFromRocketKey(key_identifier);

		}
		else if(event == "keyup"){
			Rocket::Core::Input::KeyIdentifier key_identifier = (Rocket::Core::Input::KeyIdentifier) event.GetParameter< int >("key_identifier", 0);

			sevent.type = (sf::Event::EventType)Event::KeyReleased;
			sevent.key.code = (sf::Keyboard::Key)EventDispatcher::translateFromRocketKey(key_identifier);
		}
		else if(event == "mousedown"){
			sevent.type = (sf::Event::EventType)Event::MouseButtonPressed;
			sevent.mouseButton.button = (sf::Mouse::Button)event.GetParameter<int>("button", 0);
			sevent.mouseButton.x = event.GetParameter<int>("mouse_x", 0);
			sevent.mouseButton.y = event.GetParameter<int>("mouse_y", 0);
		}
		else if(event == "mouseup"){
			sevent.type = (sf::Event::EventType)Event::MouseButtonReleased;
			sevent.mouseButton.button = (sf::Mouse::Button)event.GetParameter<int>("button", 0);
			sevent.mouseButton.x = event.GetParameter<int>("mouse_x", 0);
			sevent.mouseButton.y = event.GetParameter<int>("mouse_y", 0);
		}
		else if(event == "mousemove"){
			sevent.type = (sf::Event::EventType)Event::MouseMoved;
			sevent.mouseMove.x = event.GetParameter<int>("mouse_x", 0);
			sevent.mouseMove.y = event.GetParameter<int>("mouse_y", 0);
		}
		else if(event == "wheel"){
			sevent.type = (sf::Event::EventType)Event::MouseWheelMoved;

		}
		else if(event == "textinput"){
			sevent.type = (sf::Event::EventType)Event::TextEntered;

		}
		else if(event == "click"){
			sevent.type = (sf::Event::EventType)Event::Click;
			sevent.mouseButton.x = event.GetParameter<int>("mouse_x", 0);
			sevent.mouseButton.y = event.GetParameter<int>("mouse_y", 0);
		}
		else if(event == "dblclick"){
			sevent.type = (sf::Event::EventType)Event::DoubleClick;
		}
	
		return sevent;
	}

RocketEventBox::RocketEventBox(const Rocket::Core::String &tag) : Rocket::Core::Element(tag){
		if(RocketPlugin::instance().myEventCatchers.find(tag.CString()) == RocketPlugin::instance().myEventCatchers.end())
			RocketPlugin::instance().myEventCatchers[tag.CString()] = this;

		myTagName = tag.CString();

		//Rocket::Core::Element::Focus();
};

/// Safely destructs
RocketEventBox::~RocketEventBox(){
	RocketPlugin::instance().myEventCatchers.erase(RocketPlugin::instance().myEventCatchers.find(myTagName));
};

// Called for every event sent to this element or one of its descendants.
// @param[in] event The event to process.
void RocketEventBox::ProcessEvent(Rocket::Core::Event& event){
		Rocket::Core::Element::ProcessEvent(event);
		
		onRawEvent(event);

		if(onTranslatedEvent.size() > 0){
			//translate

			onTranslatedEvent.emit(convertRocketToEvent(event));
		}
		//Rocket::Core::Element::Focus();
};

PARABOLA_NAMESPACE_END