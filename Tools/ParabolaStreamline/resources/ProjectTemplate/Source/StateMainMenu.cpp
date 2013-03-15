#include "StateMainMenu.h"
#include "GameQuiz.h"

void StateMainMenu::onActivate(){
	printf("-> Main menu");

	m_ui->onEvent.connect(MAKE_SLOT_LOCAL(StateMainMenu, rocketEvent));

	m_ui->m_globalTranslation.x  = m_game->m_renderer->m_renderTarget->getSize().x;
	m_ui->showDocument("Media/UI/home.ui");

	m_animation.addAnimable(m_ui);
	m_animation.setStartPosition(m_game->m_renderer->m_renderTarget->getSize().x, 0);
	m_animation.setDestination(0,0);
	m_animation.setDuration(2);
	m_animation.play();
}