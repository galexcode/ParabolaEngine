#ifndef StateIntro_h__
#define StateIntro_h__

#include <ParabolaCore/StateMachineNode.h>
#include <ParabolaCore/Textures.h>
#include <ParabolaCore/Sprite.h>
#include <ParabolaCore/Animation.h>
#include <ParabolaCore/AnimationGroupSequential.h>
#include <ParabolaCore/AnimationStall.h>
#include <ParabolaCore/AnimationFade.h>
#include <ParabolaCore/Logger.h>
using namespace pE;

class StateIntro : public StateMachineNode{
public:
	StateIntro(){
		m_introTexture.loadFromFile("Media/intro.png");
		s.setTexture(m_introTexture);
		
		animations.addAnimation(new AnimationFade(&s, 0, 255, 3));
		animations.addAnimation(new AnimationStall(2));
		animations.addAnimation(new AnimationFade(&s, 255, 0, 3));
		animations.play();
		animations.onFinish.connect(MAKE_SLOT_LOCAL(StateIntro, goToNext));
	}

	void goToNext(){
		emit(1, true);
	}

	bool onUpdate(Time &time){ 

		animations.onUpdate(time.asSeconds());

		return false;
	}

	bool onDraw(Renderer *renderer){
		View v;
		v.setRect(0,0, renderer->m_renderTarget->getSize().x, renderer->m_renderTarget->getSize().y);
		renderer->setView(v);

	//	renderer->drawDebugCircle(Vec2f(140,100), 30, Vec2f(), Color::Red);
		s.resize(renderer->m_renderTarget->getSize().x, renderer->m_renderTarget->getSize().y);
		renderer->draw(s);

		//renderer->drawDebugCircle(Vec2f(100,100), 30, Vec2f(), Color::Red);

		//LOG("TESTING");
		//PRINTLOG("asd", "%d\n", renderer->m_renderTarget->getSize().x);
		
		return false;
	}

	Sprite s;
	Texture m_introTexture;	
	AnimationGroupSequential animations;
	Clock c;
};

#endif // StateIntro_h__
