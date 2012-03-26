#ifndef PARABOLA_WINDOW_H
#define PARABOLA_WINDOW_H

#include "Platform.h"
#include "Strings.h"
#include "Events.h"
#include <SFML/Graphics/RenderWindow.hpp>

PARABOLA_NAMESPACE_BEGIN	

	typedef sf::VideoMode VideoMode;
	/**
		\ingroup Graphics

		\class Window
		\brief Represents a window of the underlying OS.

		Besides the ability to create a window, it also makes it ready for imeddiate OpenGL rendering.
	*/
	class PARABOLA_API Window : public sf::RenderWindow{
	public:
		/// Creates a uninitialized window
		Window();
		/// Creates a window out of some settings
		/// \param mode is the window size and color depth
		/// \param title is the text on the top of the window
		/// \param style is the configurable style of the window
		/// \param settings is the configuration of the OpenGL version and parameters such as antialiasing
		Window(VideoMode mode, const String &title, Uint32 style = sf::Style::Default, const sf::ContextSettings &settings = sf::ContextSettings());
		/// Creates a window out of another window
		/// This normally means to take the client space of another window and adopt it
		/// Common use is to make this window rendering appear as a specific frame in another application
		Window(sf::WindowHandle handle, const sf::ContextSettings &settings = sf::ContextSettings());
		/// Safely destructs this window resource
		~Window();

		/// Get the event dispatcher for this window
		EventDispatcher& eventDispatcher();

	private:
		EventDispatcher myDispatcher;
	};

PARABOLA_NAMESPACE_END

#endif