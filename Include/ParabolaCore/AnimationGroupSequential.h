#ifndef PARABOLA_ANIMATIONGROUPSEQUENTIAL_H
#define PARABOLA_ANIMATIONGROUPSEQUENTIAL_H

#include "Platform.h"
#include "AnimationGroup.h"

PARABOLA_NAMESPACE_BEGIN

/**
	\ingroup Animation
	\class AnimationGroupSequential
	\brief Can hold and play animations in a sequential order, including other groups
*/
class PARABOLA_API AnimationGroupSequential : public AnimationGroup {
public:
	/// Default construction
	AnimationGroupSequential();

	/// Update the animations, one at once
	void update(float elapsedTime);

private:
	unsigned int myIndex;
};

PARABOLA_NAMESPACE_END
#endif