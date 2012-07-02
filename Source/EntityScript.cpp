#ifndef MINIMAL_BUILD

#include "ParabolaCore/EntityScript.h"
#include "ParabolaCore/ASEngine.h"

#include <iostream>
using namespace std;

PARABOLA_NAMESPACE_BEGIN

/// Creates the entity script
EntityScript::EntityScript(EntityManager *parent) : Entity(parent){
	myScriptEngine = NULL;
};

/// Called when the entity is attached
void EntityScript::onAttach(){	
	Entity::onAttach();
	if(myScriptEngine){
		cout<<"Calling attach function on: "<<name()<<endl;
		//myScriptEngine->ExecuteScriptFunction(name() + ".as" , "void onAttach()");
	}

	asDWORD a;
	
};


PARABOLA_NAMESPACE_END

#endif