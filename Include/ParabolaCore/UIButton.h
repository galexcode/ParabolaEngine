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

	template<typename T>
	void setProperty(const String& propertyName, const T& propertyValue);

	/// Callback to render itself, renders children
	virtual void draw(Renderer* renderer);

	virtual UIControl* clone();

	/// Signal is emitted when the button is clicked
	sigc::signal<void> onClick;

	bool hover;

	Color m_color;

private:
	String m_label;
};

template<typename T>
void UIButton::setProperty(const String& propertyName, const T& propertyValue)
{
	// Give precedence to parent
	UIControl::setProperty<T>(propertyName, propertyValue);

	if(propertyName == "color")
	{
		m_color = propertyValue;
	}
}


PARABOLA_NAMESPACE_END
#endif // UIButton_h__
