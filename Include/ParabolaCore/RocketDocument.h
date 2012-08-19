#ifndef PARABOLA_ROCKETDOCUMENT_H
#define PARABOLA_ROCKETDOCUMENT_H

#include "Platform.h"
#include "ASEngine.h"
#include "Rocket/Core.h"
#include "AnimationFactory.h"

PARABOLA_NAMESPACE_BEGIN

class RocketEvent : public Rocket::Core::Event{
public:
	int getKey(){
		Rocket::Core::Input::KeyIdentifier key = (Rocket::Core::Input::KeyIdentifier)GetParameter<int>("key_identifier", 0);
		return (int)key;
	}
};

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

	void setPseudoClass(const String &pseudo_class, bool activate){
		Rocket::Core::Element::SetPseudoClass(pseudo_class.c_str(), activate);
	}

	int getNumChildren(){
		return Rocket::Core::Element::GetNumChildren(false);
	}

	RocketElement* getChild(int index){
		return static_cast<RocketElement*>(Rocket::Core::Element::GetChild(index));
	}

};

class RocketDocument : public Rocket::Core::ElementDocument{
public:
	/// Construct the document
	RocketDocument(Rocket::Core::String tagName);

	void say(const String &sayss){
		//cout<<"SAY HI:"<<endl;
	};

	RocketElement* getElementById(const String &id){
		return (RocketElement*)Rocket::Core::Element::GetElementById(id.c_str());
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