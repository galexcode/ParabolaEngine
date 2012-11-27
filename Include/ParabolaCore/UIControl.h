#ifndef PARABOLA_UIVIEW_H
#define PARABOLA_UIVIEW_H

#include "Platform.h"
#include "Rect.h"
#include "InputEvent.h"
#include "Signals.h"
#include "Strings.h"
#include "Renderer.h"
#include <vector>

PARABOLA_NAMESPACE_BEGIN

class PARABOLA_API UIControl : public sigc::trackable{
public:
	/// Base constructor of controls
	UIControl();

	/// Adds a child control
	void addControl(UIControl* control);

	/// Returns true when the control is subject of being layout in a grid or other organization form
	/// Most controls don't implement this function, as their default behavior is to respond to layouts always
	virtual bool respondsToLayouts();

	/// Callback to render itself, renders children
	virtual void draw(Renderer* renderer);

	/// Callback to handle events
	virtual bool onEventNotification(Event& event){return false;};

	/// Immediately sets the new size of the control 
	void setSize(float width, float height);

	/// Immediately sets the center of the control to a new position
	void setCenter(float x, float y);

	/// Immediately sets the center of the control to a new position
	void setCenter(Vec2f position);

	/// Define a new name for this control
	void setName(const String& name);

	/// Get the name of the control
	String getName();

	/// Signal emitted whenever the slider value changes
	sigc::signal<void, int> onValueChanged;

protected: // functions

	/// Callback when the position of the control changed, for updating nested objects
	virtual void onPositionChanged();

protected:
	/// The bounds of the control, if scissor tests are enabled, nothing is drawn outside this rect
	Rect<float> m_bounds;

	/// Unique name of the control in the hierarchy
	String m_name;

	std::vector<UIControl*> m_children;
};

PARABOLA_NAMESPACE_END
#endif