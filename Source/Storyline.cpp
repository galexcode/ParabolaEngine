#ifndef MINIMAL_BUILD

#include "ParabolaCore/Storyline.h"
#include "ParabolaCore/StoryPlayer.h"

PARABOLA_NAMESPACE_BEGIN

Storyline::Storyline(){
	parent = NULL;
	play_type = STOPPED;
}

void Storyline::setParent(StoryPlayer *parent){
	this->parent = parent;
};

void Storyline::append(StoryAction *action){
	
	action->setParent(this);
	actionList.push_back(action);
}


PARABOLA_NAMESPACE_END

#endif