#ifndef StateBasicSession_h__
#define StateBasicSession_h__

#include <ParabolaCore/StateMachineNode.h>
#include <ParabolaCore/Textures.h>
#include <ParabolaCore/Sprite.h>
#include <ParabolaCore/Animation.h>
#include <ParabolaCore/AnimationGroupSequential.h>
#include <ParabolaCore/AnimationStall.h>
#include <ParabolaCore/AnimationFade.h>
#include <ParabolaCore/Logger.h>
#include <ParabolaCore/Renderer.h>
#include <ParabolaCore/FileSystem.h>
#include <ParabolaCore/TextStream.h>
using namespace pE;

#include "Globals.h"

class StateBasicSession : public StateMachineNode{
public:
	StateBasicSession(){
		m_failedQuestions = 0;
	}

	void onActivate();

	/// Resets the session to a fresh one
	void reset();

	/// Prepares everything for a new question
	void pickRandomQuestion();

	/// Checks if a question was already out for the session
	bool isQuestionUsed(int difficultyLevel, int questionIndex);

	/// Events from libRocket
	void rocketEvent(String event);

	bool onEvent(Event &event){
		m_ui->processEvent(event);
		return false;
	}

	bool onUpdate(Time &time){ 
		return false;
	}

	bool onDraw(Renderer *renderer){
		View v;
		v.setRect(0,0, renderer->m_renderTarget->getSize().x, renderer->m_renderTarget->getSize().y);
		renderer->setView(v);
		renderer->drawRocketContext(m_ui);
		return false;
	}

	int m_currentCorrectAnswer;
	int m_failedQuestions;
	typedef std::pair<int,int> QuestionID; // int - difficulty int - question index
	std::vector<QuestionID> m_usedQuestions;

	/// Stores the amount of available questions for each difficulty
	std::map<int,int> m_questionCounts;
};


#endif // StateBasicSession_h__
