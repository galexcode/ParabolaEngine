#include "ParabolaCore/Platform.h"
#ifndef MINIMAL_BUILD

#include "ParabolaCore/ScriptGame.h"
#include "ParabolaCore/Text.h"
#include "ParabolaCore/Window.h"
#include "ParabolaCore/Sprite.h"
#include "ParabolaCore/Sound.h"
#include "ParabolaCore/Kinesis.h"
#include "ParabolaCore/RocketContext.h"
#include "ParabolaCore/RocketPlugin.h"


#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
using namespace std;

PARABOLA_NAMESPACE_BEGIN


ScriptGame *game;
SceneRenderer *grenderer;

void enableRenderScript(const String &script, const String &func){
	cout<<"enabled rendering"<<endl;
	game->renderScriptEnabled = true;
	game->renderScriptName = script;
	game->renderScriptFunc = func;
}





/// Initializes the scripted game from a specific script
ScriptGame::ScriptGame() : GameCore(){
	entryPointScript = "main.as";
	game = this;
	renderScriptEnabled = false;
}

/// Called when the game is instanced, calls int main() on the starter script
void ScriptGame::onCreate(){
	renderer = createRenderer(NULL);
	grenderer = renderer.get();

	asEngine.exportStrings();
	asEngine.exportFiles();
	asEngine.exportMath();
	asEngine.exportBasicEngine();
	asEngine.exportBasicGameCore();
	asEngine.exportEvents();
	asEngine.exportBasicGraphics();
	asEngine.exportKinesis();	
	asEngine.exportContentBanks();
	asEngine.exportSoundGameCore();
	asEngine.exportRocketUi();
	asEngine.exportAnimations();
	asEngine.exportParticleSystems();

	asEngine.exportGameAs("myGame", this);

	asEngine.exportGlobalProperty("SceneRenderer Renderer", renderer.get());

	//p->drawDebug(renderer.get());
	exportScripts();

	//RocketContext *c = RocketContext::create("core_ui", Vec2i(1024,768));
	RocketPlugin::instance().loadFont("pirulen.ttf");
	myMainScript = asEngine.loadScript("main.as");
	if(myMainScript){
		myCreateFunc = myMainScript->getFunctionIdByName("void onCreate()");
		myEventFunc = myMainScript->getFunctionIdByName("void onEvent(Event@)");
		myUpdateFunc = myMainScript->getFunctionIdByName("void onUpdate(float)");
		myRenderFunc = myMainScript->getFunctionIdByName("void onRender()");
		
		myMainScript->call(myCreateFunc);
	}
	else{
		this->close();
		std::cout<<"Finished execution with errors."<<std::endl;
		system("pause");
	}
};

/// Draws the configured scene graph
/// If the direct render script is enabled, it is rendered after the other objects.
void ScriptGame::onRender(){
	if(!myMainScript)return ;

	View v;
	v.reset(sf::FloatRect(0,0,1024,768));
	renderer->setView(v);

	//renderer->draw(Text(")sf", 0,0));

	renderer->getRenderTarget()->resetGLStates();
	//renderer->draw(Text(")sf", 0,0));

	
	myMainScript->call(myRenderFunc);
	//renderer->draw(Text(")sf", 0,0));




};

/// Called when an event is fired.
void ScriptGame::onEvent(const Event &event){
	if(!myMainScript)return ;

	myMainScript->prepareMethod(myEventFunc);
	myMainScript->prepareMethodArgument(0, (void*)&const_cast<Event&>(event), ScriptArgumentTypes::Object);
	myMainScript->call();
};

/// Called when the game is updating
void ScriptGame::onUpdate(float elapsedTime){
	if(!myMainScript)return ;

	myMainScript->prepareMethod(myUpdateFunc);
	myMainScript->prepareMethodArgument(0, &elapsedTime, ScriptArgumentTypes::Float);
	myMainScript->call();
};

/// Exports all necessary functions to scripts
void ScriptGame::exportScripts(){
	asIScriptEngine *engine = asEngine.getASEngine();





	//engine->RegisterGlobalFunction("void enableRenderScript(const string &in, const string &in)", asFUNCTION(enableRenderScript), asCALL_CDECL);
	//engine->RegisterGlobalFunction("void drawText(const string &in, int, int)", asFUNCTION(drawdebug), asCALL_CDECL);
	//engine->RegisterGlobalFunction("void playSound(const string &in)", asFUNCTION(playsounddebug), asCALL_CDECL);
	//engine->RegisterGlobalFunction("bool isKeyPressed(int)", asFUNCTION(iskeydebug), asCALL_CDECL);
	//engine->RegisterGlobalFunction("void drawImage(const string &in, int , int)", asFUNCTION(drawimagedebug), asCALL_CDECL);



	/*

	*/
	//engine->RegisterObjectProperty(")
	
};

/************************************************************************/
/* Instancer                                                            */
/************************************************************************/
/// Prepares this instancer to create ScriptGame named as desired, and with entry point wherever wanted
ScriptGameInstancer::ScriptGameInstancer(String name, String entryPoint){
	myName = name;
	myEntryPoint = entryPoint;
};

/// Instances the ScriptGame
GameCore* ScriptGameInstancer::Instance(){
	ScriptGame* game = new ScriptGame();
	game->entryPointScript = myEntryPoint;
	return game;
};



PARABOLA_NAMESPACE_END

#endif