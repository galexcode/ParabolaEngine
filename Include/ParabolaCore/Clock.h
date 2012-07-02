#ifndef PARABOLA_CLOCK_H
#define PARABOLA_CLOCK_H

#include "Platform.h"

PARABOLA_NAMESPACE_BEGIN

class PARABOLA_API Time{
public:
	Time(){
		myMicroSeconds = 0;
	}

	Time(Int64 ms){
		myMicroSeconds = ms;
	}
	float asSeconds();
	float asMiliSeconds();
	Int64 asMicroseconds();

	static Time fromMicroseconds(Int64 ms);

	static Time fromSeconds(float seconds);

	Time operator -(Time right);

	Int64 myMicroSeconds;
};

class PARABOLA_API Clock{
public:
	Clock();

	~Clock();

	void pause();

	void start();

	void reset();

	Time getElapsedTime();

private:
	bool myPaused;

	class ClockImplementation;
	ClockImplementation *myClockImpl;
};

PARABOLA_NAMESPACE_END
#endif