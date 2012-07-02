#include "ParabolaCore/RocketPlugin.h"
#include "ParabolaCore/RocketRenderInterface.h"
#include "ParabolaCore/RocketSystemInterface.h"
#include "ParabolaCore/RocketEventInterface.h"
#include "ParabolaCore/RocketFileInterface.h"
//#include "ParabolaCore/RocketEventBox.h"
#include <Rocket/Controls.h>

PARABOLA_NAMESPACE_BEGIN

RocketPlugin* RocketPlugin::myInstance = NULL;
RocketEventDispatcher* RocketPlugin::myDispatcher = NULL;
RocketRenderInterface* RocketPlugin::RenderInterface = NULL;
RocketSystemInterface* RocketPlugin::SystemInterface = NULL;

class RocketContextInstancer;


/************************************************************************/
/* CONTEXT INSTANCER                                                    */
/************************************************************************/
class RocketContextInstancer : public Rocket::Core::ContextInstancer{
public:
	// Instances a context.
	// @param[in] name Name of this context.
	// @return The instanced context.
	virtual Rocket::Core::Context* InstanceContext(const Rocket::Core::String& name){
		return (new RocketContext(String(name.CString())));
	}

	// Releases a context previously created by this context.
	// @param[in] context The context to release.
	virtual void ReleaseContext(Rocket::Core::Context* context){
		delete context;
	}

	// Releases this context instancer
	virtual void Release(){
		delete this;
	}
};

/// Private constructor
RocketPlugin::RocketPlugin(){
	num_documents = 0;
	myDispatcher = NULL;
};

/// Safe destruction of the rocket plugin
/// Normally, it won't do nothing as the process is done before getting here.
RocketPlugin::~RocketPlugin(){
	if(myInstance){
		stopLibRocket();
	}
};

/// Get the instance of the plugin
/// In the case libRocket was not already initialized, it will be done automatically.
RocketPlugin& RocketPlugin::instance(){
	if(!myInstance){
		startLibRocket();		
	}
	return *myInstance;
};

void RocketPlugin::startLibRocket(){
	// Start the libRocket machinery

	//First thing - instance the plugin
	myInstance = new RocketPlugin();

	//Register the plugin
	Rocket::Core::RegisterPlugin(myInstance);

	//Instance the interfaces
	RenderInterface = new RocketRenderInterface();
	SystemInterface = new RocketSystemInterface();
	RocketFileInterface* file_interface = new RocketFileInterface("");

	//Assign the interfaces
	Rocket::Core::SetRenderInterface(RenderInterface);
	Rocket::Core::SetSystemInterface(SystemInterface);
	Rocket::Core::SetFileInterface(file_interface);

	// Initialise the rocket library
	Rocket::Core::Initialise();

	// Initialise the controls library
	Rocket::Controls::Initialise();


	// libRocket is now ready, register the custom RocketContext* instancer
	RocketContextInstancer *context_instancer = new RocketContextInstancer();
	Rocket::Core::Factory::RegisterContextInstancer(context_instancer);
	context_instancer->RemoveReference();

	Rocket::Core::ElementInstancerGeneric<RocketDocument> *documentinstancer = new Rocket::Core::ElementInstancerGeneric<RocketDocument>();
	Rocket::Core::Factory::RegisterElementInstancer("body", documentinstancer);
	documentinstancer->RemoveReference();

	Rocket::Core::ElementInstancerGeneric<RocketElement> *elementinstancer = new Rocket::Core::ElementInstancerGeneric<RocketElement>();
	Rocket::Core::Factory::RegisterElementInstancer("*", elementinstancer);
	elementinstancer->RemoveReference();


	//Custom event instancer
	myDispatcher = new RocketEventDispatcher();
	Rocket::Core::Factory::RegisterEventListenerInstancer(myDispatcher);
	myDispatcher->RemoveReference(); // allow destruction on exit.


};

// Stop the rocket support
void RocketPlugin::stopLibRocket(){	
	if(myInstance){
		//Shutdown the library
		Rocket::Core::Shutdown();

		//Deactivate the interfaces for safe destruction
		Rocket::Core::SetRenderInterface(NULL);
		Rocket::Core::SetSystemInterface(NULL);

		// Remove references for reference count = 0, is it necessary?!
		RenderInterface->RemoveReference();
		SystemInterface->RemoveReference();

		// Destroy the interfaces
		delete RenderInterface;
		RenderInterface = NULL;
		delete SystemInterface;
		SystemInterface = NULL;

		myDispatcher = NULL;

		// Finnally, destroy the instance
		delete myInstance;
		myInstance = NULL;
	}
	// Otherwise it was never instanced
};

