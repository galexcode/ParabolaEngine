#include "ParabolaCore/RocketContext.h"
#include "ParabolaCore/RocketPlugin.h"
#include "ParabolaCore/RocketRenderInterface.h"
#include "ParabolaCore/RocketSystemInterface.h"
#include "ParabolaCore/StringList.h"
#include "ParabolaCore/InputEvent.h"
//#include "ParabolaCore/Events.h"
#include <Rocket/Debugger.h>
#include <vector>
#include <iostream>
using namespace std;

PARABOLA_NAMESPACE_BEGIN

/// Private constructor
RocketContext::RocketContext(String contextName) : Rocket::Core::Context(contextName.c_str()){
	
};

/// Safely destroys the context on destruction
RocketContext::~RocketContext(){
	
};

/// Instances a context with the desired name and dimensions
/// Returns NULL if it was unable to create the context
/// This function needs to be static due to the static nature of the libRocket library
RocketContext* RocketContext::create(String contextName, Vec2i dimensions){
	RocketPlugin::instance(); //ensure initialization
	RocketContext* context = dynamic_cast<RocketContext*>(Rocket::Core::CreateContext(contextName.c_str(), Rocket::Core::Vector2i(dimensions.x, dimensions.y)));
	return context;
};

/// Loads a font globally in rocket, scripting convenience
void RocketContext::loadFont(String fontName){
	RocketPlugin::instance().loadFont(fontName);
};

void RocketContext::update(){
	Update();
	
	// now update animations
	for(unsigned int i = 0; i < GetNumDocuments(); i++){
		RocketDocument* document = (RocketDocument*)GetDocument(i);
		if(document){
			document->myAnimationFactory.update(1 / 60.f);
		}
	}
};

/// Dispatches a string event, normally coming from the scripting
void RocketContext::generateEvent(String eventString){
	onEvent(eventString);
};


// void RocketContext::draw(sf::RenderTarget& target, sf::RenderStates states) const{
// 	// Draw code here.
// 
// 	if(this->GetNumDocuments() == 0)
// 		return;
// 
// 	RocketPlugin::instance().renderInterface()->target = &target;
// 	RocketPlugin::instance().renderInterface()->states = &states;	
// 	const_cast<RocketContext&>(*this).Render();
// 	RocketPlugin::instance().renderInterface()->target = NULL;
// 	RocketPlugin::instance().renderInterface()->states = NULL;
// }

/// Sets the document as visible
/// If the document wasn't loaded yet, it is loaded now.
/// Returns false only if a loading has failed.
RocketDocument* RocketContext::showDocument(String documentName){
	std::map<String, RocketDocument*>::iterator it = documents.find(documentName);
	if( it != documents.end()){
		it->second->Show();
		return it->second;
	}
	else{
		RocketDocument* document = loadDocument(documentName.c_str());
		if(document){

			

			document->Show();
			return document;
		}
		else 
			return NULL;
	} 
};

/// Hides the document
/// Returns false if the document doesn't exist
bool RocketContext::hideDocument(String documentName){
	std::map<String, RocketDocument*>::iterator it = documents.find(documentName);
	if(it != documents.end()){
		it->second->Hide();
		return true;
	}
	else
		return false;
};

/// Get the context name
String RocketContext::contextName(){
	return String(RocketContext::GetName().CString());
};

/// Process the event
bool RocketContext::processEvent(InputEvent &event){
	switch(event.type){
		case InputEvent::MouseMoved:
		{
			OnMouseMove(event.mouseMove.x, event.mouseMove.y, 0);
		}break;
		case InputEvent::MouseButtonPressed:
		{
			OnMouseButtonDown(event.mouseButton.button, event.mouseButton.x, event.mouseButton.y, 0);
		}break;
		case InputEvent::MouseButtonReleased:
		{
			OnMouseButtonUp(event.mouseButton.button, event.mouseButton.x, event.mouseButton.y, 0);
		}break;

		case InputEvent::TouchPressed:
			{
	 			OnMouseMove(event.x, event.y,0);
				OnMouseButtonDown(Mouse::Left, event.x, event.y, 0);
				
			}break;
		case InputEvent::TouchReleased:
			{
				OnMouseButtonUp(Mouse::Left, event.x, event.y, 0);
				OnMouseMove(0,0,0);
			}break; 
		case InputEvent::TouchMoved:
			{ 
				OnMouseMove(event.x, event.y, 0);			
			}break;
		
	}

	return true;
};

