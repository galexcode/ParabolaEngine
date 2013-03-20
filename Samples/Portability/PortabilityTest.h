#ifndef PortabilityTest_h__
#define PortabilityTest_h__

#include <ParabolaCore/GameCore.h>
#include <ParabolaCore/Renderer.h>
using namespace pE;

class PortabilityTest : public GameCore
{
public:
	void onCreate();
	void onRender();
	void onEvent(Event &event);
	void onUpdate(Time time);
	
	Renderer* m_render;
	Vec2f m_pos;
};

#endif // PortabilityTest_h__
