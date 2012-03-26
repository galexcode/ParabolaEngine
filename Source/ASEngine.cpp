#include "ParabolaCore/ASEngine.h"
#include "ParabolaCore/GameCore.h"
#include "ParabolaCore/Engine.h"
#include "ParabolaCore/SoundPlayer.h"

#include "AS/scriptbuilder.h"
#include "AS/scriptstdstring.h"
#include "AS/scriptarray.h"
#include "AS/scriptany.h"
#include "AS/scriptfile.h"
#include "AS/scriptmath.h"

#include <iostream>

PARABOLA_NAMESPACE_BEGIN

void scriptstdprint(const std::string &in){
	std::cout<<in;
}

void ASMessageCallback(const asSMessageInfo *msg, void *param){
		if(!msg)return;
		const char *type = "ERR ";
		if( msg->type == asMSGTYPE_WARNING ) 
			type = "WARN";
		else if( msg->type == asMSGTYPE_INFORMATION ) 
			type = "INFO";

		printf("%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type, msg->message);

};

ASEngine::ASEngine(){
		asEngine = asCreateScriptEngine(ANGELSCRIPT_VERSION);
		asEngine->SetMessageCallback(asFUNCTION(ASMessageCallback), 0, asCALL_CDECL);
		asEngine->SetEngineProperty(asEP_INIT_GLOBAL_VARS_AFTER_BUILD, false);

		gameCoreBasic = false;
		gameCoreAdvanced = false;
		gameCoreSound = false;
		gameCoreExported = false;
		scriptBasic = false;
		engineBasic = false;
};

/// Ensures proper destruction of the engine
ASEngine::~ASEngine(){
	asEngine->Release();
};

/// Returns the pointer to the internal angel script engine
/// Possible use could be to export functions.
asIScriptEngine* ASEngine::getASEngine(){
	return asEngine;
};



/// Destroys a script from the engine
void ASEngine::unloadScript(const String &name){

};

/// Loads a script into the engine
/// Any functionality the script requires must be exported before loading it
/// \param name The name of the script to load, relative to the executable directory, or the added directories
/// \param alias An override for the name, as the search keyword of this script. Ignored if empty.
/// \param isByteCode When true, the script is assumed to be already compiled, and is loaded as bytecode. 
/// \return ASScript structure to interact with the loaded script, NULL if failed to load.
/// \note The name specified or the alias may be already in use. In that case, a new name is generated and can be queried later.
/////////////////////////////////////////////////////////////////////////////////////////////////
ASScript* ASEngine::loadScript(const String &name, const String &alias, bool isByteCode){
	ASScript* asScript = NULL;	

	CScriptBuilder Builder;
	int r;
	r = Builder.StartNewModule(asEngine, name.c_str());
	if(r<0){
		//pLogger::Log(LogLevel::Critical, "Could not create a new Script Module.", "[ScriptEngine]");
		return NULL;
	}

	if(isByteCode){
		
	}
	else{
		r = Builder.AddSectionFromFile(name.c_str());
		if(r<0){
			//pLogger::Log(LogLevel::Critical, "Could not stream file data into the Script Module.", "[ScriptEngine]");
			return false;
		}

		r = Builder.BuildModule();
		if(r<0){
			//pLogger::Log(LogLevel::Critical, "Could not compile the script file.", "[ScriptEngine]");
			return false;
		}

		asScript = new ASScript();
		asScript->myParent = this;
		asScript->myModule = asEngine->GetModule(name.c_str());
	}

	return asScript;
};

/// Loads a precompiled script into the engine
/// Before loading the script, ensure the functionality it uses is exported.
/// \param name The name of the script to load, relative to the executable directory, or the added directories
/// \param alias An override for the name, as the search keyword of this script. Ignored if empty.
/// \return ASScript structure to interact with the loaded script, NULL if failed to load.
ASScript* ASEngine::loadCompiledScript(const String &name, const String &alias){
	ASScript* asScript = NULL;

	//if(myLoade)

	return asScript;
};

/// Get the list of paths for searching scripts
const StringList& ASEngine::getSearchPaths(){
	return mySearchPaths;
};

/// Add a new search path
void ASEngine::addSearchPath(const String &path){
	mySearchPaths.append(path);
};

/// Add a few search paths
void ASEngine::addSearchPaths(const StringList &paths){
	mySearchPaths.append(paths);
};

/// Removes a search path
void ASEngine::removeSearchPath(const String &name){
	mySearchPaths.erase(std::find(mySearchPaths.begin(), mySearchPaths.end(), name) );
};

/// Remove all search paths
void ASEngine::clearSearchPaths(){
	mySearchPaths.clear();
};

/// Reset will reinitialize everything.
void ASEngine::reset(){

};

/// Find your script structure by its name/alias
/// NULL is returned on failure to find it.
/// Do not DELETE this yourself, rather call the appropriate function.
ASScript* ASEngine::findScript(const String &name){
	return NULL;
};


/// Wrapper for exporting reference only data types, that means they cannot be instantiated in scripts.
/// name will be the name to be known from scripts
/// typeSize is just sizeof(MyClassType)
/// dummyMethod must contain the name of a useless method from your class, because of an internal detail. 
/// Such as "dummy", if you have a function void dummy() that does nothing .
int ASEngine::exportReferenceDataType(const String &name, size_t typeSize, const String &dummyMethod){
	return 0;
};

/// Wrapper for exporting global properties
/// dataType could be "const int" or "MyClass", or anything valid for the script context
/// varName could be anything under the common constraints of variable naming.
int ASEngine::exportGlobalProperty(const String &dataType, const String &varName){
	return 0;
};

/// Compiles all scripts in the search directories
/// All files found in the directories ending with .sourceextension will be compiled into byte code.
/// \param destExtension Those files will be output with the same name.destExtension
/// \param destDirectory Where to output the file, relative to where the file is. Useful to separate between 32 bit and 64 bit versions
bool ASEngine::compileAllScripts(const String &sourceExtension, const String &destExtension, const String &destDirectory, const String &prefix){

	return false;
};

/// Compiles a script to a destination file.
bool ASEngine::compileScript(const String &scriptName,  const String &destName){
	return false;
};

/// Shortcut to call methods on compiled scripts
/// usage: callScriptMethod("myscript.as", "void main()");
/// And there it goes.
bool ASEngine::callScriptMethod(const String &scriptName, const String &method){
	asIScriptModule *module = asEngine->GetModule(scriptName.c_str());
	if(!module) return false; //not available

	bool Result = true;
	int r;
	int mainId;

	asIScriptContext *context = asEngine->CreateContext();

	r = module->ResetGlobalVars(context);
	if(r < 0) return false;

	mainId = module->GetFunctionIdByDecl(method.c_str());
	if(mainId < 0){
		std::cout<<"Error: Specified function was not found."<<std::endl;
		return false;
	}

	context->Prepare(mainId);
	r = context->Execute();
	if(r == asEXECUTION_FINISHED){
		//std::cout<<"Ran sucessfully the script."<<std::endl;
	}
	else{
		//something is wrong
		switch(r){
		case asEXECUTION_ERROR: 
			break;

		}
	}

	context->Release();

	return Result;

	return true;
};

////////////////////////////////////////////////////////////////////////// Exportation

/// Forces the basic game core functionality to be exported and sets game a global property, known by varName.
/// You must ensure that the GameCore instance is valid while this engine is running.
/// That shouldn't be a problem if your game owns locally the engine.
bool ASEngine::exportGameAs(const String &varName, GameCore* game){
	if(!gameCoreBasic) return false;
	asEngine->RegisterGlobalProperty(String("GameCore " + varName).c_str(), game);
	return true;
};

/// Exports the most basic functionality of a game, GameCore is always known by reference, and can't be instanced from scripts.
/// Only things like the name() function and other simple things are exported here.
bool ASEngine::exportBasicGameCore(){
	if(gameCoreBasic)return true;
	asEngine->RegisterObjectType("GameCore", sizeof(GameCore), asOBJ_REF);

	int r;
	r = asEngine->RegisterObjectBehaviour("GameCore", asBEHAVE_ADDREF, "void f()", asMETHOD(GameCore,dummy), asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectBehaviour("GameCore", asBEHAVE_RELEASE, "void f()", asMETHOD(GameCore,dummy), asCALL_THISCALL); if(r < 0)printf("r %d", r);

	r = asEngine->RegisterObjectMethod("GameCore", "string& name()", asMETHOD(GameCore, name) , asCALL_THISCALL);if(r < 0)printf("r %d", r);
	//r = asEngine->RegisterObjectMethod("GameCore", "void runEngineScript(const string& in)", asMETHOD(GameCore, runScript) , asCALL_THISCALL);if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("GameCore", "void close()", asMETHOD(GameCore, close) , asCALL_THISCALL);if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("GameCore", "string& windowTitle()", asMETHOD(GameCore, windowTitle) , asCALL_THISCALL);if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("GameCore", "void setWindowTitle(const string& in)", asMETHOD(GameCore, setWindowTitle) , asCALL_THISCALL);if(r < 0)printf("r %d", r);

	gameCoreBasic = true;
	return true;
};

/// Exports audio support from scripts. Only works if a game is known.
bool ASEngine::exportSoundGameCore(){
	if(!gameCoreBasic)return false;

	asEngine->RegisterObjectType("SoundPlayer", sizeof(SoundPlayer), asOBJ_REF);
	int r;
	r = asEngine->RegisterObjectBehaviour("SoundPlayer", asBEHAVE_ADDREF, "void f()", asMETHOD(SoundPlayer,dummy), asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectBehaviour("SoundPlayer", asBEHAVE_RELEASE, "void f()", asMETHOD(SoundPlayer,dummy), asCALL_THISCALL); if(r < 0)printf("r %d", r);

	r = asEngine->RegisterObjectMethod("GameCore", "SoundPlayer& getSoundPlayer(const string &in)", asMETHOD(GameCore, getSoundPlayer) , asCALL_THISCALL);if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("GameCore", "void removeSoundPlayer(const string &in)", asMETHOD(GameCore, removeSoundPlayer) , asCALL_THISCALL);if(r < 0)printf("r %d", r);


	//r = asEngine->RegisterObjectMethod("SoundPlayer", "void say(const string &in)", asMETHOD(SoundPlayer, say) , asCALL_THISCALL);if(r < 0)printf("r %d", r);

	gameCoreSound = true;
	return true;
};

/// Exports common script utilities
bool ASEngine::exportBasicScriptInformation(){
	return false;
};

/// Exports basic functionality and access to the global engine
/// By default, it will be known as Engine, change at will.
bool ASEngine::exportBasicEngine(const String &varName){
	if(engineBasic)return true;

	asEngine->RegisterObjectType("EngineSDK", sizeof(Engine), asOBJ_REF);

	int r;
	r = asEngine->RegisterObjectBehaviour("EngineSDK", asBEHAVE_ADDREF, "void f()", asMETHOD(Engine,dummy), asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectBehaviour("EngineSDK", asBEHAVE_RELEASE, "void f()", asMETHOD(Engine,dummy), asCALL_THISCALL); if(r < 0)printf("r %d", r);

	r = asEngine->RegisterObjectMethod("EngineSDK", "string getGameName(int)", asMETHOD(Engine, as_gameNameAt) , asCALL_THISCALL);if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("EngineSDK", "int gameCount()", asMETHOD(Engine, as_gameCount) , asCALL_THISCALL);if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("EngineSDK", "void loadGame(const string &in, const string &in)", asMETHOD(Engine, as_createScriptGame) , asCALL_THISCALL);if(r < 0)printf("r %d", r);

	asEngine->RegisterGlobalProperty(String(String("EngineSDK ") + varName).c_str(), Engine::instance());

	engineBasic = true;
	return engineBasic;
};

/// Exports string functionality
bool ASEngine::exportStrings(){
	if(!asEngine)return false;

	RegisterStdString(asEngine);
	RegisterScriptArray(asEngine, false);
	RegisterStdStringUtils(asEngine);

	int r;
	r = asEngine->RegisterGlobalFunction("void print(const string &in)", asFUNCTION(scriptstdprint), asCALL_CDECL);
	if(r < 0){
		//pLogger::Log(LogLevel::Critical, "Failed to export a function.");
	}

	return true;
};

/// Exports file support
bool ASEngine::exportFiles(){
	return true;
};

/// Exports math support
bool ASEngine::exportMath(){
	return true;
};
	
PARABOLA_NAMESPACE_END