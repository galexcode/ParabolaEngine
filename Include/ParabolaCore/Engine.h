/*
Copyright (C) 2010-2012 Artur Moreira - ParabolaEngine under zlib license

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#ifndef PARABOLA_ENGINE_H
#define PARABOLA_ENGINE_H

#include "Platform.h"
#include "Clock.h"
#include "Strings.h"
#include "GameCoreManager.h"
#include "Window.h"

PARABOLA_NAMESPACE_BEGIN

/**
	\ingroup Core
	\class Engine
	\brief Game engine environment. Responsible to create a game running platform.

	An OS process may be running more than one engine instances concurrently. An example is the browser plugin.



	@author Artur Moreira
*/
class PARABOLA_API Engine{
public:
	
	class Settings{
	public:
		Settings(){
			windowWidth = 1024;
			windowHeight = 768;
		}
		/// Window dimensions in the applicable platforms
		int windowWidth;
		int windowHeight;
	};

	/// Default construction
	Engine();

	/// Safely destructs the engine
	virtual ~Engine();

	/// Sets the engine back to its uninitialized state
	void finish();

	/// Automatic update of the engine state
	/// Will fetch pending events, update the games at fixed steps and do rendering
	void update();

	/// Get a reference to the engine settings
	Settings& getSettings();

	/// Launches the necessary services, like the window, if on a pc
	void create();

	/// Launches the necessary services of the engine from new settings
	void create(const Settings& settings);
	
	void createFromHandle(void* handle);

	/// Check if the engine is currently ready to function normally
	bool isRunning();

	/// Get the window/screen of this environment
	Window& getWindow();

	/// Get the game manager
	GameCoreManager& getGameManager();

	

private:

	/// Check
	bool m_running;

	GameCoreManager myGameManager;
	/// The engine always runs on a graphic area
	/// That may be the mobile phone screen, or an application window
	Window myWindow;
	/// Clock of the engine
	Clock myClock;
	Int64 myLastUpdate;
	/// Startup settings
	Settings mySettings;

};




		/*/// Begins destruction of the engine
		void close();

		/// Creates the engine if it was not created already
		/// Returns the pointer to the engine
		static Engine* create();

		/// Creates the engine if it was not created already
		/// Returns the pointer to the engine
		static Engine* create(const StringList &arglist);

		/// Creates the engine if it was not created already
		/// Returns the pointer to the engine
		static Engine* create(const EngineProfile &profile, const StringList &arglist);

		/// Creates the engine if it was not created already
		/// Returns the pointer to the engine
		static Engine* create(const EngineProfile &profile);

		/// Destroys the engine enviroment
		static void destroy();

		/// Returns a pointer to the engine environment
		/// Returns NULL if it was not created yet
		static Engine* instance();

		/// Get the profile of the engine
		/// You can configure the engine through this object.
		EngineProfile& profile();

		/// Checks if the engine is running
		bool running();

		/// Configures all the engine environment from the profile settings currently defined
		void configure();

		/// Configure the window if necessary
		/// Uses the profile settings
		void configureWindow();

		/// Processes events, updates and renders the games
		/// This is a wrapper function for all steps of updating the environment
		/// This can be called continuously and it will control the execution of the environment by itself
		void updateCore();

		/// Get the instance of the game manager
		GameCoreManager& gameManager();

		/// Get the window the engine currently owns
		Window* getWindow();

	protected:
		/// Clears the environment allocated resources
		void shutdownSubsystems();

	private:
		
		/// Private constructor
		Engine(const EngineProfile &profile = EngineProfile::DefaultProfile());

		/// Profile of the engine
		EngineProfile myProfile;

		/// Static instance of the engine, singleton
		static Engine* myInstance;

		/// Program command line arguments, if passed.
		StringList program_arguments;

		/// The link to a window if desired
		linked_ptr<Window> myWindow;

		/// Game manager
		GameCoreManager myGames;

		/// Execution control
		bool myRunning;


		/// Scripting interface - all defined in AngelScriptInterfaces.cpp
		friend class ASEngine;
		int as_gameCount();
		String as_gameNameAt(int i);
		void dummy();
		void as_createScriptGame(const String &name, const String &entry);*/


PARABOLA_NAMESPACE_END
#endif
