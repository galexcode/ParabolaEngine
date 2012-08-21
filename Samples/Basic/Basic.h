#ifndef Basic_h__
#define Basic_h__

#include <ParabolaCore/GameCore.h>
#include <ParabolaCore/Renderer.h>
#include <ParabolaCore/Sprite.h>
#include <ParabolaCore/Text.h>
#include <ParabolaCore/ProgressBar.h>
using namespace pE;

#include <iostream>
using namespace std;

class BasicSample : public GameCore{
public:

	ProgressBar progress;

	void onCreate(){
		m_renderer = Renderer::createAutomaticRenderer();
		m_view.setRect(0,0,1024,768);
		m_sampleTexture.loadFromFile("basic.png");
		m_sprite.setTexture(m_sampleTexture);
		m_sprite.setPosition(100,400);


		//t.setString("I love you this much: 0");
		much = 0;
		
		t.setString("Ok, text works now. great.");
		

		
	//	cout<<"t1 quad count: "

	}
	int much;
	
	void onEvent(Event &event){ 
		if(event.type == Event::TouchPressed){
			m_sprite.move(10,0);

			++much;
			t.setString("I love you this much: " + String::number(much));

			progress.reset();
		}
		if(event.type == Event::MouseButtonPressed){
			m_sprite.move(10,0);
		}
		if(event.type == Event::Resume){
			reloadTextures();
		}
	}

	void onUpdate(Time time){
		progress.update(time.asSeconds());
	}

	void onRender(){
		m_renderer->setView(m_view);
		m_renderer->clearBuffers();
		for(float x = 100; x < 1000; x += 100){
			m_renderer->drawDebugCircle(Vec2f(x,300), 20, Vec2f(), Color(x/4,x/6,x/8));
		}

		m_renderer->draw(progress);	
	
		m_renderer->draw(t);
		m_renderer->draw(m_sprite);
		m_renderer->display();
	}
	Text t;
	Sprite m_sprite;
	View m_view;
	Renderer *m_renderer;
	Texture m_sampleTexture;
};

#endif // Basic_h__
