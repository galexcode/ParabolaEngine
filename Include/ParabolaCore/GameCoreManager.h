#ifndef PARABOLA_GAMECOREMANAGER_H
#define PARABOLA_GAMECOREMANAGER_H

#include "Platform.h"
#include "LinkedPointer.h"

#include "GameCore.h"
#include "GameCoreInstancer.h"

#include <SFML/System/Clock.hpp>

#include <list>
#include <map>

PARABOLA_NAMESPACE_BEGIN

	class Engine;
	class Event;

	/**
		\ingroup Core
		\class GameCoreManager
		\brief Represents the multi task manager that an Engine contains.

		It manages the execution of concurrent games. There are two dualities to note:

		Instantiate and Destroy - meaning when you launch a fresh instance of a game
		                        - and when you destroy it completely

		Active or Inactive - meaning if the game is currently executing or just frozen

		Also note that only one game may draw at a time. 
		That will be the one in the front of the executing list.
		By definition, that game will have its name on the window title and will be able to draw in the screen

		By default, when a game stops execution (but still in memory), 
		the next one in the execution list will take over.
		However, if there is a home application registered, it will take over.

		When the execution list is emptied, if there is a home application registered, it takes over,
		otherwise the engine destroys itself.

		\note Cannot be instantiated, it comes only with the engine instance.
	*/
	class PARABOLA_API GameCoreManager{
	public:
		/// Safely destroys the game manager
		~GameCoreManager();

		/// Pushes the event to the active drawing game
		void pushEvent(const Event &event);

		/// Normally called when the engine has no window, therefore the game has to fetch events itself
		void checkEvents();

		/// Make the games update
		void update();

		/// Make the active drawing game render itself
		void draw();

		/// Schedules the destruction of the game for when the update step ends.
		void destroy(GameCore *game);

		/// Instances the game of type T
		/// execute boolean will decide if the game also executes directly or not.
		template<typename T>
		GameCore* instance(const String &name, bool execute = true);

		/// Registers an instancer so it can launch games later 
		/// using for example launchFromInstancer(name) by passing the same name used here
		/// In a home application, you would see this name as the icon label,
		/// and when clicking it, it would launch your game, the way you want to.
		/// Returns the name that the instancer was registered under,
		/// It will be equal to the string passed, unless it was already taken.
		String registerInstancer(GameInstancerInterface *instancer, const String &name);

		/// Searches for the desired instancer and launches the game
		GameCore* launchFromInstancer(const String &name);

		/// Get the number of alive games, the ones instantiated
		int aliveGameCount();

	private:
		/// Private constructor - can only be instanced by the engine
		GameCoreManager(Engine *parent);

		/// All games alive in memory.
		/// Uses smart pointers so it can be destroyed anywhere
		std::list<linked_ptr<GameCore> > myGameList;

		/// The games actually running
		std::list<linked_ptr<GameCore> > myExecutionList;

		/// Game instancers
		std::map<String, GameInstancerInterface* > myGameInstancers;

		/// A possible home app
		linked_ptr<GameCore> myHomeApp;

		/// Clock for updating games
		sf::Clock clock;

		/// Parent Engine
		Engine *myParent;
		friend class Engine;
	};

	/// Instances the game of type T
	/// execute boolean will decide if the game also executes directly or not.
	template<typename T>
	GameCore* GameCoreManager::instance(const String &name, bool execute){
		linked_ptr<GameCore> game;
		game = reinterpret_cast<GameCore*>(new T());
		game->myName = name;
		game->myParent = this;
		game->setWindow(myParent->getWindow());
		myGameList.push_back(game);

		game->innerCreate();

		if(execute){
			myExecutionList.push_front(game);
			game->innerActivate();
		}

		return game.get();
	};

PARABOLA_NAMESPACE_END
#endif
