#include "ParabolaCore/AnimationGroupParallel.h"

PARABOLA_NAMESPACE_BEGIN

/// Update the group all at once
void AnimationGroupParallel::update(float elapsedTime){
	if(playing()){
		for(unsigned int i = 0; i < myAnimables.size(); i++){
			myAnimations[i]->update(elapsedTime);
		}
	}	
};

PARABOLA_NAMESPACE_END