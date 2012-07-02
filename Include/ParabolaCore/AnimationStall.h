#ifndef PARABOLA_ANIMATIONSTALL_H
#define PARABOLA_ANIMATIONSTALL_H

#include "Platform.h"
#include "Animation.h"

PARABOLA_NAMESPACE_BEGIN

/**
	\ingroup Animation
	\class AnimationStall
	\brief Animation meant to stall only, if you need to skip some time until the next animation.
*/
class PARABOLA_API AnimationStall : public AnimationInterface{
public:
	/// The standard update method for animations
	void update(float elapsedTime);
};

PARABOLA_NAMESPACE_END
#endif