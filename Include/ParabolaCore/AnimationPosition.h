#ifndef PARABOLA_ANIMATIONPOSITION_H
#define PARABOLA_ANIMATIONPOSITION_H

#include "Platform.h"
#include "Vectors.h"
#include "Animation.h"
#include "ReferenceCountable.h"

PARABOLA_NAMESPACE_BEGIN

/**
	\ingroup Animation
	\class AnimationPosition
	\brief Animates a transformable object from point A to point B

*/
class AnimationPosition : public AnimationInterface, public RefCountable{
public:
	/// Construct the position animation
	AnimationPosition();

	/// Set the destination for this animation
	void setDestination(float x, float y);

	/// Set the duration
	void setDuration(float duration);

	/// Update method
	void update(float elapsedTime);

	/// Play override
	void play();

private:
	Vec2f myStart;
	Vec2f myDestination;
	float totalTime;
	float myDuration;

	AnimationEasingFunction *myFunction;
};

PARABOLA_NAMESPACE_END
#endif