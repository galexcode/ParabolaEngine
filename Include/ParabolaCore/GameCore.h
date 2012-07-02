#ifndef PARABOLA_GAMECORE_H
#define PARABOLA_GAMECORE_H

#include "Platform.h"
#include "Clock.h"
#include "Logger.h"
#include "Renderer.h"
#include "Window.h"
#include "InputEvent.h"
#include "StringList.h"
#include "Application.h"
#include "StateMachine.h"

PARABOLA_NAMESPACE_BEGIN
class GameCoreManager;
/**
	\ingroup Core
	\class GameCore
	\brief Base class for all games and applications.
	
*/
class PARABOLA_API GameCore{
public:
	/// Construct the game, its mandatory to call this base constructor when implementing GameCore
	GameCore();

	/// Get the window/screen handler
	Window& getWindow();

	/// Shutdown this game immediately
	void close();

	/// Set the fixed update step, or, the amount of time, in seconds, that will take between each update.
	void setUpdateStep(float step);
	
protected:
	/// Callback for updating the game
	virtual void onUpdate(Time time);

	/// Callback for rendering a frame
	virtual void onRender();

	/// Callback when starting to execute the game
	virtual void onCreate();

	/// Callback when an event happens
	virtual void onEvent(InputEvent &event);
	
private:
	friend class GameCoreManager;

	/// Inner update of the game
	/// Will handle fixed update steps
	/// Callbacks to onUpdate(Time time) when appropriate
	void innerUpdate(Time time);

	/// Inner render of the game
	/// Callbacks to onRender()
	void innerRender();

	/// Fixed update step
	float m_updateStep;
	float m_stackedTime;
	
	
	
	/*
	/// Get the assigned window
	/// Returns a NULL smart pointer if no window exists
	Window* getWindow();

	/// Sets the primary window
	/// It is mandatory that a window is set for onRender to be called.
	void setWindow(Window* window);

	/// Get the name of this game
	String& name();

	/// Get the current window title
	/// By default, it says "Default Game Name"
	String& windowTitle();

	/// Set the window title
	void setWindowTitle(const String &title);
	
	/// Destroys this game at the end of the update
	void close();

	/// Runs a script command
	void runScript(const String &command);

	/// Get a reference to the script engine
	ScriptEngine& scriptEngine();


	/// Creates a renderer pointing at the render target passed in
	/// If the target is NULL, it tries to bind the renderer to the current window
	SceneRenderer* createRenderer(RenderTarget *target);
	
	/// Creates a sound player or returns if already exists
	/// If a sound player with that name already exists,
	/// it is returned instead of creating a new one
	SoundPlayer& getSoundPlayer(const String &name);

	/// Destroys a sound player
	void removeSoundPlayer(const String &name);

	/// Get a content bank 
	/// If the selected content bank doesn't exist, it is created.
	ContentBank& getContentBank(const String &name);

	/// Destroy a content bank
	void removeContentBank(const String &name);

protected:
	/// Callback when the game was just instanced
	virtual void onCreate();

	/// Callback when the game is about to be destroyed
	virtual void onDestroy();

	/// Callback when the game enters the execution list
	virtual void onUpdateFocus();

	/// Callback when the game is removed from the execution list
	virtual void onUpdateLostFocus();

	/// Callback when the game becomes the active drawing game
	virtual void onRenderFocus();

	/// Callback when the game can't render anymore
	virtual void onRenderLostFocus();

	/// Callback to draw on the window
	virtual void onRender();

	/// Callback to handle the event
	virtual void onEvent(const Event &event);

	/// Callback to update the game state by elapsedTime seconds
	virtual void onUpdate(float elapsedTime);

	/// Protected constructor, cannot instance GameCore
	GameCore();
	
private:
	friend class GameCoreManager;
	GameCoreManager *myParent;

	/// Inner Create is responsible to proper initialize the game if the constructor is not called
	void innerCreate();

	/// Inner update is responsible to call the regular onUpdate
	/// Also handles fixed time step
	void innerUpdate(Uint32 elapsedTime);

	/// Inner render will check if there is an associated window, and only in that case it will draw into it
	/// Calls SetActive() on the window, clears the buffer and displays it.
	void innerRender();

	/// Inner Event Check takes the associated window and gets events from it
	void innerEventCheck();

	/// Inner Activate will do the intern preparations for the game to be drawing
	void innerActivate();

	/// Inner Deactivate will do the preparations for the game to stop drawing
	void innerDeactivate();

	/// Fixed time step - 0 for no fixed time step
	float fixedUpdateStep, accumulatedTime;
	/// Window title, will be automatically activated
	String myWindowTitle;
	/// Name of the game instance
	String myName;
	/// Screen clearing color
	Color clearColor;
	/// Localization Settings
	String mySystemLocale, mySelectedLocale;
	/// Current drawing window
	/// If there is an engine window, it is assigned here by default
	Window* myWindow;
	/// True if this game is allowed to render
	bool activeDrawing;
	/// Each game owns a intern script engine
	ScriptEngine myScriptEngine;

	/// Sound Players
	std::map<String, SoundPlayer*> mySoundPlayers;

	/// Content banks
	std::map<String, ContentBank*> myContentBanks;

	/// Scripting interface functions - all defined in AngelScriptInterfaces.cpp
	friend class ASEngine;

	void dummy();*/
};

PARABOLA_NAMESPACE_END
#endif