#include "ParabolaCore/AnimationFactory.h"
#include "ParabolaCore/AnimationPosition.h"
#include "ParabolaCore/AnimationTextWriter.h"
#include "ParabolaCore/AnimationDimension.h"
#include "ParabolaCore/RocketAnimationController.h"

#include "ParabolaCore/RocketDocument.h"

#include <iostream>
using namespace std;

PARABOLA_NAMESPACE_BEGIN

void AnimationFactory::addAnimation(AnimationInterface* animation){
		myAnimations.push_back(animation);
		animation->play();
}

void AnimationFactory::moveRocketElementTo(RocketElement* element, float x, float y, float duration){
	AnimationPosition* ap = new AnimationPosition();
	ap->addAnimable(new RocketAnimationController(element));
	ap->setDestination(x,y);
	ap->setDuration(duration);
	addAnimation(ap);
};

void AnimationFactory::resizeRocketElementTo(RocketElement* element, float width, float height, float duration){
	AnimationDimension* ap = new AnimationDimension();
	ap->addAnimable(new RocketAnimationController(element));
	ap->setDestination(width,height);
	ap->setDuration(duration);
	addAnimation(ap);
};

void AnimationFactory::addRocketElementContent(RocketElement* element, const String &content, float duration){
	AnimationTextWriter* ap = new AnimationTextWriter();
	ap->addAnimable(new RocketAnimationController(element));
	ap->setText(content);
	ap->setDuration(duration);
	addAnimation(ap);
};


/// Update the state of associated animations
void AnimationFactory::update(float elapsedTime){
	for(std::vector<AnimationInterface*>::iterator it = myAnimations.begin(); it != myAnimations.end(); it++){
		(*it)->update(elapsedTime);
		//cout<<"Updating the animations.."<<endl;
	}
};

PARABOLA_NAMESPACE_END
