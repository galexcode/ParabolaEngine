#include "ParabolaCore/Clock.h"

#ifdef PARABOLA_DESKTOP
#include <SFML/System/Clock.hpp>
#elif defined PARABOLA_ANDROID
#include <time.h>
#endif

PARABOLA_NAMESPACE_BEGIN

#ifdef PARABOLA_DESKTOP

class Clock::ClockImplementation{
public:
	sf::Clock clock;
};

#elif defined PARABOLA_ANDROID
class Clock::ClockImplementation{
public:
	ClockImplementation(){
		myStartTime = getCurrentTime();
	}

	Time getCurrentTime(){
		timespec time;
		clock_gettime(CLOCK_MONOTONIC, &time);
		Time genTime;	
		genTime.myMicroSeconds =  static_cast<Uint64>(time.tv_sec) * 1000000 + time.tv_nsec / 1000;
		return genTime;
	}

	Time myStartTime;
};
#endif


float Time::asSeconds(){
	return myMicroSeconds / 1000000.f;
}

float Time::asMiliSeconds(){	
	return myMicroSeconds / 10000.f;
};

Int64 Time::asMicroseconds(){
	return myMicroSeconds;
}

Time Time::fromSeconds(float seconds){
	return Time((Int64)(seconds * 1000000.f));
};


Time Time::fromMicroseconds(Int64 ms){
	Time t;
	t.myMicroSeconds = ms;
	return t;
};


Time Time::operator -(Time right)
{
	Time t;
	t.myMicroSeconds = myMicroSeconds - right.asMicroseconds();
	return t;
}




Clock::Clock(){
	myClockImpl = new ClockImplementation();
}

Clock::~Clock(){
	delete myClockImpl;
};

void Clock::pause(){

}

void Clock::start(){

}



void Clock::reset(){
#ifdef PARABOLA_DESKTOP
	myClockImpl->clock.restart();
#else
	myClockImpl->myStartTime = myClockImpl->getCurrentTime();
#endif
}

Time Clock::getElapsedTime(){

#ifdef PARABOLA_DESKTOP
	return Time::fromMicroseconds(myClockImpl->clock.getElapsedTime().asMicroseconds());
#else
	return myClockImpl->getCurrentTime() - myClockImpl->myStartTime;
#endif
};

PARABOLA_NAMESPACE_END