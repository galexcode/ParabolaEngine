#ifndef PARABOLA_ANIMATIONSYSTEM_H
#define PARABOLA_ANIMATIONSYSTEM_H

/**
	\defgroup Animation

	This module contains all classes relative to animations.
*/

#include "Platform.h"
#include "Signals.h"

#include <vector>

PARABOLA_NAMESPACE_BEGIN

namespace PlayModes{
	enum State{
		Playing = 0,
		Stopped,
		Paused
	};

	enum Type{

	};
};

/**
	\ingroup Animation
	\class AnimationInterface
	\brief Base class for all animations.

	Any animation class inherits
*/
class PARABOLA_API AnimationInterface{
public:
	/// Creates the animation default states
	AnimationInterface();

	sigc::signal<void> onEnd;

	/// Get the total time elapsed since this animation has started
	float getElapsedTime();

	/// Starts the updating of the animation
	virtual void play();

	/// Stops the updating of the animation
	virtual void stop();

	/// Checks if the animation is currently playing
	bool playing();

	/// Sets the animation as a loop if possible or not
	/// Animations can re implement this method, to disallow looping
	virtual void setLoop(bool isLoop);

	/// Checks if the animation is set to loop
	bool looping();

protected:
	/// Updates the state of the animation
	virtual void update(float elapsedTime) = 0;

	/// Restores the animated object(s) to their original state
	virtual void restore();

	/// Adds time to the total duration of this animation execution
	void addTime(float elapsedTime);

private:
	float totalElapsedTime;
	int myStatus;
	bool myLooping;
};

PARABOLA_NAMESPACE_END
#endif