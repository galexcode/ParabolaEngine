#include "ParabolaCore/Platform.h"
#include "ParabolaCore/ScriptedGameCore.h"

#include "ParabolaCore/Text.h"
#include "ParabolaCore/Window.h"
#include "ParabolaCore/Sprite.h"
#include "ParabolaCore/Sound.h"
#include "ParabolaCore/Kinesis.h"
#include "ParabolaCore/RocketContext.h"
#include "ParabolaCore/FileInterface.h"
#include "ParabolaCore/TextStream.h"
#include "ParabolaCore/RocketPlugin.h"
#include "ParabolaCore/NStateImage.h"
#include "ParabolaCore/NStateCustom.h"

#include <iostream>
using namespace std;

PARABOLA_NAMESPACE_BEGIN

void registerScriptedGameCore(ASEngine* engine)
{
	engine->exportReferenceDataType("ScriptedGameCore");
	engine->exportReferenceDataType("ScriptEngine");

	engine->getASEngine()->RegisterObjectProperty("ScriptedGameCore", "StateStack states", asOFFSET(ScriptedGameCore, m_states));
	engine->getASEngine()->RegisterObjectProperty("ScriptedGameCore", "ScriptEngine scripts", asOFFSET(ScriptedGameCore, m_scripting));
	engine->getASEngine()->RegisterObjectProperty("ScriptedGameCore", "ContentBank content", asOFFSET(ScriptedGameCore, m_content));
};

ScriptedGameCore::ScriptedGameCore()
	:	GameCore(),
		m_requiresPreload(false)
{

};

/// Sets the preload script. This is only useful before the onCreate() method
void ScriptedGameCore::setPreloadScript(const String& script)
{
	m_preloadScriptPath = script;
};

/// Enable or disable the preload step, important in browsers to cache resources
void ScriptedGameCore::enablePreloadStep(bool enable)
{
	m_requiresPreload = enable;
};


/// Only called when the preload is finished so the game can start


/// Called when the game is instanced, calls int main() on the starter script
void ScriptedGameCore::onCreate(){

	setUpdateStep(1.f / 100.f);

	// Export base functionality
	m_scripting.exportStrings();
	m_scripting.exportBasicEngine();
	//m_scripting.exportBasicGameCore();
	m_scripting.exportGraphics();
	m_scripting.exportEvents();
	m_scripting.exportFiles();
	m_scripting.exportMath();
	registerContentBank(&m_scripting);
	registerStateStack(&m_scripting);
	registerScriptedGameCore(&m_scripting);
	registerBrowserPreloader(&m_scripting);
	registerNStateImage(&m_scripting);
	registerNStateCustom(&m_scripting);
	registerSprite(&m_scripting);
	registerView(&m_scripting);


	m_scripting.exportGlobalProperty("ScriptedGameCore game", this);


	// PreLoad the game
	ASScript* preloadScript = m_scripting.loadScript(m_fileSystemRoot + m_preloadScriptPath);
	if(preloadScript)
	{
		cout<<"=> Loaded preload script"<<endl;

		m_preloader.onRequestDownload.connect(MAKE_SLOT_LOCAL(ScriptedGameCore, doDownload));

		/// Get main script path - if the function is missing the result is empty
		m_mainScriptPath = preloadScript->fastCall<String>("string getMainScript()");
		setName(preloadScript->fastCall<String>("string getName()"));

		if(m_requiresPreload)
		{
			// Im on the browser, need to cache resources first
			preloadScript->prepareMethod("void preload(BrowserPreloader@)");
			preloadScript->prepareMethodArgument(0, &m_preloader, ScriptArgumentTypes::Object);
			preloadScript->call();

			// now launch the loading task in parallel and wait to launch the game
			m_preloader.run();

			// HACK: for now, preloading is not enabled
			m_requiresPreload = false;
		}
	}
	else
	{
		// Error - no preload script
		cout<<"=> CRITICAL: Failed to load preload script"<<endl;
	}

	/// In case we don't need preload of resources - start immediately, otherwise it will be done later
	if(!m_requiresPreload)
	{
		startupGame();
	}

	getWindow().setFramerateLimit(30);




	/*renderer = createRenderer(NULL);
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
	}*/


	m_renderer = Renderer::createAutomaticRenderer(&getWindow());
	getWindow().setFramerateLimit(60);

	circleX = 200;

	//TESTLOG("Before texture load")
//	m_texture.loadFromFile("basic.png");
	//TESTLOG("After texture load")
	//m_sprite.setTexture(m_texture);
	
	/// Scripting engine preparation
/*	m_engine.exportStrings();
	m_engine.exportEvents();
	m_engine.exportGraphics();
	m_engine.exportKinesis();

	m_engine.exportGlobalProperty("Renderer renderer", m_renderer);

	/// Prepare the main script
	m_script = m_engine.loadScript(m_startupScript);
	if(m_script){
		m_script->call(String("void onCreate()"));
	}
	*/
};

