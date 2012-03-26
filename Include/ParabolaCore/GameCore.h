#ifndef PARABOLA_GAMECORE_H
#define PARABOLA_GAMECORE_H

#include "Platform.h"
#include "LinkedPointer.h"
#include "Strings.h"
#include "ScriptEngine.h"
#include "SoundPlayer.h"
#include "ContentBank.h"
#include "Window.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

PARABOLA_NAMESPACE_BEGIN
typedef sf::Color Color;
typedef sf::RenderTarget RenderTarget;
class GameCoreManager;
class Event;
class SceneRenderer;
class ASEngine;

/**
	\ingroup Core
	\class GameCore
	\brief Represents a game. All games shall inherit this base class.

	The GameCore class also works as a factory,
	or a repository of objects and actually handles their destruction if so is needed.

	Implement the virtual methods to make your game logic.
*/
class PARABOLA_API GameCore{
public:
	/// Get the assigned window
	/// Returns a NULL smart pointer if no window exists
	linked_ptr<Window>& getWindow();

	/// Sets the primary window
	/// It is mandatory that a window is set for onRender to be called.
	void setWindow(linked_ptr<Window> &window_ptr);

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
	linked_ptr<Window> myWindow;
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

	void dummy();
};

PARABOLA_NAMESPACE_END
#endif