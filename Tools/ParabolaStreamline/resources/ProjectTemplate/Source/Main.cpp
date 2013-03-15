#define ANDROID_PACKAGE_NAME com_demoneulogy_gamequiz
#define ANDROID_ACTIVITY_NAME GameQuiz
#include <ParabolaCore/ParabolaMain.h>
#include <ParabolaCore/Engine.h>
using namespace pE;

#include "GameQuiz.h"

Engine *sdk = NULL;

void applicationStartup(){
	sdk = new Engine();
	Engine::Settings& settings = sdk->getSettings();
	settings.windowWidth = 512;
	settings.windowHeight = 256;
	sdk->create(settings);
	sdk->getGameManager().addGameForExecution(new GameQuiz());
}

void applicationUpdate(){
	sdk->update();
}

void applicationCleanup(){
	delete sdk;
}