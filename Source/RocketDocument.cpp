#include "ParabolaCore/RocketDocument.h"
#include "ParabolaCore/RocketContext.h"

PARABOLA_NAMESPACE_BEGIN

RocketDocument::RocketDocument(Rocket::Core::String tagName) : Rocket::Core::ElementDocument(tagName){
		myMainScript = NULL;
		scriptCallStack = 0;
		 
		myScriptEngine.exportStrings();
		myScriptEngine.exportBasicGraphics();
		myScriptEngine.exportBasicScriptInformation();
		myScriptEngine.exportRocketUi();
		myScriptEngine.exportAnimations();
		myScriptEngine.exportRocketScripting(this);
		 
		/*
		
		myScriptEngine.exportFiles();
		myScriptEngine.exportMath();
		myScriptEngine.exportBasicEngine();
		myScriptEngine.exportBasicGameCore();
		myScriptEngine.exportEvents();
		myScriptEngine.exportBasicGraphics();
		myScriptEngine.exportKinesis();	
		myScriptEngine.exportContentBanks();
		myScriptEngine.exportSoundGameCore();
		
		*/

		myScriptEngine.exportGlobalProperty("AnimationFactory animator", &myAnimationFactory);
}

void RocketDocument::processInlineEvent(const String& eventValue, Rocket::Core::Event& event){
	if(myMainScript){
		String funcPrototype = "void eventHandlerCallStack" + String::number(scriptCallStack++) + "(RocketEvent@ event)";

		String resultFunction = funcPrototype + "{\n";
		resultFunction += eventValue + " \n}";
		myMainScript->compileCode(resultFunction.c_str(), funcPrototype);
		//cout<<"Compiled:"<<resultFunction<<endl;
		myMainScript->prepareMethod(funcPrototype);
		myMainScript->prepareMethodArgument(0, &event, ScriptArgumentTypes::Object);
		if(myMainScript->call()){
			//cout<<"Called function"<<endl;
			myMainScript->getModule()->RemoveFunction(myMainScript->getModule()->GetFunctionByDecl(funcPrototype));
		}

		scriptCallStack--;
	}	
}

PARABOLA_NAMESPACE_END
