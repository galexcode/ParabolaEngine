#include "ParabolaCore/GameCoreManager.h"
//#include "ParabolaCore/Window.h"
#include "ParabolaCore/Engine.h"

#include <iostream>

PARABOLA_NAMESPACE_BEGIN


/// Construct the default game core manager settings
GameCoreManager::GameCoreManager(Engine* parent) : m_creator(parent){
	allowBackgroundUpdates = false;
};

/// Push an input event into the games
void GameCoreManager::pushInputEvent(Event &event){
	for(unsigned int i = 0; i < myExecutionList.size(); i++){
		myExecutionList[i]->onEvent(event);
	}
};

/// Update the state of all games applicable
void GameCoreManager::update(Time time){
	for(unsigned int i = 0; i < myExecutionList.size(); i++){
		myExecutionList[i]->innerUpdate(time);
		myExecutionList[i]->innerRender();
	}
};

/// Simply adds an instance of a game to execution
/// It will delete the game when appropriate
void GameCoreManager::addGameForExecution(GameCore* instancedGame){
	if(instancedGame){
		myExecutionList.push_back(instancedGame); /// Since this game is on the top now	
		instancedGame->m_creator = m_creator;
		instancedGame->onCreate();
		onActiveGameChanged();
	}
};

/// Called only when the top of the execution stack has changed
void GameCoreManager::onActiveGameChanged(){
	m_creator->getWindow().setTitle(myExecutionList.back()->getWindowTitle());
};

	/*
std::vector<GameCore*> eraseList;

/// Private constructor - can only be instanced by the engine
GameCoreManager::GameCoreManager(Engine *parent) : myParent(parent){
	
};

/// Safely destroys the game manager
GameCoreManager::~GameCoreManager(){
	myParent = NULL;
};

/// Get the number of alive games, the ones instantiated
int GameCoreManager::aliveGameCount(){
	return (int)myGameList.size();
};

/// Pushes the event to the active drawing game
void GameCoreManager::pushEvent(const Event &event){
	if(myExecutionList.size() > 0){
		myExecutionList.front()->onEvent(event);
	}
};

/// Normally called when the engine has no window, therefore the game has to fetch events itself
void GameCoreManager::checkEvents(){
	if(myExecutionList.size() > 0){
		myExecutionList.front()->innerEventCheck();
	}
};

/// Make the games update
void GameCoreManager::update(){
	Uint32 elapsed = clock.getElapsedTime().asMilliseconds(); // elapsed time since last frame

	std::list<linked_ptr<GameCore> >::iterator it;
	for(it = myExecutionList.begin(); it != myExecutionList.end(); it++){
		(*it)->innerUpdate(elapsed);
	}
	
	//eliminate
	for(unsigned int i = 0; i < eraseList.size(); i++){
		for(std::list<linked_ptr<GameCore> >::iterator it = myExecutionList.begin(); it != myExecutionList.end(); it++){
			if((*it).get() == eraseList[i]){
				it = myExecutionList.erase(it);
				break;
			}
		}
		for(std::list<linked_ptr<GameCore> >::iterator it = myGameList.begin(); it != myGameList.end(); it++){
			if((*it).get() == eraseList[i]){
				(*it)->onDestroy();
				(*it).destroy();
				it = myGameList.erase(it);
				break;
			}
		}

		if(myExecutionList.empty()){
			Engine::instance()->close();
			break;
		}
	}
	eraseList.clear();

	clock.restart();
};

/// Make the active drawing game render itself
void GameCoreManager::draw(){
	if(myExecutionList.size() > 0){
		myExecutionList.front()->innerRender();
	}
};

/// Schedules the destruction of the game for when the update step ends.
void GameCoreManager::destroy(GameCore *game){
	eraseList.push_back(game);
};

/// Registers an instancer so it can launch games later 
/// using for example launchFromInstancer(name) by passing the same name used here
/// In a home application, you would see this name as the icon label,
/// and when clicking it, it would launch your game, the way you want to.
String GameCoreManager::registerInstancer(GameInstancerInterface *instancer, const String &name){
	myGameInstancers[name] = instancer;
	return name;
};

/// Searches for the desired instancer and launches the game
GameCore* GameCoreManager::launchFromInstancer(const String &name){
	std::map<String, GameInstancerInterface*>::iterator it = myGameInstancers.find(name);

	if(it != myGameInstancers.end()){
		linked_ptr<GameCore> game;
		game = reinterpret_cast<GameCore*>(it->second->Instance());
		game->myName = name;
		game->myParent = this;
		game->setWindow(myParent->getWindow());
		myGameList.push_back(game);

		game->innerCreate();

		myExecutionList.push_front(game);
		game->innerActivate();

		return game.get();

	}
	else
		return NULL;
};
*/
PARABOLA_NAMESPACE_END
