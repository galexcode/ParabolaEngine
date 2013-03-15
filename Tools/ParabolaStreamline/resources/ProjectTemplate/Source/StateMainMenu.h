#ifndef StateMainMenu_h__
#define StateMainMenu_h__

#include <ParabolaCore/StateMachineNode.h>
#include <ParabolaCore/Textures.h>
#include <ParabolaCore/Sprite.h>
#include <ParabolaCore/Animation.h>
#include <ParabolaCore/AnimationGroupSequential.h>
#include <ParabolaCore/AnimationStall.h>
#include <ParabolaCore/AnimationFade.h>
#include <ParabolaCore/AnimationPosition.h>
#include <ParabolaCore/RocketContext.h>
#include <ParabolaCore/Logger.h>
#include <ParabolaCore/Views.h>
#include <ParabolaCore/Renderer.h>
#include "Globals.h"
using namespace pE;

class StateMainMenu : public StateMachineNode{
public:
	StateMainMenu(){
		
	}

	void rocketEvent(String event){
		if(event == "start"){
			emit(2, true);
		}
	}

	void onActivate();

	bool onEvent(Event &event){
		if(m_animation.getStatus() != AnimationStates::Playing)
			m_ui->processEvent(event);
		return false;
	}

	bool onUpdate(Time &time){ 

		m_animation.onUpdate(time.asSeconds());
		return false;
		
	}

	bool onDraw(Renderer *renderer){
		View v;
		v.setRect(0,0,renderer->m_renderTarget->getSize().x, renderer->m_renderTarget->getSize().y);
		renderer->setView(v);
		renderer->drawRocketContext(m_ui);
		//renderer->drawDebugCircle(Vec2f(20,200), 30, Vec2f(), Color::Red);
		return false;
	}

	AnimationPosition m_animation;
};

#endif // StateIntro_h__
