#ifndef PARABOLA_ROCKETCONTEXT_H
#define PARABOLA_ROCKETCONTEXT_H

#include "Platform.h"
#include "Strings.h"
#include "Signals.h"
//#include "Drawable.h"
//#include "EventHandler.h"
#include "Vectors.h"
#include <map>
//#include "LinkedPointer.h"
#include "Localization.h"
#include <iostream>
using namespace std; //to ge tout
#include <Rocket/Core.h>
#include "RocketDocument.h"


PARABOLA_NAMESPACE_BEGIN

class RocketPlugin;
class RocketContextInstancer;
class InputEvent;

	/**
		\ingroup Graphics
		\ingroup libRocket
		\class RocketContext
		\brief Collection of documents. Usually it represents one game screen

		In normal circumstances you only need one context for the whole game, if you manage the documents well.
		However, if you use the above approach you will be loading your documents on the fly. It should not slow down a lot, but you have alternatives.
		If you wish, you can setup multiple contexts and load each one's documents before hand, so they are ready when you need them.

		It is a common approach and will work well if you have one context per game screen, for example.
	*/
	class PARABOLA_API RocketContext : public Rocket::Core::Context{
	public:
		/// Safely destroys the context on destruction
		~RocketContext();

		/// Instances a context with the desired name and dimensions
		/// Returns NULL if it was unable to create the context
		/// This function needs to be static due to the static nature of the libRocket library
		static RocketContext* create(String contextName, Vec2i dimensions);

		/// Updates the context
		void update();

		/// Dispatches a string event, normally coming from the scripting
		void generateEvent(String eventString);

		/// Sets the document as visible
		/// If the document wasn't loaded yet, it is loaded now.
		/// Returns false only if a loading has failed.
		RocketDocument* showDocument(String documentName);

		/// Hides the document
		/// Returns false if the document doesn't exist
		bool hideDocument(String documentName);

		/// Loads a document from documentPath
		/// If you specify an alias different than the empty string
		/// It becomes the document identifier
		RocketDocument* loadDocument(String documentPath, String alias = "");

		/// Unloads a document by its name
		/// The name can be an alias or the file path, depending on how you created it
		void unloadDocument(String documentName);

		/// Unloads all documents & mouse cursors
		void unloadAll();

		/// Shows a visual debugger
		void showDebugger();
		/// Hides the debugger, while keeping it open
		void hideDebugger();
		/// Closes the debugger
		void closeDebugger();

		/// Gets the document by its name
		/// The name can be an alias if created that way.
		/// Returns NULL if not found.
		RocketDocument* getDocument(String documentName);

		/// Reloads the document
		/// Returns true if sucessfull
		bool reloadDocument(String documentName);

		/// Reloads all documents in the context
		void reloadAllDocuments();

		/// Changes the identifier of a document to a new one
		/// Returns true if it could change the name
		bool setDocumentAlias(String documentName, String newDocumentName);

		/// Associates a language translator with the context.
		/// When loading a document, it will be used to translate any tokens.
		//void setLocalization(linked_ptr<Localization> &localization);

		/// Loads a font globally in rocket, scripting convenience
		void loadFont(String fontName);

		/// Get the context name
		String contextName();

		/// Process the event
		bool processEvent(InputEvent &event);

		sigc::signal<void, String> onEvent;


	protected:
		/// Virtual method implementation. Called when a RenderTarget is trying to render this context
		//virtual void Draw(sf::RenderTarget& target, sf::RenderStates states) const;

		/// Virtual method implementation. 
		void OnMouseButtonDown(unsigned int MouseButton, int x, int y, int keyMod);
		/// Virtual method implementation. 
		void OnMouseButtonUp(unsigned int MouseButton, int x, int y, int keyMod);
		/// Virtual method implementation. 
		void OnMouseMove(int x, int y, int keyMod);
		/// Virtual method implementation. 
		void OnKeyPress(unsigned int Key, int keyMod);
		/// Virtual method implementation. 
		void OnKeyReleased(unsigned int Key, int keyMod);
		/// Virtual method implementation. 
		void OnTextEntered(unsigned int Key);
		/// Virtual method implementation. 
		void OnMouseWheel(int delta, int keyMod);

	private:
		RocketContext(String contextName);

		void insert(RocketDocument *document);
		void remove(RocketDocument *document);

		std::map<String, RocketDocument*> documents;

	

		/// Translator
		//linked_ptr<Localization> myLocalization;

		friend class RocketPlugin; //for access
		friend class RocketContextInstancer; //for exclusive instancing
	};
		

PARABOLA_NAMESPACE_END
#endif