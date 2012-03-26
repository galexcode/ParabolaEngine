#ifndef ROCKETNAVIGATION_H
#define ROCKETNAVIGATION_H

#include "Platform.h"
#include "Rocket/Core/Core.h"
#include <iostream>
using namespace std;

namespace pE{

	class PARABOLA_API NavigationConsoleListener : public Rocket::Core::EventListener{
	public:
		Rocket::Core::ElementDocument *Doc;
		void ProcessEvent(Rocket::Core::Event& event);

		void ResizeConsole();
	};

};

#endif