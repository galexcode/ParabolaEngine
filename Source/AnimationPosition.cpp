#include "ParabolaCore/AnimationPosition.h"

#include <iostream>

PARABOLA_NAMESPACE_BEGIN
/// Construct the position animation
AnimationPosition::AnimationPosition(){
	m_totalTime = 0.f;
	m_duration = 0.f;
	m_function = new AnimationEasingQuad();
	//((AnimationEasingQuad*)myFunction)->easeOut = false;
};

/// Set the destination for this animation
void AnimationPosition::setDestination(float x, float y){
	m_end.x = x;
	m_end.y = y;
};

/// Set the initial point of animation
void AnimationPosition::setStartPosition(float x, float y){
	m_start = Vec2f(x,y);
};

/// Set the duration
void AnimationPosition::setDuration(float duration){
	m_duration = duration;
};


/// Fresh start, ensure the initial value
void AnimationPosition::onBegin(){
	for(unsigned int i = 0; i < m_animables.size(); i++){
		m_animables[i]->animable_set_position(m_start.x, m_start.y);
	}
};

/// Called when the animation is updating
/// \return MUST return the remaining time not used by the animation
/// This is essential as in a play list of animations, when one finished, the next updates immediately.
float AnimationPosition::onUpdate(float elapsedTime){
	if(getStatus() == AnimationStates::Playing){
		m_totalTime += elapsedTime;
		float xres =  m_function->compute(m_totalTime, m_start.x, m_end.x - m_start.x, m_duration);
		float yres =  m_function->compute(m_totalTime, m_start.y, m_end.y - m_start.y, m_duration);

		for(unsigned int i = 0; i < m_animables.size(); i++){
			m_animables[i]->animable_set_position(xres, yres);
		}

		if(m_totalTime >= m_duration){
			setStatus(AnimationStates::Stopped);
			// Ensure the end value
			for(unsigned int i = 0; i < m_animables.size(); i++){
				m_animables[i]->animable_set_position(xres, yres);
			}
			return m_totalTime - m_duration;
		}
		else return elapsedTime;
	}
	else return 0.f;
};

/// Play override
void AnimationPosition::play(){
	setStatus(AnimationStates::Playing);
	onBegin();
};

PARABOLA_NAMESPACE_END