/// Loads a document from documentPath
/// If you specify an alias different than the empty string
/// It becomes the document identifier
RocketDocument* RocketContext::loadDocument(String documentPath, String alias){
	RocketDocument *document = (RocketDocument*)LoadDocument(documentPath.c_str());
	if(document){
		if(alias.empty())
			documents[documentPath] = document;
		else
			documents[alias] = document;

		// Finish the script loading
		//cout<<"header scripts:"<<document->headerScripts.CString()<<endl;
		
		document->myScriptEngine.exportGlobalProperty("RocketContext context", this);
		ASScript *script = document->myScriptEngine.loadScriptFromMemory(document->headerScripts.CString(), "rocketscript");
		if(script){
			cout<<"sucessfully loaded!"<<endl;
			
			//document->DispatchEvent("hide", Rocket::Core::Dictionary(), false);
			//document->myScriptEngine.exportGlobalProperty("RocketElement element", document);

			Rocket::Core::ElementList list;

			document->GetElementsByTagName(list, "script");

			//cout<<"Read "<<list.size()<<" script elements"<<endl;

			Rocket::Core::String resultFunction = "void rocketScriptStartupCode(){";
			for(unsigned int j = 0; j < list.size(); j++){
				//cout<<"Script: "<<list[j]->GetInnerRML().CString()<<endl;
				resultFunction += list[j]->GetInnerRML(); 
				
			}
			resultFunction += " }";	
			script->compileCode(resultFunction.CString(), "rocketScriptStartupCode");

			if(script->call(String("void rocketScriptStartupCode()"))){
				cout<<"Called function"<<endl;
			}
			else cout<<"NOT CALLED"<<endl;

			document->myMainScript = script;

		}

		//parse script tags
			
	

		return document;
	}
	else 
		return false;
};

/// Unloads a document by its name
/// The name can be an alias or the file path, depending on how you created it
void RocketContext::unloadDocument(String documentName){
	std::map<String, RocketDocument*>::iterator it = documents.find(documentName);
	if(it != documents.end()){
		it->second->Close();
		UnloadDocument(it->second);
		documents.erase(it);
	}
};

/// Unloads all documents
void RocketContext::unloadAll(){
	documents.clear();
	UnloadAllDocuments();
	UnloadAllMouseCursors();
};

/// Gets the document by its name
/// The name can be an alias if created that way.
/// Returns NULL if not found.
RocketDocument* RocketContext::getDocument(String documentName){
	std::map<String, RocketDocument*>::iterator it = documents.find(documentName);
	if(it != documents.end()){
		return it->second;
	}
	else
		return NULL;
};

/// Shows a visual debugger
void RocketContext::showDebugger(){
//	Rocket::Debugger::Initialise(this);
	//Rocket::Debugger::SetContext(this);
	//Rocket::Debugger::SetVisible(true);
};
/// Hides the debugger, while keeping it open
void RocketContext::hideDebugger(){
	//Rocket::Debugger::SetVisible(false);
};
/// Closes the debugger
void RocketContext::closeDebugger(){
	//Rocket::Debugger::Initialise(NULL);
	//Rocket::Debugger::SetContext(NULL);
};

/// Changes the identifier of a document to a new one
bool RocketContext::setDocumentAlias(String documentName, String newDocumentName){
	std::map<String, RocketDocument*>::iterator it = documents.find(documentName);
	if(it != documents.end()){
		//found documentName, lets try to change

		if(documents.find(newDocumentName) == documents.end()){
			//but only if the new doesnt exist.			
			documents[newDocumentName] = it->second;
			documents.erase(it);
			return true;
		}
		else
			return false;
	}
	return false;
};

/// Associates a language translator with the context.
/// When loading a document, it will be used to translate any tokens.
/*void RocketContext::setLocalization(linked_ptr<Localization> &localization){
	myLocalization = localization;
};*/

/// Reloads the document
/// Returns true if sucessfull
bool RocketContext::reloadDocument(String documentName){
	std::map<String, RocketDocument*>::iterator it = documents.find(documentName);
	if(it != documents.end()){
		//found it, reload
		String url = it->second->GetSourceURL().CString();
		String alias = (it->first == url) ? "" : it->first;
		unloadDocument(documentName);
		loadDocument(url, alias);
		return true;
	}
	else return false;
};

