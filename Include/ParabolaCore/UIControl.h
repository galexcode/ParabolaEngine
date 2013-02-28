#ifndef PARABOLA_UIVIEW_H
#define PARABOLA_UIVIEW_H

#include "Platform.h"
#include "Rect.h"
#include "InputEvent.h"
#include "Signals.h"
#include "Strings.h"
#include "Renderer.h"
#include <vector>

#include "AnimationDimension.h"
#include "AnimationPosition.h"

#include "UILayout.h"
#include "UIState.h"

PARABOLA_NAMESPACE_BEGIN

namespace UISizePolicy
{
	enum Policy
	{
		Normal,
		ParentPercent
	};
};

class PARABOLA_API UIControl : public sigc::trackable, public Animable{
public:
	friend class UILayout;

	/// Base constructor of controls
	UIControl();

	/// Adds a child control
	void addControl(UIControl* control);

	/// Set a new layout to the control
	void setLayout(UILayout* layout);

	/// Get the currently assigned layout controller
	/// \return NULL if there is no layout controller assigned
	UILayout* getLayout();

	/// Get the number of children of this control
	int getChildCount();

	/// Is the control able to get input focus or not?
	virtual bool isFocusable();

	/// Check if the control currently has focus
	bool hasFocus();

	/// Attempts focus on this control
	bool focus();

	/// Remove focus from the element
	void blur();

	/// Get a child at a index
	UIControl* getChild(int index);

	/// Get the current size of the control
	Vec2f getSize();

	/// Get the bounding rect of this control and all its children
	FloatRect getContentBounds();

	/// Returns the UIWindow context or NULL if not attached
	UIStateContext* getContext();

	/// Returns true when the control is subject of being layout in a grid or other organization form
	/// Most controls don't implement this function, as their default behavior is to respond to layouts always
	virtual bool respondsToLayouts();

	/// Requests a tool tip text label from the control
	/// If only a empty string is returned, no tooltip is shown
	virtual String getToolTipLabel();

	void innerDraw(Renderer* renderer);

	/// Callback to render itself, renders children
	virtual void draw(Renderer* renderer);

	/// Callback to handle events
	virtual bool onEventNotification(Event& event);

	virtual bool onKeyPressed(Keyboard::Key key);
	virtual bool onTextEvent(Uint32 code);

	virtual void onAttach(){}

	/// Callback when the control is resized
	virtual void onResize();

	template<typename T>
	void setProperty(const String& propertyName, const T& propertyValue);

	/// Immediately sets the new size of the control 
	void setSize(float width, float height);

	/// Immediately sets the center of the control to a new position
	void setCenter(float x, float y);

	/// Immediately sets the center of the control to a new position
	void setCenter(Vec2f position);

	/// Set the position of the control
	void setPosition(float x, float y);

	/// Define a new name for this control
	void setName(const String& name);

	/// Deep clone of the control and its hierarchy
	virtual UIControl* clone();

	/// Get bounds of the control
	FloatRect getBounds();

	/// Get the name of the control
	String getName();

	/// Update the control
	void onUpdate(float elapsedTime);

	/// Update layout of children
	void updateLayout();

	void setRect(FloatRect rect);

	FloatRect getRect();

	Vec2f getMiddlePosition();

	/// Resizes the control over a defined time
	/// The lower border of the control will become at target position
	void resizeToPoint(float x, float y, float duration);

	void resize(float width, float height, float duration);

	void reposition(float x, float y, float duration);

	/// Signal emitted whenever the slider value changes
	sigc::signal<void, int> onValueChanged;

	UIStateContext* m_stateContext;

	/// Hierarchicly sets the context to all children
	void setContext(UIStateContext* states);

	bool m_clipContents; ///< Whether the contents of the control itself are clipped at the border
	bool m_clipChildren; ///< Whether the children are clipped on the control rectangle
	/// Is the control being rendered?
	bool m_visible;
	bool m_stretchForContents;
	bool m_drawBorder; /// temp
protected: // functions

	/// Callback when the position of the control changed, for updating nested objects
	virtual void onPositionChanged();


protected:
	/// The bounds of the control, if scissor tests are enabled, nothing is drawn outside this rect
	Rect<float> m_bounds;
	Vec2f m_minimumDimensions;
	Vec2f m_maximumDimensions;
	UISizePolicy::Policy m_maximumWidthPolicy, m_maximumHeightPolicy;

	bool m_hasFocus;



	Color m_backgroundColor;
	Color m_topBorderColor, m_bottomBorderColor, m_leftBorderColor, m_rightBorderColor;

	/// The layout controller for this control
	UILayout* m_layoutController;

	/// Unique name of the control in the hierarchy
	String m_name;

	/// Children of the control
	std::vector<UIControl*> m_children;

	/// Parent of the control, if any
	UIControl* m_parent;

	/// The resize animation
	AnimationDimension m_resizeAnimation;
	AnimationPosition m_positionAnimation;

	/// Making this class able to animate sizes
	virtual void animable_set_size(float x, float y);
	virtual Vec2f animable_get_size();
	virtual void animable_set_position(float x, float y);
	virtual Vec2f animable_get_position();
};

template<typename T>
void UIControl::setProperty(const String& propertyName, const T& propertyValue)
{
	if(propertyName == "background-color")
	{
		m_backgroundColor = propertyValue;
		return;
	}
	else if(propertyName == "border-top-color")
	{
		m_topBorderColor = propertyValue;
	}
	else if(propertyName == "border-bottom-color")
	{
		m_bottomBorderColor = propertyValue;
	}
	else if(propertyName == "border-left-color")
	{
		m_leftBorderColor = propertyValue;
	}
	else if(propertyName == "border-right-color")
	{
		m_rightBorderColor = propertyValue;
	}
};

PARABOLA_NAMESPACE_END
#endif