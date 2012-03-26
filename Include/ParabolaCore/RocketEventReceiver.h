#pragma once

namespace pE{
	


	class RocketEventReceiver{
	public:
		string LastEvent;
		/// Processes an event coming through from Rocket.
		/// @param[in] event The Rocket event that spawned the application event.
		/// @param[in] value The application-specific event value.
		void ProcessEvent(Rocket::Core::Event& event, const Rocket::Core::String& value, RocketContextManager *Manager);
	};
};