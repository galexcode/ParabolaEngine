#include "ParabolaCore/AnimationGroupSequential.h"

PARABOLA_NAMESPACE_BEGIN

/// Default construction
AnimationGroupSequential::AnimationGroupSequential(){
	myIndex = 0.f;
};

/// Update the group , one at once
void AnimationGroupSequential::update(float elapsedTime){
	if(playing() && myAnimables.size() > 0){
		myAnimations[myIndex]->update(elapsedTime);
	}
};

PARABOLA_NAMESPACE_END