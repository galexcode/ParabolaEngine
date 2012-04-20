#include "ParabolaCore/ASEngine.h"
#include "ParabolaCore/SceneRenderer.h"
#include "ParabolaCore/Sprite.h"
#include "ParabolaCore/SpriteExt.h"
#include "ParabolaCore/Textures.h"
#include "ParabolaCore/RocketContext.h"

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

SpriteExt& SpriteExtFactory(){
	return *new SpriteExt();
}


View& ViewFactory(){
	return *new View();
}

void ViewFactoryAdd(View *v){

}

void ViewFactoryRelease(View *v){

}

/// Exports the renderer and a few more things
bool ASEngine::exportBasicGraphics(){
	int r;
	/// Export drawable
	exportReferenceDataType("Drawable");

	exportReferenceDataType("Texture");
	r = asEngine->RegisterObjectMethod("Texture", "Vec2f getSize()", asMETHOD(Texture, getSize) , asCALL_THISCALL); if(r < 0)printf("r %d", r);


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
	r = asEngine->RegisterObjectMethod("Sprite", "void flipVertical()", asMETHOD(Sprite, flipVertical) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("Sprite", "void flipHorizontal()", asMETHOD(Sprite, flipHorizontal) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("Sprite", "bool isFlippedHorizontally()", asMETHOD(Sprite, isFlippedHorizontally) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("Sprite", "bool isFlippedVertically()", asMETHOD(Sprite, isFlippedVertically) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("Sprite", "void setOrigin(float, float)", asMETHODPR(Sprite, setOrigin, (float, float), void) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	//r = asEngine->RegisterObjectMethod("Sprite", "void setOrigin(Vec2f)", asMETHOD(Sprite, isFlippedVertically) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("Sprite", "void setRotation(float)", asMETHODPR(Sprite, setRotation, (float), void) , asCALL_THISCALL); if(r < 0)printf("r %d", r);

	asEngine->RegisterObjectType("SpriteExt", sizeof(SpriteExt), asOBJ_REF);	
	// Registering the factory behaviour
	r = asEngine->RegisterObjectBehaviour("SpriteExt", asBEHAVE_FACTORY, "SpriteExt@ f()", asFUNCTION(SpriteExtFactory), asCALL_CDECL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectBehaviour("SpriteExt", asBEHAVE_ADDREF, "void f()", asFUNCTION(dummyref), asCALL_CDECL_OBJLAST); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectBehaviour("SpriteExt", asBEHAVE_RELEASE, "void f()", asFUNCTION(dummyref), asCALL_CDECL_OBJLAST); if(r < 0)printf("r %d", r);

	r = asEngine->RegisterObjectMethod("SpriteExt", "bool loadFromTextFile(const string &in)", asMETHODPR(SpriteExt, loadFromTextFile, (const String&),bool) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("SpriteExt", "void update(float)", asMETHOD(SpriteExt, update) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("SpriteExt", "void triggerAnimation(const string &in)", asMETHOD(SpriteExt, triggerAnimation) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("SpriteExt", "void resize(float,float)", asMETHOD(SpriteExt, resize) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("SpriteExt", "void setPosition(Vec2f)", asMETHODPR(SpriteExt, setPosition, (Vec2f), void) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("SpriteExt", "void setPosition(float,float)", asMETHODPR(SpriteExt, setPosition, (float,float), void) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("SpriteExt", "void setOrigin(Vec2f)", asMETHODPR(SpriteExt, setOrigin, (Vec2f), void) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("SpriteExt", "void setOrigin(float,float)", asMETHODPR(SpriteExt, setOrigin, (float,float), void) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("SpriteExt", "void flip(bool,bool)", asMETHOD(SpriteExt, flip) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("SpriteExt", "bool getFlippedX()", asMETHOD(SpriteExt, getFlippedX) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("SpriteExt", "bool getFlippedY()", asMETHOD(SpriteExt, getFlippedY) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("SpriteExt", "bool containsPoint(float,float)", asMETHODPR(SpriteExt, containsPoint, (float,float), bool) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("SpriteExt", "bool containsPoint(Vec2f)", asMETHODPR(SpriteExt, containsPoint, (Vec2f), bool) , asCALL_THISCALL); if(r < 0)printf("r %d", r);


	asEngine->RegisterEnum("ViewportPreset");
	asEngine->RegisterEnumValue("ViewportPreset", "TopLeftQuarter", TopLeftQuarter);
	asEngine->RegisterEnumValue("ViewportPreset", "TopRightQuarter", TopRightQuarter);
	asEngine->RegisterEnumValue("ViewportPreset", "BottomLeftQuarter", BottomLeftQuarter);
	asEngine->RegisterEnumValue("ViewportPreset", "BottomRightQuarter", BottomRightQuarter);
	asEngine->RegisterEnumValue("ViewportPreset", "TopHalf", TopHalf);
	asEngine->RegisterEnumValue("ViewportPreset", "BottomHalf", BottomHalf);
	asEngine->RegisterEnumValue("ViewportPreset", "LeftHalf", LeftHalf);
	asEngine->RegisterEnumValue("ViewportPreset", "RightHalf", RightHalf);
	asEngine->RegisterEnumValue("ViewportPreset", "WideScreen", WideScreen);

	asEngine->RegisterObjectType("View", sizeof(View), asOBJ_REF);

	// Registering the factory behaviour
	r = asEngine->RegisterObjectBehaviour("View", asBEHAVE_FACTORY, "View@ f()", asFUNCTION(ViewFactory), asCALL_CDECL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectBehaviour("View", asBEHAVE_ADDREF, "void f()", asFUNCTION(ViewFactoryAdd), asCALL_CDECL_OBJLAST); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectBehaviour("View", asBEHAVE_RELEASE, "void f()", asFUNCTION(ViewFactoryRelease), asCALL_CDECL_OBJLAST); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("View", "void setCenter(Vec2f)", asMETHODPR(View, setCenter, (Vec2f), void) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("View", "void setCenter(float, float)", asMETHODPR(View, setCenter, (float, float), void) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("View", "Vec2f getCenter()", asMETHOD(View, getCenter) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("View", "void move(float, float)", asMETHODPR(View, move, (float, float), void) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("View", "void setSize(float, float)", asMETHODPR(View, setSize, (float, float), void) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("View", "void setRotation(float)", asMETHOD(View, setRotation) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("View", "float getRotation()", asMETHOD(View, getRotation) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("View", "void rotate(float)", asMETHOD(View, rotate) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("View", "void zoom(float)", asMETHOD(View, zoom) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("View", "void setRect(float,float,float,float)", asMETHOD(View, setRect) , asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("View", "void setViewportPreset(int)", asMETHOD(View, setViewportPreset) , asCALL_THISCALL); if(r < 0)printf("r %d", r);


	/// Export renderer
	exportReferenceDataType("SceneRenderer");
	asEngine->RegisterObjectMethod("SceneRenderer", "void drawDebugText(const string &in, float, float)", asMETHOD(SceneRenderer, drawDebugText), asCALL_THISCALL);
	asEngine->RegisterObjectMethod("SceneRenderer", "void drawDebugCircle(float, float, float)", asMETHOD(SceneRenderer, drawDebugCircle), asCALL_THISCALL);
	asEngine->RegisterObjectMethod("SceneRenderer", "void activate()", asMETHOD(SceneRenderer, activateRenderTarget), asCALL_THISCALL);
	asEngine->RegisterObjectMethod("SceneRenderer", "void draw(Drawable& inout)", asMETHODPR(SceneRenderer, draw, (Drawable&), void), asCALL_THISCALL);
	asEngine->RegisterObjectMethod("SceneRenderer", "void draw(Sprite@)", asMETHODPR(SceneRenderer, draw, (Drawable&), void), asCALL_THISCALL);
	asEngine->RegisterObjectMethod("SceneRenderer", "void draw(SpriteExt@)", asMETHODPR(SceneRenderer, draw, (Drawable&), void), asCALL_THISCALL);
	if(exportedParticles)
		asEngine->RegisterObjectMethod("SceneRenderer", "void draw(ParticleEffect@)", asMETHODPR(SceneRenderer, draw, (Drawable&), void), asCALL_THISCALL);

	asEngine->RegisterObjectMethod("SceneRenderer", "void setView(View@)", asMETHOD(SceneRenderer, setView), asCALL_THISCALL);
	asEngine->RegisterObjectMethod("SceneRenderer", "Vec2f convertCoords(Vec2f)", asMETHODPR(SceneRenderer, convertLocalCoordinates, (Vec2f), Vec2f), asCALL_THISCALL);
	asEngine->RegisterObjectMethod("SceneRenderer", "Vec2f convertCoords(Vec2f, View@)", asMETHODPR(SceneRenderer, convertLocalCoordinates, (Vec2f, View&), Vec2f), asCALL_THISCALL);



	exportedRenderer = true;

	return true;
};

/// Exports access to rocket ui
bool ASEngine::exportRocketUi(){
	if(exportedRocket)return true;

	exportReferenceDataType("RocketContext");
	exportReferenceDataType("RocketDocument");
	exportReferenceDataType("RocketElement");
	exportReferenceDataType("RocketEvent");


	if(exportedRenderer){
		asEngine->RegisterGlobalFunction("RocketContext@ createRocketContext(string, Vec2i)", asFUNCTION(RocketContext::create), asCALL_CDECL);
		asEngine->RegisterObjectMethod("RocketContext", "void update()", asMETHOD(RocketContext, update), asCALL_THISCALL);
		asEngine->RegisterObjectMethod("RocketContext", "void showDocument(string)", asMETHOD(RocketContext, showDocument), asCALL_THISCALL);
		asEngine->RegisterObjectMethod("RocketContext", "void loadFont(string)", asMETHOD(RocketContext, loadFont), asCALL_THISCALL);

		asEngine->RegisterObjectMethod("RocketEvent", "RocketElement@ currentElement()", asMETHOD(Rocket::Core::Event, GetCurrentElement), asCALL_THISCALL);


		asEngine->RegisterObjectMethod("SceneRenderer", "void draw(RocketContext@)", asMETHODPR(SceneRenderer, draw, (RocketContext*), void), asCALL_THISCALL);

	}

	exportedRocket = true;
	return true;
};

/// Exports as rocket scripting tools
bool ASEngine::exportRocketScripting(RocketDocument* document){
	exportRocketUi();
	if(exportedRocketInternal)return true;

	getASEngine()->RegisterObjectMethod("RocketDocument", "RocketContext@ getContext()", asMETHOD(RocketDocument, GetContext), asCALL_THISCALL);
	getASEngine()->RegisterObjectMethod("RocketDocument", "void hide()", asMETHOD(RocketDocument, Hide), asCALL_THISCALL);


	getASEngine()->RegisterObjectMethod("RocketDocument", "void say(const string& in)", asMETHOD(RocketDocument, say), asCALL_THISCALL);
	getASEngine()->RegisterObjectMethod("RocketDocument", "RocketElement@ getElementById(const string &in)", asMETHOD(RocketDocument, getElementById), asCALL_THISCALL);

	getASEngine()->RegisterObjectMethod("RocketElement", "string getInnerRML()", asMETHOD(RocketElement, getInnerRML), asCALL_THISCALL);
	getASEngine()->RegisterObjectMethod("RocketElement", "void setProperty(const string &in, const string& in)", asMETHOD(RocketElement, setProperty), asCALL_THISCALL);


	exportGlobalProperty("RocketDocument document", document);


	exportedRocketInternal = true;
	return true;
};

PARABOLA_NAMESPACE_END