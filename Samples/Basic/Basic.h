#ifndef Basic_h__
#define Basic_h__

#include <ParabolaCore/GameCore.h>
#include <ParabolaCore/Renderer.h>
#include <ParabolaCore/Sprite.h>
using namespace pE;

class BasicSample : public GameCore{
public:
	void onCreate(){
		m_renderer = Renderer::createAutomaticRenderer();
		m_view.setRect(0,0,1024,768);
		m_sampleTexture.loadFromFile("basic.png");
		m_sprite.setTexture(m_sampleTexture);
		m_sprite.setPosition(100,400);
	}
	
	void onEvent(InputEvent &event){
		if(event.type == InputEvent::TouchPressed){
			m_sprite.move(10,0);
		}
		if(event.type == InputEvent::MouseButtonPressed){
			m_sprite.move(10,0);
		}
		if(event.type == InputEvent::Resume){
			reloadTextures();
		}
	}

	void onRender(){
		m_renderer->setView(m_view);
		m_renderer->clearBuffers();
		for(float x = 100; x < 1000; x += 100){
			m_renderer->drawDebugCircle(Vec2f(x,300), 20, Vec2f(), Color(x/4,x/6,x/8));
		}
		m_renderer->draw(m_sprite);
		m_renderer->display();
	}

	Sprite m_sprite;
	View m_view;
	Renderer *m_renderer;
	Texture m_sampleTexture;
};

#endif // Basic_h__
