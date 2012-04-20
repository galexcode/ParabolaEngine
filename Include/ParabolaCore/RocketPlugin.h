#ifndef PARABOLA_ROCKETPLUGIN_H
#define PARABOLA_ROCKETPLUGIN_H

#include "Platform.h"
#include "RocketContext.h"
#include "Strings.h"
#include "RocketEventBox.h"


/**
	\defgroup libRocket

	libRocket user interface library related classes.
*/

PARABOLA_NAMESPACE_BEGIN
	class RocketEventDispatcher;
	class RocketRenderInterface;
	class RocketSystemInterface;

	/**
		\ingroup libRocket
		\ingroup Graphics
		\class RocketPlugin
		\brief A libRocket plugin to manage rocket resources.

		The plugin is a singleton class. It is meant to be used plug and play on your game.
		You cannot instance it yourself, rather use RocketPlugin::instance()
		
		If you want to use libRocket UI in your game, you may proceed to creating your RocketContext right away,
		everything will be initialized automatically. When the last RocketContext object is destroyed, the libRocket plugin will
		fall asleep again.

		This means that libRocket is only working when there are alive contexts.

		You can use this plugin for some specific purposes, but you should be fine with using only the contexts.

		\see RocketContext
	*/
	class PARABOLA_API RocketPlugin: public Rocket::Core::Plugin{
	public:
		/// Safe destruction of the rocket plugin
		/// Normally, it won't do nothing as the process is done before getting here.
		~RocketPlugin();

		/// Get the instance of the plugin
		/// In the case libRocket was not already initialized, it will be done automatically.
		/// When the last context is destroyed, libRocket goes back to sleep.
		static RocketPlugin& instance();

		/// Get the global event dispatcher of libRocket
		RocketEventDispatcher& eventDispatcher();

		/// Registers a tag name as a input area
		/// This is used to have a specific element in your document fetching input and sending it through the event dispatcher
		/// Returns whether the registration was sucessfull
		/// This must be done before the document is loaded, or the tag with this name will not be any special
		bool registerEventCatcher(String tag_name);

		/// Get an already created event catcher
		RocketEventBox* getEventCatcher(const String &tagName);

		/// Updates all contexts created globally
		void updateAll();

		/// Gets the global number of documents loaded
		int getNumDocuments();

		/// Gets the global number of contexts created
		int getNumContexts();

		/// Loads a font from a file
		/// By default argument, it has no alias, its not in bold and not in italic.
		/// The alias is simply to specify another name for the font when using the 
		/// font-family property in RCSS.
		/// An empty string alias means no alias and normal style in the font
		bool loadFont(String path, String alias = "", bool bold = false, bool italic = false);

		/// Get the render interface of libRocket
		RocketRenderInterface* renderInterface();

		/// Get the system interface of libRocket
		RocketSystemInterface* systemInterface();
	
	protected:
		/// Implementation of virtual method. Called when the plugin starts
		virtual void OnInitialise();
		/// Implementation of virtual method. Called when the plugin shuts down
		virtual void OnShutdown();
		/// Implementation of virtual method. Called when a document is opened
		virtual void OnDocumentOpen(Rocket::Core::Context* context, const Rocket::Core::String& document_path);
		/// Implementation of virtual method. Called when a document is loaded
		virtual void OnDocumentLoad(Rocket::Core::ElementDocument* document);
		/// Implementation of virtual method. Called when a document is unloaded
		virtual void OnDocumentUnload(Rocket::Core::ElementDocument* document);
		/// Implementation of virtual method. Called when a context is created
		virtual void OnContextCreate(Rocket::Core::Context* context);
		/// Implementation of virtual method. Called when a context is destroyed
		virtual void OnContextDestroy(Rocket::Core::Context* context);
		/// Implementation of virtual method. Called when a single element is created
		virtual void OnElementCreate(Rocket::Core::Element* element);
		/// Implementation of virtual method. Called when a single element is destroyed
		virtual void OnElementDestroy(Rocket::Core::Element* element);

	private:
		RocketPlugin();

		// Start the rocket support and make instance valid
		static void startLibRocket();
		// Stop the rocket support
		static void stopLibRocket();
		static RocketPlugin* myInstance;

		// Interfaces
		static RocketRenderInterface *RenderInterface;
		static RocketSystemInterface *SystemInterface;

		// Objects
		std::map<String, RocketContext*> contexts;

		static RocketEventDispatcher* myDispatcher;

		friend class RocketEventBox;
		std::map<String, RocketEventBox*> myEventCatchers;

		int num_documents;
	};
	

PARABOLA_NAMESPACE_END
#endif