#include "PortabilityTest.h"
#include <ParabolaCore/CGL.h>

#include <iostream>
using namespace std;
	
void PortabilityTest::onCreate()
{
	m_render = Renderer::createAutomaticRenderer(&getWindow());
	
	m_pos.x = m_pos.y = 250;
}

void PortabilityTest::onEvent(Event &event)
{
	if(event.type == Event::TouchPressed)
	{
		m_pos.x = event.x;
		m_pos.y = event.y;
	}
}

void PortabilityTest::onUpdate(Time time)
{
	
}

void PortabilityTest::onRender()
{
	m_render->clearBuffers();
	
	View v;
	v.setRect(0,0,500,500);
	m_render->pushView(v);
	
	m_render->drawDebugQuad(m_pos.x, m_pos.y, 0, 500*0.9, 500*0.9, Color::Red);
}