/// Registers a tag name as a input area
/// This is used to have a specific element in your document fetching input and sending it through the event dispatcher
/// Returns an element that you can configure to taste.
/// This must be done before the document is loaded, or the tag with this name will not be any special
/*bool RocketPlugin::registerEventCatcher(String tag_name){
	if(myEventCatchers.find(tag_name) != myEventCatchers.end())return false; //already exists

	Rocket::Core::String str = tag_name.c_str();
	Rocket::Core::ElementInstancerGeneric<RocketEventBox> *tagInstancer = new Rocket::Core::ElementInstancerGeneric<RocketEventBox>();
	tagInstancer = (Rocket::Core::ElementInstancerGeneric<RocketEventBox>*)Rocket::Core::Factory::RegisterElementInstancer(str, tagInstancer);
	if(!tagInstancer)return false;
	tagInstancer->RemoveReference();
	return true;
};*/

/// Get an already created event catcher
/*RocketEventBox* RocketPlugin::getEventCatcher(const String &tagName){
	if(myEventCatchers.find(tagName) == myEventCatchers.end()){
		return NULL;
	}
	else{
		return myEventCatchers.find(tagName)->second;
	}
};*/

/// Updates all contexts created globally
void RocketPlugin::updateAll(){
	for(std::map<String, RocketContext*>::iterator it = contexts.begin(); it != contexts.end(); it++){
		it->second->Update();
	}
};


/// Gets the global number of documents loaded
int RocketPlugin::getNumDocuments(){
	return num_documents;
};

/// Get the global event dispatcher of libRocket
RocketEventDispatcher& RocketPlugin::eventDispatcher(){
	return *myDispatcher;
};

/// Gets the global number of contexts created
int RocketPlugin::getNumContexts(){
	return (int)contexts.size();
};

/// Loads a font from a file
/// By default argument, it has no alias, its not in bold and not in italic.
/// The alias is simply to specify another name for the font when using the 
/// font-family property in RCSS.
/// An empty string alias means no alias.
bool RocketPlugin::loadFont(String path, String alias, bool bold, bool italic){
	if(alias.empty()){
		return Rocket::Core::FontDatabase::LoadFontFace(path.c_str()); 
	}
	else{
		Rocket::Core::Font::Style style;
		Rocket::Core::Font::Weight weight;

		if(bold)weight = Rocket::Core::Font::WEIGHT_BOLD;
		else weight = Rocket::Core::Font::WEIGHT_NORMAL;

		if(italic)style = Rocket::Core::Font::STYLE_ITALIC;
		else style = Rocket::Core::Font::STYLE_NORMAL;

		return Rocket::Core::FontDatabase::LoadFontFace(path.c_str(), alias.c_str(), style, weight); 
	}
	
};

/// Get the render interface of libRocket
RocketRenderInterface* RocketPlugin::renderInterface(){
	return RocketPlugin::RenderInterface;
};

/// Get the system interface of libRocket
RocketSystemInterface* RocketPlugin::systemInterface(){
	return RocketPlugin::SystemInterface;
};
	
/// PLUGIN CALLBACKS
void RocketPlugin::OnInitialise(){
		
}
void RocketPlugin::OnShutdown(){
	
}
void RocketPlugin::OnDocumentOpen(Rocket::Core::Context* context, const Rocket::Core::String& document_path){
		
}
void RocketPlugin::OnDocumentLoad(Rocket::Core::ElementDocument* document){
	num_documents++;
	((RocketContext*)document->GetContext())->insert((RocketDocument*)document);
}
void RocketPlugin::OnDocumentUnload(Rocket::Core::ElementDocument* document){
	num_documents--;
	((RocketContext*)document->GetContext())->remove((RocketDocument*)document);
}
void RocketPlugin::OnContextCreate(Rocket::Core::Context* context){
	contexts[context->GetName().CString()] = (RocketContext*)context;
}
void RocketPlugin::OnContextDestroy(Rocket::Core::Context* context){
	contexts.erase(contexts.find(context->GetName().CString()));

	if(contexts.size() == 0){
		//disable due to no more contexts alive
		stopLibRocket();
	}
}
void RocketPlugin::OnElementCreate(Rocket::Core::Element* element){

}
void RocketPlugin::OnElementDestroy(Rocket::Core::Element* element){

}



PARABOLA_NAMESPACE_END