#include "ParabolaCore/ASEngine.h"
#include "ParabolaCore/Kinesis.h"

#include <iostream>
using namespace std;

PARABOLA_NAMESPACE_BEGIN

void KWConstructor(void *memory)
{
	// Initialize the pre-allocated memory by calling the
	// object constructor with the placement-new operator
	new(memory) KinesisWorld();

}

void KWDestructor(void *memory)
{
	// Uninitialize the memory by calling the object destructor
	((KinesisWorld*)memory)->~KinesisWorld();
	
}

/// Exports physics functionality
bool ASEngine::exportKinesis(){
	int r;
	exportReferenceDataType("KinesisBodyActor");

	asEngine->RegisterObjectMethod("KinesisBodyActor", "Vec2f getPosition()", asMETHOD(KinesisBodyActor, getPosition), asCALL_THISCALL);
	asEngine->RegisterObjectMethod("KinesisBodyActor", "void setVelocity(Vec2f)", asMETHOD(KinesisBodyActor, setVelocity), asCALL_THISCALL);

	asEngine->RegisterObjectType("KinesisWorld", sizeof(KinesisWorld), asOBJ_VALUE | asOBJ_APP_CLASS_CD);

	
	// Register the behaviours
	r = asEngine->RegisterObjectBehaviour("KinesisWorld", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(KWConstructor), asCALL_CDECL_OBJLAST); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectBehaviour("KinesisWorld", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(KWDestructor), asCALL_CDECL_OBJLAST); if(r < 0)printf("r %d", r);
	
	r = asEngine->RegisterObjectMethod("KinesisWorld", "void update(float)", asMETHOD(KinesisWorld,update), asCALL_THISCALL); if(r < 0)printf("r %d", r);;
	r = asEngine->RegisterObjectMethod("KinesisWorld", "void createStaticBox(float, float, float, float)", asMETHOD(KinesisWorld,CreateStaticBox), asCALL_THISCALL); if(r < 0)printf("r %d", r);;
	r = asEngine->RegisterObjectMethod("KinesisWorld", "KinesisBodyActor@ createDynamicBox(float, float, float, float)", asMETHOD(KinesisWorld,CreateQuickBox), asCALL_THISCALL); if(r < 0)printf("r %d", r);;
	r = asEngine->RegisterObjectMethod("KinesisWorld", "void destroyBody(KinesisBodyActor@)", asMETHOD(KinesisWorld,destroyBodyActor), asCALL_THISCALL); if(r < 0)printf("r %d", r);;
	

	if(exportedRenderer)
		r = asEngine->RegisterObjectMethod("KinesisWorld", "void drawDebug(SceneRenderer& inout)", asMETHOD(KinesisWorld,drawDebug), asCALL_THISCALL); if(r < 0)printf("r %d", r);;

	exportedKinesis = true;
	return true;
}

PARABOLA_NAMESPACE_END