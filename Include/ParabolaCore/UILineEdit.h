#ifndef UILineEdit_h__
#define UILineEdit_h__

#include "Platform.h"
#include "UIControl.h"
#include "Text.h"

PARABOLA_NAMESPACE_BEGIN

class PARABOLA_API UILineEdit : public UIControl{
public:
	bool onEventNotification(Event& event);

	void setText(const String& text);

	void draw(Renderer* renderer);

	Text t;
	String s;
};

PARABOLA_NAMESPACE_END
#endif // UILineEdit_h__
