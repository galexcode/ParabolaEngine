#ifndef Basic_h__
#define Basic_h__

#include <ParabolaCore/GameCore.h>
//#include <ParabolaCore/Renderer.h>
using namespace pE;

class BasicSample : public GameCore{
public:
	void onCreate(){
		//m_renderer = Renderer::createAutomaticRenderer();
	}

	void onRender(){
	/*	View v;
		v.setRect(0,0,1000,1000);
		m_renderer->applyView(v);
		m_renderer->clearBuffers();
		m_renderer->drawDebugCircle(Vec2f(200,300), 40, Vec2f(), Color(100,200,100));
		m_renderer->display();*/
	}

	//Renderer *m_renderer;
};

#endif // Basic_h__
