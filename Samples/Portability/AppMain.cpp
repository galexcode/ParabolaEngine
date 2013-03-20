#include <ParabolaCore/ParabolaMain.h>
#include <ParabolaCore/Engine.h>
#include "PortabilityTest.h"
using namespace pE;

Engine sdk;
PortabilityTest test;

void applicationStartup(pE::Engine** engine)
{
	sdk.create();
	sdk.getGameManager().addGameForExecution(&test);
	*engine = &sdk;
}

void applicationUpdate()
{
	sdk.update();
}

void applicationCleanup()
{
	
}