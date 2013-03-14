#include <ParabolaCore/UIManager.h>
#include <ParabolaCore/UIWindow.h>
#include <ParabolaCore/Renderer.h>

#include <iostream>
using namespace std;

PARABOLA_NAMESPACE_BEGIN
UIWindow* UIManager::create(const String &name)
{
	if(m_windows.find(name) == m_windows.end())
	{
		m_windows[name] = (new UIWindow());
	}
	m_windows[name]->setRect(area);
	return m_windows[name];
}

void UIManager::draw(const String& name, Renderer* renderer)
{
	if(m_windows.find(name) == m_windows.end())
	{
		cout<<"INVALID WINDOW FOR DRAWING."<<endl;
		return;
	}

	View windowView;
	windowView.setRect(0,0,renderer->m_renderTarget->getSize().x, renderer->m_renderTarget->getSize().y);
	renderer->pushView(windowView);
	m_windows[name]->draw(renderer);
	renderer->popView();
}

void UIManager::setArea(float x, float y, float w, float h)
{
	for(std::map<String,UIWindow*>::iterator it = m_windows.begin(); it != m_windows.end(); it++)
	{
		(*it).second->setRect(FloatRect(x,y,w,h));
		
	}
	area = FloatRect(x,y,w,h);
}
PARABOLA_NAMESPACE_END