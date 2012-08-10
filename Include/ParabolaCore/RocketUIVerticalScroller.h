#include "Rocket/Core/Context.h"
#include "Rocket/Core/Element.h"
#include "Rocket/Core/EventListener.h"

#include "Platform.h"
#include "RocketDocument.h"

PARABOLA_NAMESPACE_BEGIN

class UIElementScroll : public RocketElement, public Rocket::Core::EventListener
{
public:
	UIElementScroll(const Rocket::Core::String& tag);
	~UIElementScroll();

	static void registerWithlibRocket();

	virtual void OnChildAdd(Rocket::Core::Element* child);

	virtual void ProcessEvent(Rocket::Core::Event& event);

	virtual void OnUpdate();

private:
	Rocket::Core::Context* mContext;

	bool mScrolling;
	int mMouseY;
	int mMouseDownY;
	float mMouseDownTime;

	float mLastUpdate;

	float mScrollValue;
	float mScrollVelocity;
};

PARABOLA_NAMESPACE_END
