#ifndef PARABOLA_ANIMATIONGROUP_H
#define PARABOLA_ANIMATIONGROUP_H

#include "Platform.h"
#include "Animation.h"
#include <vector>

PARABOLA_NAMESPACE_BEGIN
/**
	\ingroup Animation
	\class AnimationGroup
	\brief Base grouping class for animations
*/
class PARABOLA_API AnimationGroup : public AnimationInterface{
public:

	/// Mandatory implementation for the update method in a group
	virtual void update(float elapsedTime) = 0;

	std::vector<AnimationInterface*> myAnimations;
};

PARABOLA_NAMESPACE_END
#endif