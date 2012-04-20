#include "ParabolaCore/ASScript.h"
#include "ParabolaCore/ASEngine.h"

#include <iostream>
using namespace std;

PARABOLA_NAMESPACE_BEGIN


/// Creates a yet empty script, not meant to be instantiated by other than the AS Engine
ASScript::ASScript(){
	myParent = NULL;
	myModule = NULL;
	myExecutionContext = NULL;
	myEnableContextDestruction = true;
	myCallPending = false;
	myPreserveGlobals = true;
};

/// Safely destruct the script
ASScript::~ASScript(){

};

/// Prepare the context to call the function with the selected id
bool ASScript::prepareMethod(int funcid){
	if(myModule){
		myPreparedMethod = funcid;
		if(myPreparedMethod > 0){
			requestContext();
			myExecutionContext->Prepare(myPreparedMethod);
			myCallPending = true;
			return true;
		}
		else{
			cout<<"Tried to prepare an invalid function"<<endl;
		}
	}
	return false;
};

/// Prepare the context to call 
bool ASScript::prepareMethod(const String &funcName){
	if(myModule != NULL){
		myPreparedMethod = myModule->GetFunctionIdByDecl(funcName.c_str());
		if(myPreparedMethod > 0){
			requestContext();
			myExecutionContext->Prepare(myPreparedMethod);
			myCallPending = true;
			//cout<<"ASScript: prepared module"<<endl;
			return true;
		}
		else{
			cout<<"ASScript: could not prepare method: "<<funcName<<endl;
			return false;
		}
	}
	else{
		cout<<"ASScript: Could not prepare module:" <<myModule<<endl;
		return false;
	}
	
};

/// Pass an argument to the function
/// \param index must be filled with the argument index in the remote function
/// \param data must point to the address of the argument to be passed
/// \param argumentType must be a valid exportable argument type.
/// Use with care, incorrect use may lead to crashes.
void ASScript::prepareMethodArgument(int index, void* data, ScriptArgumentTypes::ArgTypes argumentType){
	if(!myExecutionContext)return;

	int result = asINVALID_ARG;
	switch(argumentType){
		case ScriptArgumentTypes::Object:
			result = myExecutionContext->SetArgObject(index, data);
		break;
		case ScriptArgumentTypes::Ptr:
			result = myExecutionContext->SetArgAddress(index, data);
		break;
		case ScriptArgumentTypes::Float:
			result = myExecutionContext->SetArgFloat(index, *((float*)data));
		break;
	}

	if(result == asINVALID_ARG){
		cout<<"ARGUMENT NUMBER INVALID"<<endl;
	}
	else if(result == asINVALID_TYPE){
		cout<<"ARGUMENT TYPE INVALID"<<endl;
	}
	else if(result == asCONTEXT_NOT_PREPARED){
		cout<<"CONTEXT NOT READY"<<endl;
	}
};

/// Give a limited time to the function execution.
void ASScript::prepareMethodTimeout(float timeoutSeconds){

};

/// Call an already prepared context
/// Returns whether the execution was successful.
/// If you want the return value, pass your object address and specify the type you want to get.
/// Be careful when using the return values, incorrect use may cause crashes.
bool ASScript::call(void *data, ScriptArgumentTypes::ArgTypes returnType){
	if(myCallPending == true && myModule != NULL){
		//requestContext();
		if(!myPreserveGlobals)
			myModule->ResetGlobalVars(myExecutionContext);

		//myExecutionContext->Prepare(myPreparedMethod);
		int r = myExecutionContext->Execute();
		if(r == asEXECUTION_FINISHED){
			myCallPending = false;
			releaseContext();
			return true;
		}
		else{
			cout<<"Failed to run function"<<endl;
		}
		releaseContext();
		return true;
	}
	else{
		cout<<"No module: "<<myModule<<endl;
		return false;
	}
};

/// Call immediately the selected function
bool ASScript::call(const String &funcName){
	prepareMethod(funcName);
	return call();
};

/// Call the selected function right away
bool ASScript::call(int funcid){
	prepareMethod(funcid);
	return call();
};

/// Get function id by its name
int ASScript::getFunctionIdByName(const String &name){
	if(myModule){
		int id;
		id = myModule->GetFunctionIdByDecl(name.c_str());
		/*if(id > 0){
			
		}*/
		return id;
	}
	else
		return -1;
};

/// Get the last return value, if the context is still alive
/// Otherwise it returns NULL.
/// Once again, be careful when casting the void* to the right object.
void* ASScript::getReturnValue(ScriptArgumentTypes::ArgTypes returnType){
	return NULL;
};

/// Request the context to be created, if not already created
void ASScript::requestContext(){
	if(!myExecutionContext){
		if(myParent){
			myExecutionContext = myParent->getASEngine()->CreateContext();
			if(myExecutionContext && myPreserveGlobals){
				//just start globals now				
				myModule->ResetGlobalVars(myExecutionContext);
			}
		}
	}
};

/// Enable/Disable the destruction of the script context.
/// When disabled, the script state is preserved between calls, like global variables.
/// Otherwise, you will be always calling a fresh script
void ASScript::enableContextDestruction(bool enabled){

};

/// Destroy the context.
void ASScript::releaseContext(){

}

/// Clears the function cache (optimization, internal use)
void ASScript::clearCache(){

};

/// Compile additional code to this script
void ASScript::compileCode(const char* code, const String &sectionName){
	if(myModule){
		//myModule->AddScriptSection("xxx", code);
		//myModule->Build();
		asIScriptFunction *func = 0;
		myModule->CompileFunction(sectionName.c_str(), code, 0, asCOMP_ADD_TO_MODULE, &func);
		if(func){
			//cout<<"will now call new function"<<endl;			
		}

		if(!myModule){
			cout<<"Module died"<<endl;
		}
	}
};

/// Get the module of this script
asIScriptModule* ASScript::getModule(){
	return myModule;
};


//////////////////////////////////////////////////////////////////////////////////////////




/// Initializes the stream on the desired script
ASBinaryStream::ASBinaryStream(const String &fileName, StreamMode::AccessModes openMode){
	stream.open(fileName, openMode);
};

/// Writes data to the stream
void ASBinaryStream::Write(const void *ptr, asUINT size){
	if(stream.valid()){
		stream.write((const char*)ptr, size);
	}
};

/// Reads data from the stream
void ASBinaryStream::Read(void *ptr, asUINT size){
	if(stream.valid()){
		if(stream.valid()){
			stream.read((char*)ptr, size);
		}
	}
};
PARABOLA_NAMESPACE_END