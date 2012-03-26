#ifndef PARABOLA_ROCKETEVENTBOX_H
#define PARABOLA_ROCKETEVENTBOX_H

#include "Platform.h"
#include "Strings.h"
#include "Signals.h"
#include "Events.h"
#include <Rocket/Core.h>

PARABOLA_NAMESPACE_BEGIN
typedef Rocket::Core::Event RocketEvent;
/**
	\ingroup libRocket
	\ingroup Graphics
	\class RocketEventBox
	\brief Represents a custom tag in RML to grab all events and translate them into the engine's normal events

	...
	\todo still undone properly
*/
class RocketEventBox : public Rocket::Core::Element{
public:
	/// Creates the custom element from the selected tag name
	RocketEventBox(const Rocket::Core::String &tag);

	/// Safely destructs
	~RocketEventBox();

	// Called for every event sent to this element or one of its descendants.
	// @param[in] event The event to process.
	virtual void ProcessEvent(Rocket::Core::Event& event);

	sigc::signal<void, RocketEvent&> onRawEvent;
	sigc::signal<void, Event&> onTranslatedEvent;

private:
	String myTagName;
};

PARABOLA_NAMESPACE_END
#endif
