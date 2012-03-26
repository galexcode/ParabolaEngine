#include "ParabolaCore/ASEngine.h"
#include "ParabolaCore/ParticleSystem.h"
#include "ParabolaCore/FileSystem.h"

#include <iostream>
using namespace std;

PARABOLA_NAMESPACE_BEGIN
/// Exports everything necessary to make this engine a particle loader
void ASEngine::activateParticleLoaderProfile(){
	exportStrings();

	asEngine->RegisterObjectType("ParticleEffect", sizeof(ParticleSystem), asOBJ_REF);
	asEngine->RegisterObjectType("ParticleGroup", sizeof(ParticleGroup), asOBJ_REF);
	asEngine->RegisterObjectType("ParticleRenderer", sizeof(ParticleRenderer), asOBJ_REF);
	asEngine->RegisterObjectType("ParticleZone", sizeof(ParticleZone), asOBJ_REF);
	asEngine->RegisterObjectType("ParticleEmitter", sizeof(ParticleEmitter), asOBJ_REF);
	asEngine->RegisterObjectType("ParticleTexture", sizeof(ParticleTexture), asOBJ_REF);
	asEngine->RegisterObjectType("ParticleModifier", sizeof(ParticleModifier), asOBJ_REF);


	int r;
	r = asEngine->RegisterObjectBehaviour("ParticleEffect", asBEHAVE_ADDREF, "void f()", asMETHOD(ParticleSystem,dummy), asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectBehaviour("ParticleEffect", asBEHAVE_RELEASE, "void f()", asMETHOD(ParticleSystem,dummy), asCALL_THISCALL); if(r < 0)printf("r %d", r);

	r = asEngine->RegisterObjectBehaviour("ParticleGroup", asBEHAVE_ADDREF, "void f()", asMETHOD(ParticleGroup,dummy), asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectBehaviour("ParticleGroup", asBEHAVE_RELEASE, "void f()", asMETHOD(ParticleGroup,dummy), asCALL_THISCALL); if(r < 0)printf("r %d", r);
	
	r = asEngine->RegisterObjectBehaviour("ParticleRenderer", asBEHAVE_ADDREF, "void f()", asMETHOD(ParticleRenderer,dummy), asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectBehaviour("ParticleRenderer", asBEHAVE_RELEASE, "void f()", asMETHOD(ParticleRenderer,dummy), asCALL_THISCALL); if(r < 0)printf("r %d", r);

	r = asEngine->RegisterObjectBehaviour("ParticleZone", asBEHAVE_ADDREF, "void f()", asMETHOD(ParticleZone,dummy), asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectBehaviour("ParticleZone", asBEHAVE_RELEASE, "void f()", asMETHOD(ParticleZone,dummy), asCALL_THISCALL); if(r < 0)printf("r %d", r);
	
	r = asEngine->RegisterObjectBehaviour("ParticleEmitter", asBEHAVE_ADDREF, "void f()", asMETHOD(ParticleEmitter,dummy), asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectBehaviour("ParticleEmitter", asBEHAVE_RELEASE, "void f()", asMETHOD(ParticleEmitter,dummy), asCALL_THISCALL); if(r < 0)printf("r %d", r);
	
	r = asEngine->RegisterObjectBehaviour("ParticleTexture", asBEHAVE_ADDREF, "void f()", asMETHOD(ParticleTexture,dummy), asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectBehaviour("ParticleTexture", asBEHAVE_RELEASE, "void f()", asMETHOD(ParticleTexture,dummy), asCALL_THISCALL); if(r < 0)printf("r %d", r);

	r = asEngine->RegisterObjectBehaviour("ParticleModifier", asBEHAVE_ADDREF, "void f()", asMETHOD(ParticleModifier,dummy), asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectBehaviour("ParticleModifier", asBEHAVE_RELEASE, "void f()", asMETHOD(ParticleModifier,dummy), asCALL_THISCALL); if(r < 0)printf("r %d", r);


	//////////////////////////////////////////////////////////////////////////
	// Methods


	r = asEngine->RegisterObjectMethod("ParticleEffect", "string getName()", asMETHOD(ParticleSystem, getName) , asCALL_THISCALL);if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("ParticleEffect", "ParticleGroup@ addGroup(const string &in, int capacity)", asMETHOD(ParticleSystem, addGroup) , asCALL_THISCALL);if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("ParticleEffect", "ParticleRenderer@ createPointRenderer(const string &in, int pointSize)", asMETHOD(ParticleSystem, createPointRenderer) , asCALL_THISCALL);if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("ParticleEffect", "ParticleZone@ createSphereZone(const string &in, float x, float y, float z, float radius)", asMETHOD(ParticleSystem, createSphereZone) , asCALL_THISCALL);if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("ParticleEffect", "ParticleEmitter@ createSphericEmitter(const string &in, float direction_x, float direction_y, float direction_z, float angleMin, float angleMax, ParticleZone &zone, bool full, int tank, float flow, float forceMin, float forceMax)", asMETHOD(ParticleSystem, createSphericEmitter) , asCALL_THISCALL);if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("ParticleEffect", "ParticleTexture@ createTexture(const string &in, const string &in)", asMETHOD(ParticleSystem, createTexture) , asCALL_THISCALL);if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("ParticleEffect", "ParticleModifier@ createGravityModifier(const string &in, float x, float y, float z)", asMETHOD(ParticleSystem, createGravityModifier) , asCALL_THISCALL);if(r < 0)printf("r %d", r);
	
	
	r = asEngine->RegisterObjectMethod("ParticleGroup", "string getName()", asMETHOD(ParticleGroup, getName) , asCALL_THISCALL);if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("ParticleGroup", "void setRenderer(ParticleRenderer &in)", asMETHOD(ParticleGroup, setRenderer) , asCALL_THISCALL);if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("ParticleGroup", "void setLifeTime(float min, float max)", asMETHOD(ParticleGroup, setLifeTime) , asCALL_THISCALL);if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("ParticleGroup", "void addEmitter(ParticleEmitter &inout)", asMETHOD(ParticleGroup, addEmitter) , asCALL_THISCALL);if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("ParticleGroup", "void addModifier(ParticleModifier &inout)", asMETHOD(ParticleGroup, addModifier) , asCALL_THISCALL);if(r < 0)printf("r %d", r);






	r = asEngine->RegisterObjectMethod("ParticleGroup", "void teste()", asMETHOD(ParticleGroup, defaultGroup1) , asCALL_THISCALL);if(r < 0)printf("r %d", r);

	
};


/// Prepares an AS engine with particle systems support, creates one system and returns it
ParticleSystem* ASEngine::loadParticleSystem(const String &scriptName, ParticleSystem *pSystem, bool byteCode){
	if(pSystem == NULL){
		pSystem = new ParticleSystem();
	}

	if(true){
		ASEngine as;
		as.activateParticleLoaderProfile();

		ASScript* script = as.loadScript(scriptName);
		if(script){
			script->prepareMethod("void create(ParticleEffect @effect)");
			script->prepareMethodArgument(0, pSystem, ScriptArgumentTypes::Object);

			if(script->call()){
				cout<<"Particle system loaded."<<endl;
			}
		}
	}
	else{
		cout<<"Could not load the particle system."<<endl;
	}

	return pSystem;	
};

PARABOLA_NAMESPACE_END