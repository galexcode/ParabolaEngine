#include "ParabolaCore/GameCore.h"
#include "ParabolaCore/Window.h"
#include "ParabolaCore/SceneRenderer.h"
#include "ParabolaCore/GameCoreManager.h"

PARABOLA_NAMESPACE_BEGIN

/// Creates a fresh game
/// Defaults at 60Hz update rate.
GameCore::GameCore() : fixedUpdateStep(1.f / 60.f), myParent(NULL), accumulatedTime(0.f), myWindowTitle("Default Game Name"), activeDrawing(false){
	clearColor = Color::Transparent;
	myScriptEngine.myParent = this;
};

/// Get the assigned window
/// Returns a NULL smart pointer if no window exists
linked_ptr<Window>& GameCore::getWindow(){
	return myWindow;
};

/// Sets the primary window
/// It is mandatory that a window is set for onRender to be called.
void GameCore::setWindow(linked_ptr<Window> &window_ptr){
	myWindow = window_ptr;
};

/// Get the name of this game
String& GameCore::name(){
	return myName;
};

/// Runs a script command
void GameCore::runScript(const String &command){
	myScriptEngine.run(command);
};

/// Get a reference to the script engine
ScriptEngine& GameCore::scriptEngine(){
	return myScriptEngine;
};

/// Inner update is responsible to call the regular onUpdate
/// Also handles fixed time step
void GameCore::innerUpdate(Uint32 elapsedTime){
	accumulatedTime += (float)elapsedTime / 1000.f;
	while(accumulatedTime >= fixedUpdateStep){
		onUpdate(fixedUpdateStep);
		accumulatedTime -= fixedUpdateStep;
	}
};

/// Inner render will check if there is an associated window, and only in that case it will draw into it
/// Calls SetActive() on the window, clears the buffer and displays it.
void GameCore::innerRender(){
	if(myWindow && activeDrawing){
		myWindow->SetActive(true);
		myWindow->Clear(clearColor);
		onRender();
		myWindow->Display();
	}
};

/// Inner Create is responsible to proper initialize the game if the constructor is not called
void GameCore::innerCreate(){
	fixedUpdateStep = (1.f / 60.f);
	accumulatedTime = (0.f);
	activeDrawing = (false);
	myScriptEngine.myParent = this;
	clearColor = Color::Transparent;
	onCreate();
};


/// Inner Activate will do the intern preparations for the game to be drawing
void GameCore::innerActivate(){
	activeDrawing = true;
	if(myWindow){
		myWindow->SetTitle(myWindowTitle);
	}
	onRenderFocus();
};

/// Inner Deactivate will do the preparations for the game to stop drawing
void GameCore::innerDeactivate(){
	activeDrawing = false;
	onRenderLostFocus();
};

/// Callback to draw on the window
void GameCore::onRender(){

};

/// Callback to handle the event
void GameCore::onEvent(const Event &event){

};

/// Callback to update the game state by elapsedTime seconds
void GameCore::onUpdate(float elapsedTime){

};

/// Callback when the game becomes the active drawing game
void GameCore::onRenderFocus(){

};

/// Callback when the game can't render anymore
void GameCore::onRenderLostFocus(){

};

/// Callback when the game was just instanced
void GameCore::onCreate(){

};

/// Callback when the game is about to be destroyed
void GameCore::onDestroy(){

};

/// Callback when the game enters the execution list
void GameCore::onUpdateFocus(){

};

/// Callback when the game is removed from the execution list
void GameCore::onUpdateLostFocus(){

};

/// Inner Event Check takes the associated window and gets events from it
void GameCore::innerEventCheck(){
	if(myWindow && activeDrawing){
		static Event event;
		while(myWindow->eventDispatcher().catchEvent(event, true)){
			onEvent(event);
		}
	}
};

/// Destroys this game at the end of the update
void GameCore::close(){
	if(myParent){
		myParent->destroy(this);
	}
};

/// Creates a renderer pointing at the render target passed in
/// If the target is NULL, it tries to bind the renderer to the current window
SceneRenderer* GameCore::createRenderer(RenderTarget *target){
	SceneRenderer* renderer = new SceneRenderer();

	// assign window
	if(target){
		renderer->setRenderTarget(target);
	}
	else if(getWindow()){
		renderer->setRenderTarget(getWindow().get());
	}

	return renderer;
};

/// Get the current window title
/// By default, it says "Default Game Name"
String& GameCore::windowTitle(){
	return myWindowTitle;
};

/// Set the window title
void GameCore::setWindowTitle(const String &title){
	myWindowTitle = title;
	if(activeDrawing && myWindow) myWindow->SetTitle(title);
};


/// Get a sound player
SoundPlayer& GameCore::getSoundPlayer(const String &name){
	if(mySoundPlayers.find(name) == mySoundPlayers.end()){
		mySoundPlayers[name] = new SoundPlayer(this, name);
	}	
	return *mySoundPlayers[name];
};

/// Destroys a sound player
void GameCore::removeSoundPlayer(const String &name){
	std::map<String, SoundPlayer*>::iterator it = mySoundPlayers.find(name);
	if(it != mySoundPlayers.end()){
		delete it->second;
		mySoundPlayers.erase(it);
	}
};

/// Get a content bank 
/// If the selected content bank doesn't exist, it is created.
ContentBank& GameCore::getContentBank(const String &name){
	if(myContentBanks.find(name) == myContentBanks.end()){
		myContentBanks[name] = new ContentBank(this, name);
	}	
	return *myContentBanks[name];
};

/// Destroy a content bank
void GameCore::removeContentBank(const String &name){
	std::map<String, ContentBank*>::iterator it = myContentBanks.find(name);
	if(it != myContentBanks.end()){
		delete it->second;
		myContentBanks.erase(it);
	}
};

PARABOLA_NAMESPACE_END