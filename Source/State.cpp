#include "ParabolaCore/State.h"
#include "ParabolaCore/StateStack.h"
#include "ParabolaCore/Events.h"

#include <iostream>

PARABOLA_NAMESPACE_BEGIN
	State::State() : RefCountable() {
		m_parent = NULL;
	};

	void State::onActivate(){
		
	};

	void State::onDeactivate(){

	};

	void State::onMessageReceived(String message){

	};

	void State::onDataReceived(String dataID, void* data){

	};

	StateStack* State::parentMachine(){
		return m_parent;
	};

	/// Emits a signal to the parent machine
	/// If the machine decides to change into another state, it returns true.
	bool State::emit(int stateID, bool replaces){
		if(m_parent){
			return m_parent->handleSignal(stateID, replaces);
		}else{
			std::cout<<"You can't be using a state without a machine."<<std::endl;
			return false;
		}
	};

/// Finish will inform the state stack this state is done, and should be removed
void State::finish()
{
	if(m_parent)
	{
		// schedule this state for erasing
		m_parent->erase(this);
	}
};

/// Attempts to launch a state from the bind list
bool State::launchBindedState(const String& stateName)
{
	if(m_parent)
	{
		State* bindedState = m_parent->getBinding(stateName);
		if(bindedState)
		{
			m_parent->add(bindedState);
			return true;
		}
		else return false;
	}
	else return false;
};


	/// Delivers an event to the state
	/// If returns true, it will be propagated to the rest of the stack
	/// Otherwise it will remain under this.
	bool State::onEvent(Event &event){
		return true;
	};

	bool State::onUpdate(Time &time){
		return true;
	};

	/// Draws the state with the current renderer
	/// If returns true, other states in the stack will be rendered
	/// Otherwise this state has exclusivity over drawing
	bool State::onDraw(Renderer *renderer){
		return true;
	};

PARABOLA_NAMESPACE_END