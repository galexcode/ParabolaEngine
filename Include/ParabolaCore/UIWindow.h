#ifndef PARABOLA_UIWINDOW_H
#define PARABOLA_UIWINDOW_H

#include "Platform.h"
#include "InputEvent.h"
#include "Renderer.h"

#include "UIControl.h"
#include "UIState.h"
#include "UISurface.h"
#include "UIToolTip.h"


PARABOLA_NAMESPACE_BEGIN

/**
	\ingroup UserInterface
	\class UIWindow
	\brief A Surface to draw user interface controls.
*/
class PARABOLA_API UIWindow{
public:
	/// Construct the window
	UIWindow();

	/// Returns a control in the hierarchy with the name, or NULL if not found
	UIControl* getControlByName(const String& name);

	/// Sets new boundaries to this UIWindow
	void setDimensions(Rect<float> dimensions);

	/// Get the position of the exact middle of this UIWindow
	Vec2f getMiddlePosition();

	/// Creates a new surface, which is underneath the relativeSurface specified
	/// \return NULL in case the relativeSurface is not a valid surface
	UISurface* createSurfaceBelow(UISurface* relativeSurface, const String& name);

	/// Get a surface by its name
	UISurface* getSurfaceByName(const String& name);

	/// Get the surface closer to the user
	/// \return the UISurface* or NULL if there are no surfaces
	UISurface* getTopSurface();

	/// Draw the UI
	void draw(Renderer* renderer);

	/// Update the state of the ui
	void update(float elapsedTime);


	/// Pushes a new event through the ui system
	bool pushEvent(Event& event);

private:
	/// The bounds of the window
	/// In nearly every case, the bounds match exactly the dimensions of the screen
	/// But for particular reasons, the working area of the user interface system can be smaller or bigger.
	Rect<float> m_bounds;

	/// Multiple layers in the interface controls
	/// m_surfaces[0] is the top layer, the closer to the user
	std::vector<UISurface*> m_surfaces;

	/// The shared state of this ui system
	UIState m_state;

	/// Tooltips
	UIToolTip* m_toolTip;
	bool m_showingToolTip;
	float m_timeSinceLastMouseMovement;
};

PARABOLA_NAMESPACE_END
#endif