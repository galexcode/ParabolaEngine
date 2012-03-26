#include "ParabolaCore/Animation.h"

PARABOLA_NAMESPACE_BEGIN
/// Creates the animation default states
AnimationInterface::AnimationInterface() : totalElapsedTime(0.f), myStatus(PlayModes::Stopped), myLooping(false){
	
};

/// Get the total time elapsed since this animation has started
float AnimationInterface::getElapsedTime(){
	return totalElapsedTime;
};

/// Starts the updating of the animation
void AnimationInterface::play(){
	myStatus = PlayModes::Playing;
};

/// Stops the updating of the animation
void AnimationInterface::stop(){
	myStatus = PlayModes::Stopped;
};

/// Checks if the animation is currently playing
bool AnimationInterface::playing(){
	return (myStatus == PlayModes::Playing);
};

/// Restores the animated object(s) to their original state
void AnimationInterface::restore(){

};


/// Sets the animation as a loop if possible or not
/// Animations can re implement this method, to disallow looping
void AnimationInterface::setLoop(bool isLoop){
	myLooping = isLoop;
};

/// Checks if the animation is set to loop
bool AnimationInterface::looping(){
	return myLooping;
};

/// Adds time to the total duration of this animation execution
void AnimationInterface::addTime(float elapsedTime){
	totalElapsedTime += elapsedTime;
};

PARABOLA_NAMESPACE_END