void ScriptedGameCore::startupGame()
{
	// Create the game
	m_mainScript = m_scripting.loadScript(m_fileSystemRoot + m_mainScriptPath);
	if(m_mainScript)
	{
		cout<<"=> Loaded main script"<<endl;

		m_mainScript->call(m_mainScript->getFunctionIdByName("void onCreate()"));
	}
	else
	{
		cout<<"=> CRITICAL: Failed to load main script"<<endl;
	}

};
/// Draws the configured scene graph
/// If the direct render script is enabled, it is rendered after the other objects.
void ScriptedGameCore::onRender(){
	//m_renderer->m_clearColor.r = 255;
	m_renderer->clearBuffers();
	View v;
	v.setRect(0,0,1024,768);

	/// Render the frame
	/*if(m_script){
		m_script->call(String("void onRender()"));
	}*/
	
	m_renderer->setView(v);
//	m_renderer->draw(m_sprite);
	//m_renderer->display();
	//m_renderer->drawDebugCircle(Vec2f(circleX,200), 30, Vec2f(), Color::Red);

	
	m_states.drawStates(m_renderer);

	// dirty rendering
	if(m_mainScript)
	{
		m_mainScript->prepareMethod("void onRender(Renderer@)");
		m_mainScript->prepareMethodArgument(0, m_renderer, ScriptArgumentTypes::Object);
		m_mainScript->call();
	}

	Text t;
	t.setString(String("[") + getName() + String("]") + String("Preload Script: ")  + m_preloadScriptPath);

	Text t2;
	t2.setCharacterSize(15);
	t2.setPosition(0, 50);
	String finalS = "Log: " + m_info;
	t2.setString(finalS);
	
	//m_renderer->draw(t);
	//m_renderer->draw(t2);

	getWindow().swapBuffers(); //tempo	
};

bool ScriptedGameCore::doDownload(String s, String d)
{
	// Save the file locally to the base file system root
	return onRequestDownload(s, m_fileSystemRoot + d);
};

/// Called when an event is fired.
void ScriptedGameCore::onEvent(Event &event){
	m_states.propagateEvent(event);

	// dirty rendering
	if(m_mainScript)
	{
		m_mainScript->prepareMethod("void onEvent(Event@)");
		m_mainScript->prepareMethodArgument(0, &event, ScriptArgumentTypes::Object);
		m_mainScript->call();
	}

	if(event.type == Event::MouseWheelMoved  || event.type == Event::TouchPressed){
		circleX += 20; 
	}
};

/// Called when the game is updating
void ScriptedGameCore::onUpdate(Time time){
/*	if(m_script){
		float elapsedTime = time.asSeconds();
		m_script->prepareMethod(String("void onUpdate(float)"));
		m_script->prepareMethodArgument(0, &elapsedTime, ScriptArgumentTypes::Float);
		m_script->call();
	}*/

	m_states.updateStates(time);

	// dirty rendering
	if(m_mainScript)
	{
		float elapsedTime = time.asSeconds();
		m_mainScript->prepareMethod("void onUpdate(float)");
		m_mainScript->prepareMethodArgument(0, &elapsedTime, ScriptArgumentTypes::Float);
		m_mainScript->call();
	}
};

/// Exports all necessary functions to scripts
void ScriptedGameCore::exportScripts(){
	//asIScriptEngine *engine = asEngine.getASEngine();





	//engine->RegisterGlobalFunction("void enableRenderScript(const string &in, const string &in)", asFUNCTION(enableRenderScript), asCALL_CDECL);
	//engine->RegisterGlobalFunction("void drawText(const string &in, int, int)", asFUNCTION(drawdebug), asCALL_CDECL);
	//engine->RegisterGlobalFunction("void playSound(const string &in)", asFUNCTION(playsounddebug), asCALL_CDECL);
	//engine->RegisterGlobalFunction("bool isKeyPressed(int)", asFUNCTION(iskeydebug), asCALL_CDECL);
	//engine->RegisterGlobalFunction("void drawImage(const string &in, int , int)", asFUNCTION(drawimagedebug), asCALL_CDECL);



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
	ScriptedGameCore* game = new ScriptedGameCore();
	game->entryPointScript = myEntryPoint;
	return game;
};

PARABOLA_NAMESPACE_END