#ifndef PARABOLA_WINDOW_H
#define PARABOLA_WINDOW_H

#include "Platform.h"
#include "Vectors.h"
#include "InputEvent.h"
#include "Views.h"

PARABOLA_NAMESPACE_BEGIN

/**
	\ingroup Graphics

	\class Window
	\brief Represents a screen or window where the engine is able to draw graphics

*/
class PARABOLA_API Window{
public:
	/// Default constructor
	Window();		
		
	/// Destroy the window
	~Window();

	/// Attempts to launch a window if applicable
	void create(int screenWidth, int screenHeight);

	/// Convert a point from target coordinates to the view coordinates
	Vec2f convertCoords(const Vec2i &point, const View &view);

	/// Get the width of the screen/window
	int getWidth();

	/// Get the height of the screen/window
	int getHeight();

	/// Get the size of the window
	Vec2i getSize();

	/// Discard all pending events
	void discardEvents();

	/// Enable/Disable fullscreen mode
	void setFullscreen(bool enable);

	/// Get the fullscreen mode
	bool getFullscreen();

	/// Swaps buffers
	void swapBuffers();

	/// Check if there is a pending event
	bool pollEvent(InputEvent &event);

	void setFramerateLimit(int limit);


private:
	class WindowImplementation;
	WindowImplementation* myWindowImpl;		

	bool m_fullscreen;
};

PARABOLA_NAMESPACE_END
#endif