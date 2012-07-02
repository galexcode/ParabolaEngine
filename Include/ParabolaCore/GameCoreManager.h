#ifndef PARABOLA_GAMECOREMANAGER_H
#define PARABOLA_GAMECOREMANAGER_H

#include "Platform.h"
#include "GameCore.h"
#include "InputEvent.h"
#include <vector>

PARABOLA_NAMESPACE_BEGIN

/**
	\ingroup Core
	\class GameCoreManager
	\brief Manager for multi tasking of games

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
	/// Construct the default game core manager settings
	GameCoreManager();

	/// Push an input event into the games
	void pushInputEvent(InputEvent &event);

	/// Update the state of all games applicable
	void update(Time time);

	/// Simply adds an instance of a game to execution
	/// It will delete the game when appropriate
	void addGameForExecution(GameCore* instancedGame);

private:
	/// All games currently running, not necessarily updating or rendering
	std::vector<GameCore*> myExecutionList;

	/// Variable decides whether a game can be updated without being the active one
	bool allowBackgroundUpdates;
};

PARABOLA_NAMESPACE_END
#endif
