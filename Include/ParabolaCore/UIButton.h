#ifndef UIButton_h__
#define UIButton_h__

#include "Platform.h"
#include "UIControl.h"
#include "Strings.h"

PARABOLA_NAMESPACE_BEGIN

/**
	\ingroup UserInterface
	\class UIButton
	\brief A simple button control
*/
class PARABOLA_API UIButton : public UIControl{
public:
	/// Constructs the button
	UIButton();

	/// Constructs the button from a label text
	UIButton(const String& title);

	/// Callback to handle an event
	bool onEventNotification(Event& event);

	/// Callback to render itself, renders children
	virtual void draw(Renderer* renderer);

	/// Signal is emitted when the button is clicked
	sigc::signal<void> onClick;

	Color m_color;

private:
	String m_label;
};

PARABOLA_NAMESPACE_END
#endif // UIButton_h__
