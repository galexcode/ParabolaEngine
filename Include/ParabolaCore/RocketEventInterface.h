#ifndef PARABOLA_ROCKETEVENTINTERFACE_H
#define PARABOLA_ROCKETEVENTINTERFACE_H

#include "Platform.h"
#include "Signals.h"
#include "Strings.h"
#include <Rocket/Core.h>

PARABOLA_NAMESPACE_BEGIN
	
class RocketPlugin;
class RocketEventListener;
/**
	\ingroup Graphics
	\ingroup libRocket
	\class RocketEventDispatcher
	\brief This class emits libRocket events that a user can be notified of

	...
*/
class PARABOLA_API RocketEventDispatcher: public Rocket::Core::EventListenerInstancer{
public:
	/// Safely destructs the event dispatcher
	virtual ~RocketEventDispatcher();

	/// Signal is triggered when a libRocket event fires
	sigc::signal<void, String> onEventTriggered;

protected:
	/// Creates a RocketEventDispatcher
	/// Not instance able except by the RocketPlugin
	RocketEventDispatcher();
	
	/// Instances a event listener
	/// A event listener is an object bound with a specific event of a specific element
	/// When that event is fired, it's ProcessEvent() method is called.
	virtual Rocket::Core::EventListener* InstanceEventListener(const Rocket::Core::String& value, Rocket::Core::Element *element);

	/// Destroys the instancer.
	virtual void Release();

private:
	friend class RocketPlugin;
	friend class RocketEventListener;
};


/**
	\ingroup Graphics
	\ingroup libRocket
	\class RocketEventListener
	\brief Represents one event from the RML

	...
*/
class PARABOLA_API RocketEventListener: public Rocket::Core::EventListener{
public:
	/// Creates the listener associated with >value< event
	RocketEventListener(const Rocket::Core::String& value);

	/// Safely destroys the listener
	virtual ~RocketEventListener();


protected:
	/// Called when the event associated with this listener is triggered
	virtual void ProcessEvent(Rocket::Core::Event& event);

	/// Destroys the listener
	virtual void OnDetach(Rocket::Core::Element* element);

private:
	Rocket::Core::String value;
	friend class RocketEventDispatcher;

	RocketEventDispatcher* myDispatcher;
		
};	

PARABOLA_NAMESPACE_END
#endif