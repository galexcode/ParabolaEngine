#ifndef PARABOLA_STATEMACHINE_H
#define PARABOLA_STATEMACHINE_H

#include "Platform.h"
#include "State.h"

#include <vector>
#include <map>

PARABOLA_NAMESPACE_BEGIN

	struct StateStackOperation
	{
		enum Type
		{
			Erase = 0,
			Add
		};

		Type type;
		State* obj;
	};

	class Renderer;
	class Event;

	/**
		\ingroup Core
		\class StateMachine
		\brief Represents a finite state machine.

		It allows you to create a machine and add states to it, then transition between them.
	*/
	class PARABOLA_API StateStack{
	public:
		/// Creates an empty state machine
		StateStack();
		/// Safely destroys all states by sending them a destroy callback
		~StateStack();

		/// Adds state to immediate execution
		void add(State* state);

	/// Adds a state to the waiting list
	void addWaiting(State* state);


		/// Get the state associated with stateID
		/// Returns NULL if that state doesn't belong to the machine
		/// \note This function may be dangerous to use
		/// That is because you get a base node
		/// pointer which you may then cast to your custom state.
		/// If the returned node isn't of the type you casted it to, you get undefined behavior
		/// Using dynamic_cast is recommended to avoid this kind of problems.
		State* getState(int stateID);

		/// Sets a new state or replaces an existing one
		/// It makes an associated between an int identifier and the actual node
		void setState(int stateID, State* node);

		/// Destroys the state specified
		/// States are reference counted, so it may not be destroyed immediately
		void removeState(int stateID);

		/// Replaces the top of the stack with the new state
		void swapState(int stateID);
		/// Pushes a state into the stack
		void pushState(int stateID);
		/// Pops the top of the stack
		void popState();

		/// Handles a signal received from a state
		/// \todo improvements here
		bool handleSignal(int stateID, bool toReplace);
		
		/// Delivers a String to stateID state
		bool deliverMessage(int stateID, String message);

		/// Delivers a String and a pointer to anything to stateID state
		bool deliverData(int stateID, String dataID, void* data);

		/// Updates the right states 
		void updateStates(Time &time);

		/// Delivers the event to the right events
		void propagateEvent(Event &event);

		/// Draws the right states
		void drawStates(Renderer *renderer);

	/// Bind a new state to the list
	/// Returns false if the name was already taken
	bool bind(const String& name, State* state);

	/// Processes the list of changes to the stack
	void applyChanges();

	/// Erase a state
	void erase(State* state);

	/// Get a state or NULL
	State* getBinding(const String& name);

private:
	std::map<int, State*> nodes;
	std::vector<State*> nodeStack;
	std::vector<State*> m_waitingList;
	std::map<String, State*> m_bindList;
	std::vector<StateStackOperation> m_pendingOperations;

	bool m_stackLock;
};

class ASEngine;
bool registerStateStack(ASEngine* engine);

PARABOLA_NAMESPACE_END
#endif