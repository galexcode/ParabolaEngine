#include "ParabolaCore/Engine.h"
#include "ParabolaCore/ScriptGame.h"
#include "ParabolaCore/ASEngine.h"
#include "ParabolaCore/AnimationFactory.h"
#include "ParabolaCore/AnimationPosition.h"

PARABOLA_NAMESPACE_BEGIN

AnimationFactory& AnimationFactoryFactory(){
	return *new AnimationFactory();
}

AnimationPosition& AnimationPositionFactory(){
	return *new AnimationPosition();
}



/// Exports animation support
bool ASEngine::exportAnimations(){

	asEngine->RegisterObjectType("AnimationPosition", sizeof(AnimationPosition), asOBJ_REF);

	asEngine->RegisterObjectBehaviour("AnimationPosition", asBEHAVE_FACTORY, "AnimationPosition@ f()", asFUNCTION(AnimationPositionFactory), asCALL_CDECL);
	asEngine->RegisterObjectBehaviour("AnimationPosition", asBEHAVE_ADDREF, "void f()", asMETHOD(RefCountable, addReference), asCALL_THISCALL);
	asEngine->RegisterObjectBehaviour("AnimationPosition", asBEHAVE_RELEASE, "void f()", asMETHOD(RefCountable, removeReference), asCALL_THISCALL);

	asEngine->RegisterObjectMethod("AnimationPosition", "void setDestination(float,float)", asMETHOD(AnimationPosition, setDestination), asCALL_THISCALL);
	asEngine->RegisterObjectMethod("AnimationPosition", "void setDuration(float)", asMETHOD(AnimationPosition, setDuration), asCALL_THISCALL);




	asEngine->RegisterObjectType("AnimationFactory", sizeof(AnimationFactory), asOBJ_REF);

	asEngine->RegisterObjectBehaviour("AnimationFactory", asBEHAVE_FACTORY, "AnimationFactory@ f()", asFUNCTION(AnimationFactoryFactory), asCALL_CDECL);
	asEngine->RegisterObjectBehaviour("AnimationFactory", asBEHAVE_ADDREF, "void f()", asMETHOD(RefCountable, addReference), asCALL_THISCALL);
	asEngine->RegisterObjectBehaviour("AnimationFactory", asBEHAVE_RELEASE, "void f()", asMETHOD(RefCountable, removeReference), asCALL_THISCALL);

	asEngine->RegisterObjectMethod("AnimationFactory", "void addAnimation(AnimationPosition& inout)", asMETHOD(AnimationFactory, addAnimation), asCALL_THISCALL);
	asEngine->RegisterObjectMethod("AnimationFactory", "void moveElementTo(RocketElement@,float,float,float)", asMETHOD(AnimationFactory, moveRocketElementTo), asCALL_THISCALL);
	asEngine->RegisterObjectMethod("AnimationFactory", "void resizeElementTo(RocketElement@,float,float,float)", asMETHOD(AnimationFactory, resizeRocketElementTo), asCALL_THISCALL);
	asEngine->RegisterObjectMethod("AnimationFactory", "void addElementContent(RocketElement@,const string &in, float)", asMETHOD(AnimationFactory, addRocketElementContent), asCALL_THISCALL);
	
	return true;
};

















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