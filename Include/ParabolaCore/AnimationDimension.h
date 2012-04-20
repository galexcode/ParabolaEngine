#ifndef PARABOLA_ANIMATIONDIMENSION_H
#define PARABOLA_ANIMATIONDIMENSION_H

#include "Platform.h"
#include "Vectors.h"
#include "Animation.h"

PARABOLA_NAMESPACE_BEGIN

/**
	\ingroup Animation
	\class AnimationDimension
	\brief Animates a transformable object from dimension A to B

*/
class PARABOLA_API AnimationDimension : public AnimationInterface{
public:
	/// Construct the position animation
	AnimationDimension();

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