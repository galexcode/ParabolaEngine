#include <ParabolaCore/BrowserPluginInstance.h>
#include <ParabolaCore/ScriptGame.h>

#include <SFML/System.hpp>

PARABOLA_NAMESPACE_BEGIN

sf::Mutex BrowserPluginInstance::m_globalMutex;

/// Prepares the needed resources to run
BrowserPluginInstance::BrowserPluginInstance() : m_executionThread(&BrowserPluginInstance::runThread, this){
	thread_running = false;
	thread_initialized = false;
};

/// Starts the engine from an window handle
void BrowserPluginInstance::start(WindowHandle handle, std::map<String,String>& params){
	m_windowHandle = handle;
	m_params = params;
	m_executionThread.launch();
	//while(!thread_initialized){} // must wait
};

/// Finish execution of the plugin, back to starting state
void BrowserPluginInstance::finish(){
	/// Finish the engine environment and wait for its thread to be over
	m_sdk.finish();
	if(thread_running)
		m_executionThread.wait();
};

/// The thread controlling the engine and game
void BrowserPluginInstance::runThread(){
	thread_running = true;
	thread_initialized = false;

	/// some initialization
	
	//sf::Lock lock(m_globalMutex);
	m_sdk.createFromHandle(m_windowHandle);
	if(m_params.find("startup") != m_params.end()){
		m_sdk.getGameManager().addGameForExecution(new ScriptGame(m_params["startup"]));

	}
	else{
		m_sdk.getGameManager().addGameForExecution(new ScriptGame());
	}
	
		
	
	

	//m_sdk.getGameManager().addGameForExecution(new ScriptGame());

	while(m_sdk.isRunning()){
		thread_initialized = true;
		m_sdk.getWindow().setActive(true);
		m_sdk.update();
		//sf::sleep(sf::milliseconds(20));
		
	}

	/// some destruction
	thread_running = false;
};

/// Get the URL path of the webpage running the plugin
String BrowserPluginInstance::getURL(){
	return m_browserPageURL;
};

/// Set the URL of the webpage
void BrowserPluginInstance::setURL(const String& url){
	m_browserPageURL = url;
};


PARABOLA_NAMESPACE_END