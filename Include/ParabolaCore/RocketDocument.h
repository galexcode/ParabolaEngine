#ifndef PARABOLA_ROCKETDOCUMENT_H
#define PARABOLA_ROCKETDOCUMENT_H

#include "Platform.h"
#include "ASEngine.h"
#include "Rocket/Core.h"
#include "AnimationFactory.h"

PARABOLA_NAMESPACE_BEGIN

class RocketElement : public Rocket::Core::Element{
public:
	RocketElement(Rocket::Core::String tag) : Rocket::Core::Element(tag){

	}

	String getInnerRML(){
		return String(GetInnerRML().CString());
	}

	void setProperty(const String &propertyName, const String& propertyValue){
		Rocket::Core::Element::SetProperty(propertyName.c_str(), propertyValue.c_str());
	}

};

class RocketDocument : public Rocket::Core::ElementDocument{
public:
	/// Construct the document
	RocketDocument(Rocket::Core::String tagName);

	void say(const String &sayss){
		//cout<<"SAY HI:"<<endl;
	};

	Rocket::Core::Element* getElementById(const String &id){
		return Rocket::Core::Element::GetElementById(id.c_str());
	}

	// Load a script into the document.
	// @param[in] stream Stream of code to process.
	// @param[in] source_name Name of the the script the source comes from, useful for debug information.
	virtual void LoadScript(Rocket::Core::Stream* stream, const Rocket::Core::String& source_name){
		//std::cout<<"Script<<asfas"<<endl;
		//cout<<"Header script: "<<source_name.CString()<<endl;
		if(stream->IsReadReady()){
			Rocket::Core::String buffer;
			stream->Read(buffer, stream->Length());
		//	cout<<buffer.CString()<<endl;
			headerScripts += buffer;

		}
	}

	void processInlineEvent(const String& eventValue, Rocket::Core::Event& event);

	AnimationFactory myAnimationFactory;
	int scriptCallStack;
	ASEngine myScriptEngine;
	ASScript* myMainScript;
	Rocket::Core::String headerScripts;
};

PARABOLA_NAMESPACE_END

#endif