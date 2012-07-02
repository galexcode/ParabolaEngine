#ifndef PARABOLA_ROCKETSYSTEMINTERFACE_H
#define PARABOLA_ROCKETSYSTEMINTERFACE_H

#include "Platform.h"
#include <Rocket/Core/SystemInterface.h>
//#include <SFML/System.hpp>

PARABOLA_NAMESPACE_BEGIN
	/**
		\ingroup libRocket
		\ingroup Graphics
		\class RocketSystemInterface
		\brief Represents the custom libRocket system interface

		Responsible for time managing and localization of ui.
	*/
	class PARABOLA_API RocketSystemInterface : public Rocket::Core::SystemInterface{
	public:
		/// Get the number of seconds elapsed since the start of the application
		/// @returns Seconds elapsed
		virtual float GetElapsedTime();

		/// Log messages that libRocket sends
		virtual bool LogMessage(Rocket::Core::Log::Type type, const Rocket::Core::String& message);

		/// Translate strings
		int TranslateString(Rocket::Core::String& translated, const Rocket::Core::String& input);

	private:
		//sf::Clock timer;
	};

PARABOLA_NAMESPACE_END
#endif