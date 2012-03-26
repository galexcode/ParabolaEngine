#include "ParabolaCore/Window.h"

PARABOLA_NAMESPACE_BEGIN

/// Creates a uninitialized window
Window::Window() : sf::RenderWindow(){
	myDispatcher.Parent = this;
};
/// Creates a window out of some settings
/// \param mode is the window size and color depth
/// \param title is the text on the top of the window
/// \param style is the configurable style of the window
/// \param settings is the configuration of the OpenGL version and parameters such as antialiasing
Window::Window(VideoMode mode, const String &title, Uint32 style, const sf::ContextSettings &settings)
: sf::RenderWindow(mode, title, style, settings) 
{

};
/// Creates a window out of another window
/// This normally means to take the client space of another window and adopt it
/// Common use is to make this window rendering appear as a specific frame in another application
Window::Window(sf::WindowHandle handle, const sf::ContextSettings &settings)
: sf::RenderWindow(handle, settings)
{

};
/// Safely destructs this window resource
Window::~Window() {

};

/// Get the event dispatcher for this window
EventDispatcher& Window::eventDispatcher(){
	return myDispatcher;
};


PARABOLA_NAMESPACE_END