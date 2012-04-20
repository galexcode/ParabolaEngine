#include "ParabolaCore/ASEngine.h"
#include "ParabolaCore/Kinesis.h"

#include <iostream>
using namespace std;

PARABOLA_NAMESPACE_BEGIN

KinesisWorld* KWFactory()
{
	// Initialize the pre-allocated memory by calling the
	// object constructor with the placement-new operator
	return new KinesisWorld();
}

void KWAddRef(void *memory)
{
		
}

void KWRelease(void* memory){

}

/// Exports physics functionality
bool ASEngine::exportKinesis(){
	int r;
	exportReferenceDataType("KinesisBodyActor");

	asEngine->RegisterObjectMethod("KinesisBodyActor", "Vec2f getPosition()", asMETHOD(KinesisBodyActor, getPosition), asCALL_THISCALL);
	asEngine->RegisterObjectMethod("KinesisBodyActor", "void setVelocity(Vec2f)", asMETHOD(KinesisBodyActor, setVelocity), asCALL_THISCALL);
	asEngine->RegisterObjectMethod("KinesisBodyActor", "Vec2f getVelocity()", asMETHOD(KinesisBodyActor, getVelocity), asCALL_THISCALL);
	asEngine->RegisterObjectMethod("KinesisBodyActor", "void setAngle(float)", asMETHOD(KinesisBodyActor, setAngle), asCALL_THISCALL);
	asEngine->RegisterObjectMethod("KinesisBodyActor", "void setFixedRotation(bool)", asMETHOD(KinesisBodyActor, setFixedRotation), asCALL_THISCALL);



	exportReferenceDataType("b2PrismaticJointDef");

	asEngine->RegisterObjectType("KinesisWorld", sizeof(KinesisWorld), asOBJ_REF);
	

	// Registering the factory behaviour
	r = asEngine->RegisterObjectBehaviour("KinesisWorld", asBEHAVE_FACTORY, "KinesisWorld@ f()", asFUNCTION(KWFactory), asCALL_CDECL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectBehaviour("KinesisWorld", asBEHAVE_ADDREF, "void f()", asFUNCTION(KWAddRef), asCALL_CDECL_OBJLAST); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectBehaviour("KinesisWorld", asBEHAVE_RELEASE, "void f()", asFUNCTION(KWRelease), asCALL_CDECL_OBJLAST); if(r < 0)printf("r %d", r);

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