#ifndef PARABOLA_BROWSERPLUGININSTANCE_H
#define PARABOLA_BROWSERPLUGININSTANCE_H

#include "Platform.h"
#include "Engine.h"
#include <SFML/System/Thread.hpp>
#include <SFML/System/Mutex.hpp>
#include <SFML/System/Lock.hpp>


PARABOLA_NAMESPACE_BEGIN
typedef void* WindowHandle;

/**
	\ingroup Core
	\class BrowserPluginInstance
	\brief One web player instance. This is equivalent to one window running the plugin within a webpage

	1:1 relationship html element running the plugin to an instance of the class
*/
class PARABOLA_API BrowserPluginInstance{
public:
	/// Prepares the needed resources to run
	BrowserPluginInstance();

	/// Starts the engine from an window handle
	void start(WindowHandle handle, std::map<String,String>& params);

	/// The thread controlling the engine and game
	void runThread();

	/// Finish execution of the plugin, back to starting state
	void finish();

	/// Get the URL path of the webpage running the plugin
	String getURL();

	/// Set the URL of the webpage
	void setURL(const String& url);


	sf::Thread m_executionThread;
	Engine m_sdk;
	WindowHandle m_windowHandle;
	std::map<String,String> m_params;

	/// The URL of the path where the plugin's HTML page is running
	String m_browserPageURL;

	bool thread_running;
	bool thread_initialized;

	static sf::Mutex m_globalMutex;
};

PARABOLA_NAMESPACE_END
#endif