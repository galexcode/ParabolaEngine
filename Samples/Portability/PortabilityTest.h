#ifndef LightingTest_h__
#define LightingTest_h__

#include <ParabolaCore/GameCore.h>
#include <ParabolaCore/Sprite.h>
using namespace pE;

class LightingTest : public GameCore
{
public:
	

	void onCreate();
	void onRender();
	void onEvent(Event &event);
	void onUpdate(Time time);

	Renderer* m_render;
	Texture carTexture;
	Sprite carSprite;

	Vec2f m_pos;

	bool m_lighting;

};

#endif // LightingTest_h__
