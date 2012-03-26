#include "ParabolaCore/ScriptGame.h"
#include "ParabolaCore/Text.h"
#include "ParabolaCore/Window.h"
#include "ParabolaCore/Sprite.h"
#include "ParabolaCore/Sound.h"

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

void drawdebug(const String &text, int x, int y){
	grenderer->draw(Text(text, x, y));
}

void drawimagedebug(const String &text, int x, int y){
	sf::Texture *t = new sf::Texture();
	t->LoadFromFile(text);

	Sprite a;
	a.SetTexture(*t);
	a.SetPosition(x, y);

	grenderer->draw(a);
}

void playsounddebug(const String &text){
	sf::SoundBuffer *buffer = new sf::SoundBuffer;
	buffer->LoadFromFile(text);

	sf::Sound *sound = new sf::Sound;
	sound->SetBuffer(*buffer);
	sound->Play();
}

bool iskeydebug(int a){
	return sf::Keyboard::IsKeyPressed((sf::Keyboard::Key)a) ;
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

	/*asEngine.RegisterString();
	asEngine.exportEngineTools();
	asEngine.exportGameTools(this);
	asEngine.exportSoundPlayer();

	exportScripts();
	asEngine.CompileScript(entryPointScript);
	asEngine.ExecuteScriptFunction(entryPointScript, "int main()");*/
};

/// Draws the configured scene graph
/// If the direct render script is enabled, it is rendered after the other objects.
void ScriptGame::onRender(){
	if(renderScriptEnabled){
		//asEngine.ExecuteScriptFunction(renderScriptName, renderScriptFunc);
	}
};

/// Called when an event is fired.
void ScriptGame::onEvent(const Event &event){
	if(event.Type == Event::KeyPressed){
		//asEngine.ExecuteScriptFunction(entryPointScript, "void onKeyPress()");
	}
};

/// Exports all necessary functions to scripts
void ScriptGame::exportScripts(){
	asIScriptEngine *engine = asEngine.getASEngine();

	engine->RegisterGlobalFunction("void enableRenderScript(const string &in, const string &in)", asFUNCTION(enableRenderScript), asCALL_CDECL);
	engine->RegisterGlobalFunction("void drawText(const string &in, int, int)", asFUNCTION(drawdebug), asCALL_CDECL);
	engine->RegisterGlobalFunction("void playSound(const string &in)", asFUNCTION(playsounddebug), asCALL_CDECL);
	engine->RegisterGlobalFunction("bool isKeyPressed(int)", asFUNCTION(iskeydebug), asCALL_CDECL);
	engine->RegisterGlobalFunction("void drawImage(const string &in, int , int)", asFUNCTION(drawimagedebug), asCALL_CDECL);



	engine->RegisterEnum("Keyboard");
	engine->RegisterEnumValue("Keyboard", "A", Keyboard::A);
	engine->RegisterEnumValue("Keyboard", "B", Keyboard::B);
	engine->RegisterEnumValue("Keyboard", "C", Keyboard::C);
	engine->RegisterEnumValue("Keyboard", "D", Keyboard::D);
	engine->RegisterEnumValue("Keyboard", "E", Keyboard::E);
	engine->RegisterEnumValue("Keyboard", "F", Keyboard::F);
	engine->RegisterEnumValue("Keyboard", "G", Keyboard::G);
	engine->RegisterEnumValue("Keyboard", "H", Keyboard::H);
	engine->RegisterEnumValue("Keyboard", "I", Keyboard::I);
	engine->RegisterEnumValue("Keyboard", "J", Keyboard::J);
	engine->RegisterEnumValue("Keyboard", "K", Keyboard::K);
	engine->RegisterEnumValue("Keyboard", "L", Keyboard::L);
	engine->RegisterEnumValue("Keyboard", "M", Keyboard::M);
	engine->RegisterEnumValue("Keyboard", "N", Keyboard::N);
	engine->RegisterEnumValue("Keyboard", "O", Keyboard::O);
	engine->RegisterEnumValue("Keyboard", "P", Keyboard::P);
	engine->RegisterEnumValue("Keyboard", "Q", Keyboard::Q);
	engine->RegisterEnumValue("Keyboard", "R", Keyboard::R);
	engine->RegisterEnumValue("Keyboard", "S", Keyboard::S);
	engine->RegisterEnumValue("Keyboard", "T", Keyboard::T);
	engine->RegisterEnumValue("Keyboard", "U", Keyboard::U);
	engine->RegisterEnumValue("Keyboard", "V", Keyboard::V);
	engine->RegisterEnumValue("Keyboard", "W", Keyboard::W);
	engine->RegisterEnumValue("Keyboard", "X", Keyboard::X);
	engine->RegisterEnumValue("Keyboard", "Y", Keyboard::Y);
	engine->RegisterEnumValue("Keyboard", "Z", Keyboard::Z);


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