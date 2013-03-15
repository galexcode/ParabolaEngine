#ifndef GameQuiz_h__
#define GameQuiz_h__

#include <ParabolaCore/GameCore.h>
#include <ParabolaCore/Renderer.h>
#include <ParabolaCore/StateMachine.h>
#include <ParabolaCore/AnimationFloat.h>

#include <ParabolaCore/Kinesis.h>
using namespace pE;

#include "StateIntro.h"
#include "StateMainMenu.h"
#include "StateBasicSession.h"

#include "Globals.h"

#include <iostream>
using namespace std;

class GameQuiz : public GameCore{
public:
	void onCreate(){
		m_renderer = Renderer::createAutomaticRenderer(&getWindow());

		/*m_game = this; 
		m_ui = RocketContext::create("global_context", getWindow().getSize());
		m_ui->loadFont("Media/Fonts/DroidSansFallback.ttf");

		m_machine.setState(0, new StateIntro());
		m_machine.setState(1, new StateMainMenu());
		m_machine.setState(2, new StateBasicSession());
		m_machine.pushState(0);*/

		position = Vec2f(100,100);

		af.setVariable(&x);
		af.setCurrentValue(100);
		af.setTargetValue(400);
		af.setDuration(5);		
		af.play();
		

	}

	void onEvent(Event &event){
		//m_machine.propagateEvent(event);


	}

	void onUpdate(Time time){
		//m_machine.updateStates(time);
		af.update(time.asSeconds());
	}

	void onRender(){
		m_renderer->clearBuffers();
		//m_machine.drawStates(m_renderer);

		View v;
		v.setRect(0,0,500,256);
		m_renderer->setView(v);

		m_renderer->drawDebugCircle(Vec2f(x, position.y),20, Vec2f(), Color(255,0,0, 255));

		m_renderer->display();
	}

	/// State machine
	StateMachine m_machine;


	Vec2f position;
	AnimationFloat af;
	float x;

	/// Renderer
	Renderer *m_renderer;
};

#endif // GameQuiz_h__
