#define ANDROID_PACKAGE_NAME com_parabolasamples_basic
#define ANDROID_ACTIVITY_NAME BasicSample

#include <ParabolaCore/ParabolaMain.h>
#include <ParabolaCore/Engine.h>
#include "Basic.h"
using namespace pE;

 
Engine *sdk = NULL; 

void applicationStartup(){
	sdk = new Engine();
	sdk->create();
	sdk->getGameManager().addGameForExecution(new BasicSample());
} 

void applicationUpdate(){ 
	sdk->update();
}

void applicationCleanup(){
	delete sdk;
}