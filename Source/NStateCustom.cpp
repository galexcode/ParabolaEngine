#include <ParabolaCore/NStateCustom.h>
#include <ParabolaCore/ASEngine.h>
#include <ParabolaCore/Vectors.h>
#include <ParabolaCore/Renderer.h>
#include <ParabolaCore/ScriptedGameCore.h>

#include "AS/aswrappedcall.h"


#include <iostream>
using namespace std;

PARABOLA_NAMESPACE_BEGIN

State* NStateCustomRefCast(NStateCustom* a)
{
	return refCast<NStateCustom, State>(a);
}

bool registerNStateCustom(ASEngine* engine)
{
	engine->getASEngine()->RegisterObjectType("CustomState", sizeof(NStateCustom), asOBJ_REF);
	
	if(engine->getPortableMode())
	{
		engine->getASEngine()->RegisterObjectBehaviour("CustomState", asBEHAVE_FACTORY, "CustomState@ f()", WRAP_FN(genericFactory<NStateCustom>), asCALL_GENERIC);
		engine->getASEngine()->RegisterObjectBehaviour("CustomState", asBEHAVE_ADDREF, "void f()", WRAP_MFN(NStateCustom, addReference), asCALL_GENERIC);
		engine->getASEngine()->RegisterObjectBehaviour("CustomState", asBEHAVE_RELEASE, "void f()", WRAP_MFN(NStateCustom, removeReference), asCALL_GENERIC);
		engine->getASEngine()->RegisterObjectBehaviour("CustomState", asBEHAVE_IMPLICIT_REF_CAST, "State@ f()", WRAP_OBJ_LAST(NStateCustomRefCast), asCALL_GENERIC);

		engine->getASEngine()->RegisterObjectMethod("CustomState", "void set(const string &in)", WRAP_MFN(NStateCustom, set), asCALL_GENERIC);
		engine->getASEngine()->RegisterObjectMethod("CustomState", "void finish()", WRAP_MFN(NStateCustom, finish), asCALL_GENERIC);
		engine->getASEngine()->RegisterObjectMethod("CustomState", "bool launchBindedState(const string &in)", WRAP_MFN(NStateCustom, launchBindedState), asCALL_GENERIC);
	}
	else
	{
		engine->getASEngine()->RegisterObjectBehaviour("CustomState", asBEHAVE_FACTORY, "CustomState@ f()", asFUNCTION(genericFactory<NStateCustom>), asCALL_CDECL);
		engine->getASEngine()->RegisterObjectBehaviour("CustomState", asBEHAVE_ADDREF, "void f()", asMETHOD(NStateCustom, addReference), asCALL_THISCALL);
		engine->getASEngine()->RegisterObjectBehaviour("CustomState", asBEHAVE_RELEASE, "void f()", asMETHOD(NStateCustom, removeReference), asCALL_THISCALL);
		engine->getASEngine()->RegisterObjectBehaviour("CustomState", asBEHAVE_IMPLICIT_REF_CAST, "State@ f()", asFUNCTION((refCast<NStateCustom,State>)), asCALL_CDECL_OBJLAST);

		engine->getASEngine()->RegisterObjectMethod("CustomState", "void set(const string &in)", asMETHOD(NStateCustom, set), asCALL_THISCALL);
		engine->getASEngine()->RegisterObjectMethod("CustomState", "void finish()", asMETHOD(NStateCustom, finish), asCALL_THISCALL);
		engine->getASEngine()->RegisterObjectMethod("CustomState", "bool launchBindedState(const string &in)", asMETHOD(NStateCustom, launchBindedState), asCALL_THISCALL);

	}

	return true;
};

/// The custom state needed parameters
void NStateCustom::set(const String& file)
{
	m_scriptEngine = new ASEngine();
	m_fileName = file;

	m_scriptEngine->exportStrings();
	m_scriptEngine->exportBasicEngine();
	//m_scripting.exportBasicGameCore();
	m_scriptEngine->exportGraphics();
	m_scriptEngine->exportEvents();
	m_scriptEngine->exportFiles();
	m_scriptEngine->exportMath();
	//registerStateStack(&m_scripting);
	//registerScriptedGameCore(&m_scripting);
	//registerBrowserPreloader(&m_scripting);
	//registerNStateImage(&m_scripting);
	m_scriptEngine->exportReferenceDataType("State");
	registerNStateCustom(m_scriptEngine);

	m_scriptEngine->exportGlobalProperty("CustomState this", this);
	m_script = m_scriptEngine->loadScript(m_fileName);

}

/// Construct the state
NStateCustom::NStateCustom()
	:	State(),
	m_duration(5.f),
	m_elapsedTime(0.f)
{
	cout<<"[NStateImage] Construct"<<endl;
};

/// Destruct the state
NStateCustom::~NStateCustom()
{
	cout<<"[NStateImage] Destruct"<<endl;
};

void NStateCustom::onActivate()
{
	if(m_script)
	{
		m_script->call(m_script->getFunctionIdByName("void onCreate()"));
	}
};


void NStateCustom::setImage(const String &image)
{
	cout<<"[NStateImage] Image: "<<image<<endl;

	m_texture.loadFromFile(image);
	m_sprite.setTexture(m_texture);
	m_sprite.resize(1024,768);
};

/// Delivers an event to the state
/// If returns true, it will be propagated to the rest of the stack
/// Otherwise it will remain under this.
bool NStateCustom::onEvent(Event &event)
{
	if(m_script)
	{
		m_script->prepareMethod("void onEvent(Event@)");
		m_script->prepareMethodArgument(0, &event, ScriptArgumentTypes::Object);
		m_script->call();
	}
	return true;
}

/// Tells the state how much time it should update itself
/// Must return false if updating lesser states is not wanted
/// Returning true will update other stack states.
bool NStateCustom::onUpdate(Time &time)
{
	if(m_script)
	{
		float elapsedTime = time.asSeconds();
		m_script->prepareMethod("void onUpdate(float)");
		m_script->prepareMethodArgument(0, &elapsedTime, ScriptArgumentTypes::Float);
		m_script->call();
	}
	return true;
};

/// Draws the state with the current renderer
/// If returns true, other states in the stack will be rendered
/// Otherwise this state has exclusivity over drawing
bool NStateCustom::onDraw(Renderer *renderer)
{
	// dirty rendering
	if(m_script)
	{
		m_script->prepareMethod("void onRender(Renderer@)");
		m_script->prepareMethodArgument(0, renderer, ScriptArgumentTypes::Object);
		m_script->call();
	}
	return true;
};

PARABOLA_NAMESPACE_END