/// Reloads all documents in the context
void RocketContext::reloadAllDocuments(){
	/*std::vector<String> v1,v2;
	std::map<String, RocketDocument*>::iterator it;
	for(it = documents.begin(); it != documents.end(); it++){
		String url = it->second->GetSourceURL().CString();
		String alias = (it->first == url) ? "" : it->first;
		it->second->Close();
		it = documents.erase(it);

		v1.push_back(url);
		v2.push_back(alias);
	}

	for(unsigned int i = 0; i < v1.size(); i++){
		loadDocument(v1[i], v2[i]);
	}*/
};

void RocketContext::insert(RocketDocument *document){
	//in the case i need, i can insert documents from the plugin with this
};
void RocketContext::remove(RocketDocument *document){
	//in the case i need, i can remove documents from the plugin with this
};


void RocketContext::OnMouseButtonDown(unsigned int MouseButton, int x, int y, int keyMod){
	ProcessMouseMove(x, y, keyMod);
	ProcessMouseButtonDown(MouseButton, keyMod);
};

void RocketContext::OnMouseButtonUp(unsigned int MouseButton, int x, int y, int keyMod){
	ProcessMouseMove(x, y, keyMod);
	ProcessMouseButtonUp(MouseButton, keyMod);
};

void RocketContext::OnMouseMove(int x, int y, int keyMod){
	ProcessMouseMove(x, y, keyMod);
};

void RocketContext::OnMouseWheel(int delta, int keyMod){
	ProcessMouseWheel(delta, keyMod);
};


void RocketContext::OnKeyPress(unsigned int Key, int keyMod){
	//ProcessKeyDown((Rocket::Core::Input::KeyIdentifier)EventDispatcher::translateToRocketKey(Key), keyMod);
};

void RocketContext::OnKeyReleased(unsigned int Key, int keyMod){
	//ProcessKeyUp((Rocket::Core::Input::KeyIdentifier)EventDispatcher::translateToRocketKey(Key), keyMod);
};

void RocketContext::OnTextEntered(unsigned int Key){
	if(Key >= 32){	
		ProcessTextInput((Rocket::Core::word)Key);			
	}
};


















/*


	void RocketContext::QueueEvent(Rocket::Core::Event& event, Rocket::Core::String& value){
		RocketEvent *Event = new RocketEvent;
		Event->Value = value.CString();
		Event->Event = event;

		if(InternalHandlerEnabled){
			ParseAndExecute(Event);
			if(Event->Value.length() > 0)
				EventQueue.push(Event);
		}
		else
			EventQueue.push(Event);
	}*/

/*
	bool RocketContext::NextPendingEvent(RocketEvent &Event){
		if(EventQueue.size() == 0)
			return false;

		Event = *EventQueue.front();
		//Event.Event = EventQueue[0]->Event;
		//Event.Value = EventQueue[0]->Value;
		EventQueue.pop();
		return true;
	}*/

	/*void RocketContext::ParseAndExecute(RocketEvent* Event){
		int Begin = Event->Value.contains("[engine]");
		if(Begin == -1) //No {engine] tag, exit
			return ;

		String Commands;
		int End = Event->Value.contains("[/engine]");
		if(End == -1){
			//No closing tag, just copy everything

			Commands = Event->Value.substr(Begin+8, Event->Value.length()-Begin+9);
			Event->Value.erase(Begin, Event->Value.length()-Begin+8);
		}
		else{
			//Take right subString
			Commands = Event->Value.substr(Begin+8,End-Begin-8);
			Event->Value.erase(Begin, End+9-Begin);
		}

		StringList CommandList = Commands.split(";");
		for(unsigned int i = 0; i < CommandList.size(); i++){
			StringList CommandParameters = CommandList[i].split(" ", 1);
			if(CommandParameters[0] == "log"){
				cout<<"Internal Log[libRocket]: "<<CommandParameters[1]<<endl;
				continue;
			}
			if(CommandParameters[0] == "open"){
				StringList Options = CommandParameters[1].split("->");
				Rocket::Core::ElementDocument* Document;
				if(Options.size() > 1){
					if(Options[1] == "fadein"){
						cout<<"Fade effect"<<endl;
						Document = OpenDocument(Options[0], false);

						//Rocket::RocketManager->SetElementColor(Document, Color(0,0,0,20));
						Document->Show();
						Document->Focus();
					}
				}
				else{
					cout<<"Normally opened"<<endl;
					Document = OpenDocument(Options[0]);
				}
				
				continue;
			}
			if(CommandParameters[0] == "close"){
				if(CommandParameters[1] == "this"){
					//Close this document
					Event->Event.GetCurrentElement()->GetOwnerDocument()->Close();
				}
				
				continue;
			}

		}
		
	}*/

	






PARABOLA_NAMESPACE_END