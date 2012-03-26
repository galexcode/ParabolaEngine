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
};

/// Safely destruct the script
ASScript::~ASScript(){

};

/// Prepare the context to call the function with the selected id
bool ASScript::prepareMethod(int funcid){
	return false;
};

/// Prepare the context to call 
bool ASScript::prepareMethod(const String &funcName){
	if(myModule){
		myPreparedMethod = myModule->GetFunctionIdByDecl(funcName.c_str());
		if(myPreparedMethod > 0){
			requestContext();
			myExecutionContext->Prepare(myPreparedMethod);
			myCallPending = true;
			return true;
		}
	}
	return false;
};

/// Pass an argument to the function
/// \param index must be filled with the argument index in the remote function
/// \param data must point to the address of the argument to be passed
/// \param argumentType must be a valid exportable argument type.
/// Use with care, incorrect use may lead to crashes.
void ASScript::prepareMethodArgument(int index, void* data, ScriptArgumentTypes::ArgTypes argumentType){
	int result;
	switch(argumentType){
		case ScriptArgumentTypes::Object:
			result = myExecutionContext->SetArgObject(index, data);
		break;
		case ScriptArgumentTypes::Ptr:
			result = myExecutionContext->SetArgAddress(index, data);
		break;
	}

	if(result == asINVALID_ARG){
		cout<<"ARGUMENT NUMBER INVALID"<<endl;
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
	if(myCallPending && myModule){
		//requestContext();
		myModule->ResetGlobalVars(myExecutionContext);
		//myExecutionContext->Prepare(myPreparedMethod);
		int r = myExecutionContext->Execute();
		if(r == asEXECUTION_FINISHED){
			myCallPending = false;
			releaseContext();
			return true;
		}
		releaseContext();
		return true;
	}
	else
		return false;
};

/// Call immediately the selected function
bool ASScript::call(const String &funcName){
	return false;

};

/// Call the selected function right away
bool ASScript::call(int funcid){
	return false;

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