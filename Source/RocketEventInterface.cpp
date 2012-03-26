#include "ParabolaCore/RocketEventInterface.h"
#include "ParabolaCore/RocketPlugin.h"
#include <iostream>

PARABOLA_NAMESPACE_BEGIN
	
	RocketEventListener::RocketEventListener(const Rocket::Core::String& value) : value(value), myDispatcher(NULL){
		
	}

	RocketEventListener::~RocketEventListener(){

	}

	// Sends the event to the engine stack or a gamecore directly
	void RocketEventListener::ProcessEvent(Rocket::Core::Event& event)
	{
		//std::cout<<"Event: "<<value.CString()<<std::endl;		
		if(myDispatcher){
			myDispatcher->onEventTriggered.emit(value.CString());
		}
	}

	// Destroys the event.
	void RocketEventListener::OnDetach(Rocket::Core::Element* ROCKET_UNUSED(element))
	{
		delete this;
	}







	//////////////////////DISPATCHER

	RocketEventDispatcher::RocketEventDispatcher(){

	}

	RocketEventDispatcher::~RocketEventDispatcher(){

	}

	// Instances a new event handle for Invaders.
	Rocket::Core::EventListener* RocketEventDispatcher::InstanceEventListener(const Rocket::Core::String& value, Rocket::Core::Element *element)
	{
		RocketEventListener *Event = new RocketEventListener(value);
		Event->myDispatcher = this;
		return Event;
	}

	// Destroys the instancer.
	void RocketEventDispatcher::Release()
	{
		delete this;
	}


PARABOLA_NAMESPACE_END