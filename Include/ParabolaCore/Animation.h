#ifndef PARABOLA_ANIMATIONSYSTEM_H
#define PARABOLA_ANIMATIONSYSTEM_H

/**
	\defgroup Animation

	This module contains all classes relative to animations.
*/

#include "Platform.h"
#include "Vectors.h"
#include "Signals.h"
#include "AnimationEasing.h"

#include <vector>

PARABOLA_NAMESPACE_BEGIN

namespace PlayModes{
	enum State{
		Playing = 0,
		Stopped,
		Paused
	};
};

/**
	\ingroup Animation
	\class Animable
	\brief Base class for all objects that can be animated.
*/
class PARABOLA_API Animable{
public:

	/// Virtual destructor, for detaching running animations.
	virtual ~Animable();

	/// Signal to stop animations that are depending on this animable
	sigc::signal<void, Animable*> onDetachAnimation;

	virtual void animable_set_position(float x, float y) {};
	virtual Vec2f animable_get_position() {return Vec2f();};
	virtual void animable_set_color(int r, int g, int b, int a){}
	virtual Vec2f animable_get_size(){return Vec2f();}
	virtual void animable_set_size(float x, float y){}
	virtual void animable_add_character(char c){}
};

/**
	\ingroup Animation
	\class AnimationInterface
	\brief Base class for all animations.

	Any animation class inherits
*/
class PARABOLA_API AnimationInterface : public sigc::trackable{
public:
	/// Creates the animation default states
	AnimationInterface();

	sigc::signal<void> onEnd;

	/// Add a new object to this animation
	void addAnimable(Animable* animable);

	/// Remove animable from the list
	void removeAnimable(Animable* animable);

	/// Get the number of objects being animated
	int getAnimableCount();

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

	/// Updates the state of the animation
	virtual void update(float elapsedTime) = 0;

protected:

	/// Restores the animated object(s) to their original state
	virtual void restore();

	/// Adds time to the total duration of this animation execution
	void addTime(float elapsedTime);

	/// Registered objects for animation update
	std::vector<Animable*> myAnimables;

private:
	float totalElapsedTime;
	int myStatus;
	bool myLooping;	
};

PARABOLA_NAMESPACE_END
#endif