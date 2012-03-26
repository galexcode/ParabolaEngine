#include "ParabolaCore/Engine.h"
#include "ParabolaCore/ScriptGame.h"

PARABOLA_NAMESPACE_BEGIN
/************************************************************************/
/* Engine                                                               */
/************************************************************************/
int Engine::as_gameCount(){
	return gameManager().aliveGameCount();
}

String Engine::as_gameNameAt(int i){
	int j = 0;	
	std::list<linked_ptr<GameCore> >::iterator it = gameManager().myGameList.begin();

	while(j < i){
		if(it != gameManager().myGameList.end())
			it++;
		else
			return "NULL"; //because the index was invalid
	}

	return (*it).get()->name();
}

void Engine::as_createScriptGame(const String &name, const String &entry){
	gameManager().registerInstancer(new ScriptGameInstancer(name, entry), name );
	gameManager().launchFromInstancer(name);
};

void Engine::dummy(){

};

/************************************************************************/
/* GameCore                                                             */
/************************************************************************/

void GameCore::dummy(){

};

PARABOLA_NAMESPACE_END