#include "ParabolaCore/ASEngine.h"
#include "ParabolaCore/SceneRenderer.h"
#include "ParabolaCore/Sprite.h"

PARABOLA_NAMESPACE_BEGIN

void SprConstructor(void *memory)
{
	// Initialize the pre-allocated memory by calling the
	// object constructor with the placement-new operator
	new(memory) Sprite();
}

void SprDestructor(void *memory)
{
	// Uninitialize the memory by calling the object destructor
	((Sprite*)memory)->~Sprite();
}

void dummyref(void*){

}

Sprite& dummyfac(){
	return *new Sprite();
}

/// Exports the renderer and a few more things
bool ASEngine::exportBasicGraphics(){
	int r;
	/// Export drawable
	exportReferenceDataType("Drawable");
	exportReferenceDataType("Texture");

	/// Export sprites
	asEngine->RegisterObjectType("Sprite", sizeof(Sprite), asOBJ_REF);	
	// Register the behaviours
	//r = asEngine->RegisterObjectBehaviour("Sprite", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(SprConstructor), asCALL_CDECL_OBJLAST); if(r < 0)printf("r %d", r);
//	r = asEngine->RegisterObjectBehaviour("Sprite", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(SprDestructor), asCALL_CDECL_OBJLAST); if(r < 0)printf("r %d", r);
	
	// Registering the factory behaviour
	r = asEngine->RegisterObjectBehaviour("Sprite", asBEHAVE_FACTORY, "Sprite@ f()", asFUNCTION(dummyfac), asCALL_CDECL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectBehaviour("Sprite", asBEHAVE_ADDREF, "void f()", asFUNCTION(dummyref), asCALL_CDECL_OBJLAST); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectBehaviour("Sprite", asBEHAVE_RELEASE, "void f()", asFUNCTION(dummyref), asCALL_CDECL_OBJLAST); if(r < 0)printf("r %d", r);

	r = asEngine->RegisterObjectMethod("Sprite", "void setTexture(Texture@, bool)", asMETHOD(Sprite, setTexture) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("Sprite", "void setCenterPosition(Vec2f)", asMETHODPR(Sprite, setCenterPosition, (Vec2f), void) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("Sprite", "void setPosition(Vec2f)", asMETHODPR(Sprite, setPosition, (Vec2f), void) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("Sprite", "void setPosition(float x, float y)", asMETHODPR(Sprite, setPosition, (float, float), void) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("Sprite", "void resize(float x, float y)", asMETHODPR(Sprite, resize, (float,float), void) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("Sprite", "bool containsPoint(Vec2f)", asMETHODPR(Sprite, containsPoint, (Vec2f), bool) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("Sprite", "bool containsPoint(float x, float y)", asMETHODPR(Sprite, containsPoint, (float, float), bool) , asCALL_THISCALL); if(r < 0)printf("r %d", r);

	/// Export renderer
	exportReferenceDataType("SceneRenderer");
	asEngine->RegisterObjectMethod("SceneRenderer", "void drawDebugText(const string &in, float, float)", asMETHOD(SceneRenderer, drawDebugText), asCALL_THISCALL);
	asEngine->RegisterObjectMethod("SceneRenderer", "void drawDebugCircle(float, float, float)", asMETHOD(SceneRenderer, drawDebugCircle), asCALL_THISCALL);
	asEngine->RegisterObjectMethod("SceneRenderer", "void activate()", asMETHOD(SceneRenderer, activateRenderTarget), asCALL_THISCALL);
	asEngine->RegisterObjectMethod("SceneRenderer", "void draw(Drawable& inout)", asMETHODPR(SceneRenderer, draw, (Drawable&), void), asCALL_THISCALL);
	asEngine->RegisterObjectMethod("SceneRenderer", "void draw(Sprite@)", asMETHODPR(SceneRenderer, draw, (Drawable&), void), asCALL_THISCALL);


	exportedRenderer = true;

	return true;
};

PARABOLA_NAMESPACE_END