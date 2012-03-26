#include "ParabolaCore/Engine.h"
#include "ParabolaCore/Window.h"

PARABOLA_NAMESPACE_BEGIN

/// Static instance of the engine, singleton
Engine* Engine::myInstance = NULL;


/// Private constructor
Engine::Engine(const EngineProfile &profile) : myRunning(false), myGames(this) {
	myInstance = this;
	myProfile = profile;
	myProfile.myParent = this;
};

/// Safely destructs the engine
Engine::~Engine(){
	shutdownSubsystems();
	myInstance = NULL;
};

/// Destroys the engine environment
void Engine::destroy(){
	if(myInstance){
		delete myInstance;
		myInstance = NULL;
	}
};

/// Creates the engine if it was not created already
/// Returns the pointer to the engine
Engine* Engine::create(){
	if(myInstance == NULL){
		new Engine();
	}

	myInstance->configure();
	return myInstance;
};


/// Creates the engine if it was not created already
/// Returns the pointer to the engine
Engine* Engine::create(const StringList &arglist){
	if(!myInstance){
		Engine *e = new Engine();
		e->program_arguments = arglist;
	}
	myInstance->configure();
	return myInstance;
}

/// Creates the engine if it was not created already
/// Returns the pointer to the engine
Engine* Engine::create(const EngineProfile &profile, const StringList &arglist){
	if(!myInstance){
		Engine *e = new Engine(profile);
		e->program_arguments = arglist;
	}
	myInstance->configure();
	return myInstance;
}

/// Creates the engine if it was not created already
/// Returns the pointer to the engine
Engine* Engine::create(const EngineProfile &profile){
	if(!myInstance){
		Engine *e = new Engine(profile);
	}
	myInstance->configure();
	return myInstance;
}

/// Returns a pointer to the engine environment
/// Returns NULL if it was not created yet
Engine* Engine::instance(){
	return myInstance;
};

/// Get the profile of the engine
/// You can configure the engine through this object.
EngineProfile& Engine::profile(){
	return myProfile;
};	

/// Checks if the engine is running
bool Engine::running(){
	return myRunning;
};

/// Configures all the engine environment from the profile settings currently defined
void Engine::configure(){



	configureWindow();
	




	myRunning = true;
};

/// Configure the window if necessary
/// Uses the profile settings
void Engine::configureWindow(){
	if(myProfile.run_window){
		if(!myWindow){
			myWindow = new Window();
		}

		//configure it and launch

		myWindow->Create(sf::VideoMode(1024, 768, 32), "Engine !");
		myWindow->EnableVerticalSync(true);
	}
	else{
		if(myWindow){
			myWindow.destroy();
		}
	}
};

/// Processes events, updates and renders the games
/// This is a wrapper function for all steps of updating the environment
/// This can be called continuously and it will control the execution of the environment by itself
void Engine::updateCore(){
	// Event processing - as fast as possible
	if(myWindow){
		static Event event;
		// Will push the events to the handlers, if any
		while(myWindow->eventDispatcher().catchEvent(event, true)){
			myGames.pushEvent(event); // Will push every single event to the games
		}	
	}
	else{
		myGames.checkEvents();
	}

	// Update the games as desired - all settings are inside, including a clock
	myGames.update();

	// Draw a frame - also controlled internally, as it may not draw at all
	myGames.draw();
};

/// Clears the environment allocated resources
void Engine::shutdownSubsystems(){

};


/// Get the instance of the game manager
GameCoreManager& Engine::gameManager(){
	return myGames;
};
/// Get the window the engine currently owns
linked_ptr<Window>& Engine::getWindow(){
	return myWindow;
};

/// Begins destruction of the engine
void Engine::close(){	
	myRunning = false;
};


PARABOLA_NAMESPACE_END
