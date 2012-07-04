#include "ParabolaCore/Window.h"
#include "ParabolaCore/Application.h"

#ifdef PARABOLA_DESKTOP
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#elif defined PARABOLA_ANDROID
//android specifics
#endif
 
#include <iostream>
using namespace std;


PARABOLA_NAMESPACE_BEGIN

#ifdef PARABOLA_DESKTOP
class Window::WindowImplementation : public sf::RenderWindow{
public:
	WindowImplementation() : sf::RenderWindow(){

	}
};
#elif defined PARABOLA_ANDROID
class Window::WindowImplementation{
public:

};
#endif
	
/// Default constructor
Window::Window(){
	myWindowImpl = new WindowImplementation();

	m_fullscreen = false;
}

/// Destroy the window
Window::~Window(){
	delete myWindowImpl;
} 

/// Attempts to launch a window if applicable
void Window::create(int screenWidth, int screenHeight){
#ifdef PARABOLA_DESKTOP
	myWindowImpl->create(sf::VideoMode(screenWidth,screenHeight,32), "Parabola Engine SDK", sf::Style::Default);
	m_fullscreen = false;
	myWindowImpl->setVerticalSyncEnabled(true);
	myWindowImpl->setFramerateLimit(60);
#endif
};

void Window::setFramerateLimit(int limit){
#ifdef PARABOLA_DESKTOP
	myWindowImpl->setFramerateLimit(limit);
#endif
};


/// Get the width of the screen/window
int Window::getWidth(){
#ifdef PARABOLA_DESKTOP
	return myWindowImpl->getSize().x;
#elif defined PARABOLA_ANDROID
	return Application::myInstance->myWindowWidth;
#endif
};

/// Get the height of the screen/window
int Window::getHeight(){
#ifdef PARABOLA_DESKTOP
	return myWindowImpl->getSize().y;
#elif defined PARABOLA_ANDROID
	return Application::myInstance->myWindowHeight;
#endif
};

/// Get the size of the window
Vec2i Window::getSize(){
	return (Vec2i(getWidth(), getHeight()));
};


/// Enable/Disable fullscreen mode
void Window::setFullscreen(bool enable){
#ifdef PARABOLA_DESKTOP
	if(enable){
		//activate fullscreen
		myWindowImpl->create(sf::VideoMode::getDesktopMode(), "Hawkeye", sf::Style::Fullscreen);
	}
	else{
		myWindowImpl->create(sf::VideoMode(1024,768,32), "Hawkeye", sf::Style::Default);
	}

	m_fullscreen = enable;

#endif
};

/// Convert a point from target coordinates to the view coordinates
Vec2f Window::convertCoords(const Vec2i &point, const View &view){
	// First, convert from viewport coordinates to homogeneous coordinates
	Vec2f coords;
// 	IntRect viewport = getViewport(view);
// 	coords.x = -1.f + 2.f * (point.x - viewport.left) / viewport.width;
// 	coords.y = 1.f  - 2.f * (point.y - viewport.top)  / viewport.height;

	coords.x = -1.f + 2.f * (point.x - 0.f) / getWidth();
	coords.y = 1.f  - 2.f * (point.y - 0.f)  / getHeight(); //CHEATING FOR NOW

	// Then transform by the inverse of the view matrix
	return view.getInverseTransform().transformPoint(coords);
};

/// Get the fullscreen mode
bool Window::getFullscreen(){
	return m_fullscreen;
};

/// Check if there is a pending event
bool Window::pollEvent(InputEvent &event){
#ifdef PARABOLA_DESKTOP
	static sf::Event tevent;
	if(myWindowImpl->pollEvent(tevent)){
		event.type = (InputEvent::EventType)(int)tevent.type;
		event.mouseButton = *static_cast<InputEvent::MouseButtonEvent*>((void*)&tevent.mouseButton);	

		//event = static_cast<InputEvent>((void*)&tevent);
		//memcpy(&event, &tevent, sizeof(event.type)/* + sizeof(InputEvent::KeyEvent)*/);
	//	cout<<"Size of event::; "<<sizeof(tevent)<<endl;
		return true;
	}
	else return false;
#else
	return false;
#endif
};

/// Discard all pending events
void Window::discardEvents(){
#ifdef PARABOLA_DESKTOP
	sf::Event event;
	while(myWindowImpl->pollEvent(event));
#endif
};

/// Swaps buffers
void Window::swapBuffers(){
#ifdef PARABOLA_DESKTOP
	myWindowImpl->display();
#elif defined PARABOLA_ANDROID
	
#endif
};
	
	
	/*
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
*/

PARABOLA_NAMESPACE_END