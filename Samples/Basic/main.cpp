/*#define ANDROID_PACKAGE_NAME com_parabolaenginesamples_basic
#define ANDROID_ACTIVITY_NAME BasicSample
#include <ParabolaCore/ParabolaMain.h>
#include <ParabolaCore/Engine.h>
//#include "Basic.h"

using namespace pE;
using namespace pE;

using namespace std;
using namespace std;
using namespace std;
using namespace std;
using namespace std;
using namespace std;
using namespace std;
Engine *sdk;

void applicationStartup(){
	sdk = new Engine();
	sdk->create();
	//sdk->getGameManager().addGameForExecution(new BasicSample());
} 

void applicationUpdate(){ 
	sdk->update();
}

void applicationCleanup(){
	delete sdk;
}*/

#include <ParabolaCore/Engine.h>
using namespace pE;
using namespace pE;