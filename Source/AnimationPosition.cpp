#include "ParabolaCore/AnimationPosition.h"

#include <iostream>

PARABOLA_NAMESPACE_BEGIN
/// Construct the position animation
AnimationPosition::AnimationPosition(){
	totalTime = 0.f;
	myDuration = 0.f;
	myFunction = new AnimationEasingQuad();
	//((AnimationEasingQuad*)myFunction)->easeOut = false;
};

/// Set the destination for this animation
void AnimationPosition::setDestination(float x, float y){
	myDestination.x = x;
	myDestination.y = y;
};

/// Set the duration
void AnimationPosition::setDuration(float duration){
	myDuration = duration;
};


/// Update method
void AnimationPosition::update(float elapsedTime){
	if(myStart == myDestination){
		stop();
	}
	else{
		totalTime += elapsedTime;
		if(totalTime >= myDuration){
			myStart = myDestination;
			m_animables[0]->animable_set_position(myDestination.x,myDestination.y);
			
		}

		float calc_x = myFunction->compute(totalTime, myStart.x, myDestination.x - myStart.x, myDuration);
		float calc_y = myFunction->compute(totalTime, myStart.y, myDestination.y - myStart.y, myDuration);


		m_animables[0]->animable_set_position(calc_x,calc_y);
		//std::cout<<"t "<<totalTime<<std::endl;
	}
};

/// Play override
void AnimationPosition::play(){
	if(m_animables.size() != 0){
		myStart = m_animables[0]->animable_get_position();
		totalTime = 0.f;
		AnimationInterface::play();
	}	
};

PARABOLA_NAMESPACE_END