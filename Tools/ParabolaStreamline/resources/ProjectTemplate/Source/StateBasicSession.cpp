#include "StateBasicSession.h"
#include <algorithm>

void StateBasicSession::onActivate(){
	m_ui->onEvent.connect(MAKE_SLOT_LOCAL(StateBasicSession, rocketEvent));
	m_ui->showDocument("Media/UI/question1.ui");
	printf("Activated");

	m_currentCorrectAnswer = 1;

	// Read the question availability info
	m_questionCounts.clear();
	StringList difficulties = FileSystem::scanDirectory("Questions", "txt", false);
	for(unsigned int i = 0; i < difficulties.size(); i++){
		ScopedFile in(difficulties[i], IODevice::TextRead);
		TextStream txt(&in);
		int qcount = txt.getLine().toInt();

		//difficulties[i].split('/', 0, )
		int difficulty;
		m_questionCounts[difficulty] = qcount;
	}
}
 
void StateBasicSession::reset(){
	m_failedQuestions = 0;
	m_usedQuestions.clear();
}

/// Prepares everything for a new question
void StateBasicSession::pickRandomQuestion(){

};

/// Checks if a question was already out for the session
bool StateBasicSession::isQuestionUsed(int difficultyLevel, int questionIndex){
	return (std::find(m_usedQuestions.begin(), m_usedQuestions.end(), std::make_pair<int,int>(difficultyLevel, questionIndex)) != m_usedQuestions.end());
};

void StateBasicSession::rocketEvent(String event){
	printf("%s\n", event.c_str());

	if(event.startsWith("answer")){
		int chosen = 0;
		StringList l = event.split('_', 0);
		chosen = l.at(1).toInt();
		printf("Chosen option %d\n", chosen);

		if(chosen == m_currentCorrectAnswer){
			printf("CORRECT ANSWER\n");
		}
	}
}