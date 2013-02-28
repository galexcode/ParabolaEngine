#include "ParabolaCore/StateStack.h"
#include "ParabolaCore/ASEngine.h"
#include "AS/aswrappedcall.h"

#include <iostream>
#include <algorithm>
using namespace std;

PARABOLA_NAMESPACE_BEGIN

/// Register the state stack into engine
bool registerStateStack(ASEngine* engine)
{
	engine->exportReferenceDataType("StateStack");
	engine->exportReferenceDataType("State");

	if(engine->getPortableMode())
	{
		engine->getASEngine()->RegisterObjectMethod("StateStack", "void add(State@)", WRAP_MFN(StateStack, add), asCALL_GENERIC);
		engine->getASEngine()->RegisterObjectMethod("StateStack", "void addWaiting(State@)", WRAP_MFN(StateStack, addWaiting), asCALL_GENERIC);
		engine->getASEngine()->RegisterObjectMethod("StateStack", "bool bind(const string& in, State@)", WRAP_MFN(StateStack, bind), asCALL_GENERIC);

	}
	else
	{
		engine->getASEngine()->RegisterObjectMethod("StateStack", "void add(State@)", asMETHOD(StateStack, add), asCALL_THISCALL);
		engine->getASEngine()->RegisterObjectMethod("StateStack", "void addWaiting(State@)", asMETHOD(StateStack, addWaiting), asCALL_THISCALL);
		engine->getASEngine()->RegisterObjectMethod("StateStack", "bool bind(const string& in, State@)", asMETHOD(StateStack, bind), asCALL_THISCALL);
	}

	return true;
};


	StateStack::StateStack() : m_stackLock(false){

	};

	StateStack::~StateStack(){
		//destroy states? need reference counting.
		for(std::map<int, State*>::iterator it = nodes.begin(); it != nodes.end(); it++){
			(*it).second->removeReference();
		}

	};

/// Get a state or NULL
State* StateStack::getBinding(const String& name)
{
	std::map<String, State*>::iterator it = m_bindList.find(name);
	if(it != m_bindList.end())
	{
		return it->second;
	}
	else return NULL;
};

/// Adds state to immediate execution
void StateStack::add(State* state)
{
	state->addReference();
	state->m_parent = this;

	if(m_stackLock)
	{
		// schedule
		StateStackOperation sso;
		sso.type = StateStackOperation::Add;
		sso.obj = state;
		m_pendingOperations.push_back(sso);
	}
	else
	{
		// do
		state->onActivate();
		nodeStack.push_back(state);
	}
};

/// Adds a state to the waiting list
void StateStack::addWaiting(State* state)
{
	state->addReference(); // reference just for the waiting list
	m_waitingList.push_back(state);

	cout<<"[StateStack] State added to waiting list"<<endl;
};


/// Processes the list of changes to the stack
void StateStack::applyChanges()
{
	while(!m_pendingOperations.empty())
	{
		switch(m_pendingOperations.front().type)
		{
			case StateStackOperation::Erase:
				erase(m_pendingOperations.front().obj);
				break;

			case StateStackOperation::Add:
				m_pendingOperations.front().obj->onActivate();
				nodeStack.push_back(m_pendingOperations.front().obj);
				break;
		}

		m_pendingOperations.erase(m_pendingOperations.begin());
	}

	// There is a chance of already having more states - stack overflow if there is a loophole within state logic
	if(!m_pendingOperations.empty())
	{
		applyChanges();
	}
};

/// Bind a new state to the list
bool StateStack::bind(const String& name, State* state)
{
	if(m_bindList.find(name) != m_bindList.end())
	{
		return false;
	}
	else
	{
		state->addReference();
		m_bindList[name] = state;
	}

	return true;
};

/// Erase a state
void StateStack::erase(State* state)
{
	if(m_stackLock)
	{
		// schedule
		StateStackOperation sso;
		sso.obj = state;
		sso.type = StateStackOperation::Erase;
		m_pendingOperations.push_back(sso);
	}
	else
	{
		// do
		state->removeReference();
		nodeStack.erase(std::find(nodeStack.begin(), nodeStack.end(), state));
		cout<<"[StateStack] Erased"<<endl;

		// erased, if reaches 0, add to stack from waiting list
		if(nodeStack.empty() && !m_waitingList.empty())
		{
			add(m_waitingList.front());
			m_waitingList.front()->removeReference(); // remove waiting list reference
			m_waitingList.erase(m_waitingList.begin());
		}
	}
};

	State* StateStack::getState(int stateID){
		State *node = nodes[stateID];
		node->RefCount++;
		return node;
	};

	void StateStack::setState(int stateID, State* node){
		nodes[stateID] = node;
		node->m_parent = this;
		node->RefCount++;
	};

	void StateStack::removeState(int stateID){
		nodes[stateID]->removeReference();
		nodes[stateID] = NULL;
	};

	/// Replaces the top of the stack with the new state
	void StateStack::swapState(int stateID){
		popState();
		pushState(stateID);
	};

	/// Pushes a state into the stack
	void StateStack::pushState(int stateID){
		State *node = nodes[stateID];
		if(node){
			nodeStack.push_back(node);
			node->onActivate();
			
		}
		else{
			std::cout<<"You tried to push a node that doesnt exist."<<std::endl;
		}
		
	};

	/// Pops the top of the stack
	void StateStack::popState(){
		if(nodeStack.size() != 0){					
			nodeStack[nodeStack.size()-1]->onDeactivate();
			nodeStack.pop_back();		
		}
		else{
			
		}
	};


	void StateStack::propagateEvent(Event &event){
		if(nodeStack.size() == 0){
			return;
		}

		int index = nodeStack.size()-1;
		bool stop = false;

		m_stackLock = true;
		while(index != -1 && stop == false){
			stop = !nodeStack[index]->onEvent(event);
			index--;
		}
		m_stackLock = false;

		applyChanges();
	};

	bool StateStack::handleSignal(int stateID, bool toReplace){
		if(nodes[stateID] != NULL){
			if(toReplace){
				swapState(stateID);
			}
			else{
				pushState(stateID);
			}
			return true;
		}
		else
			return false;
	};

	bool StateStack::deliverMessage(int stateID, String message){
		if(nodes[stateID] != NULL){
			nodes[stateID]->onMessageReceived(message);
			return true;
		}
		else
			return false;
	};

	bool StateStack::deliverData(int stateID, String dataID, void* data){
		if(nodes[stateID] != NULL){
			nodes[stateID]->onDataReceived(dataID, data);
			return true;
		}
		else
			return false;
	};

void StateStack::drawStates(Renderer *renderer){
	if(nodeStack.size() == 0){
		return;
	}

	int index = 0;
	bool stop = false;

	while(index < nodeStack.size()){
		nodeStack[index]->onDraw(renderer);
		index++;
	}
};

	void StateStack::updateStates(Time &time){
		
		if(nodeStack.size() == 0){
			return;
		}
		// older states draw first
		int index = nodeStack.size()-1;
		bool stop = false;

		m_stackLock = true;
		while(index != -1 && stop == false){
			stop = !nodeStack[index]->onUpdate(time);
			index--;
		}
		m_stackLock = false;

		applyChanges();
	};

PARABOLA_NAMESPACE_END
