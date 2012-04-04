#include "ParabolaCore/StoryAction.h"
#include "ParabolaCore/StoryPlayer.h"
#include "ParabolaCore/SoundPlayer.h"
#include "ParabolaCore/SceneRenderer.h"
#include "ParabolaCore/Text.h"

PARABOLA_NAMESPACE_BEGIN


SceneRenderer* StoryAction::getRenderer(){
	if(parent){
		if(parent->parent){
			return parent->parent->renderer.get();
		}
	}
	return NULL;
}





int StoryActionWait::onUpdate(double deltaTime){
	elapsedTime += deltaTime;

	if(elapsedTime >= duration){
		// This task has finished
		std::cout<<">> Wait: task has finished."<<std::endl;
		//parent->stopTaskExecution(this);
		return TERMINATE;
	}

	return CONTINUE;
}


int StoryActionLog::onUpdate(double deltaTime){
	std::cout<< ">> Log: "<<message<<std::endl;
	return TERMINATE;
};

/************************************************************************/
/* ShowSub                                                              */
/************************************************************************/

int StoryActionShowSub::onUpdate(double deltaTime){	
	return NO_LOCK;
};

void StoryActionShowSub::onDraw(){
	SceneRenderer* renderer = getRenderer();
	if(renderer){
//		renderer->draw(Text(message,x,y));
	}
}

/************************************************************************/
/* PlaySound                                                            */
/************************************************************************/

int StoryActionPlaySound::onUpdate(double deltaTime){
	if(played)
	{
		/*linked_ptr<SoundPlayer> sp = parent->parent->soundPlayer;
		/*if(sp){
			sp->cleanSoundList();
			return TERMINATE;
		}*/
		/*if(sound->GetStatus() == sf::SoundSource::Stopped){
			sp->cleanSoundList();
			return TERMINATE;
		}*/

		return CONTINUE;
	}

	std::cout<< ">> PlaySound: task completed"<<std::endl;
	if(parent){
		StoryPlayer *story_player = parent->parent;

		if(story_player){
			/*if(story_player->soundPlayer){
				sound = story_player->soundPlayer->playOnce(message);
				played = true;
			}*/

			//std::cout<<"Found story player ! "<<story_player->storyCount()<<endl;
		}	

	
	}
	return NO_LOCK;
};
PARABOLA_NAMESPACE_END