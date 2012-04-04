#ifndef PARABOLA_PARTICLESYSTEMS_H
#define PARABOLA_PARTICLESYSTEMS_H

#include "Platform.h"
#include "Drawable.h"
#include "Strings.h"
#include "Textures.h"

#include <windows.h>
#include <GL/GL.h>
#include <GL/GLU.h>

#include "SPARK.h"
#include "SPARK_GL.h"

PARABOLA_NAMESPACE_BEGIN
class ParticleSystem;

/**
	\ingroup Graphics
	\class ParticleRenderer
	\brief Wrapper for a SPARK renderer. Scripting convenience.
*/
class PARABOLA_API ParticleRenderer{
public:	
	SPK::Ref<SPK::GL::GLRenderer> myRenderer;
};

/**
	\ingroup Graphics
	\class ParticleTexture
	\brief Wrapper for a SPARK textures. Scripting convenience.
*/
class PARABOLA_API ParticleTexture{
public:
	bool loadTexture(const String &path);
	GLuint myTextureID;
};

/**
	\ingroup Graphics
	\class ParticleModifier
	\brief Wrapper for a SPARK modifiers. Scripting convenience.
*/
class PARABOLA_API ParticleModifier{
public:
	SPK::Ref<SPK::Modifier> myModifier;
};

/**
	\ingroup Graphics
	\class ParticleZone
	\brief Wrapper for a SPARK zones. Scripting convenience.
*/
class PARABOLA_API ParticleZone{
public:
	SPK::Ref<SPK::Zone> myZone;
};

/**
	\ingroup Graphics
	\class ParticleEmitter
	\brief Wrapper for a SPARK emitters. Scripting convenience.
*/
class PARABOLA_API ParticleEmitter{
public:
	SPK::Ref<SPK::Emitter> myEmitter;
};

/**
	\ingroup Graphics
	\class ParticleGroup
	\brief Wrapper for a SPARK groups. Scripting convenience.
*/
class PARABOLA_API ParticleGroup{
public:
	ParticleGroup(SPK::Ref<SPK::Group> group, ParticleSystem *parent){
		myGroup = group;
		myParent = parent;
	}

	/// Just a test - creates a funny effect
	void defaultGroup1();

	String getName(){
		return myGroup->getName();
	}	

	void addEmitter(ParticleEmitter &emitter){
		myGroup->addEmitter(emitter.myEmitter);
	}

	void addModifier(ParticleModifier &modifier){
		myGroup->addModifier(modifier.myModifier);
	}



	void setLifeTime(float minLife, float maxLife){
		if(minLife < 0 || maxLife < 0)
			myGroup->setImmortal(true);
		else
			myGroup->setLifeTime(minLife, maxLife);
	}

	void setRenderer(ParticleRenderer &pRenderer){
		myGroup->setRenderer(pRenderer.myRenderer);
	}

	SPK::Ref<SPK::Group> myGroup;
	ParticleSystem *myParent;
};

/**
	\ingroup Graphics
	\class ParticleSystem
	\brief A particle system, to provide effects that can be rendered.

	...
*/
class PARABOLA_API ParticleSystem{
public:
	/// Creates an empty Particle System
	ParticleSystem();
		
	/// Overload of the assignment operator, for copying systems
	ParticleSystem& operator=(const ParticleSystem &other);

	/// Adds a new group to the system
	ParticleGroup& addGroup(const String &name, int capacity);

	/// Get the name of this particle system
	String getName();

	ParticleTexture& createTexture(const String &name, const String &path){
		ParticleTexture *pRend = new ParticleTexture();
		pRend->loadTexture(path);
		myTextures[name] = pRend;
		return *pRend;
	}

	/// Creates a point renderer directly
	ParticleRenderer& createPointRenderer(const String &name, float pointSize);

	ParticleZone& createSphereZone(const String &name, float x, float y, float z, float radius){
		ParticleZone *pRend = new ParticleZone();
		pRend->myZone = SPK::Sphere::create(SPK::Vector3D(x,y,z), radius);
		myZones[name] = pRend;
		return *pRend;
	}

	ParticleModifier& createGravityModifier(const String &name, float x, float y, float z){
		ParticleModifier *pRend = new ParticleModifier();
		pRend->myModifier = SPK::Gravity::create(SPK::Vector3D(x,y,z));
		myModifiers[name] = pRend;
		return *pRend;
	}

	ParticleEmitter& createSphericEmitter(const String &name, float direction_x, float direction_y, float direction_z,
											float angleMin, float angleMax, ParticleZone &zone,
												bool full, int tank, float flow, float forceMin, float forceMax){

		ParticleEmitter *pRend = new ParticleEmitter();
		pRend->myEmitter = SPK::SphericEmitter::create(SPK::Vector3D(direction_x, direction_y, direction_z),angleMin, angleMax, zone.myZone , full, tank, flow, forceMin, forceMax);
		
		myEmitters[name] = pRend;
		return *pRend;
	}




	// Static, default systems
	/// A simple system
	void createBasicSystem();

	SPK::Ref<SPK::Sphere> mySphere;

	void render();

	void UpdateSystem(float DeltaTime);

	void dummy(){}

		//void Render(sf::RenderTarget &renderTarget, sf::Renderer &renderer) const;
	SPK::Ref<SPK::System> sparkSystem;
	SPK::Ref<SPK::GL::GLQuadRenderer> renderer;

	String myName;

	std::map<String, ParticleRenderer*> myRenderers;
	std::map<String, ParticleZone*> myZones;
	std::map<String, ParticleEmitter*> myEmitters;
	std::map<String, ParticleTexture*> myTextures;
	std::map<String, ParticleModifier*> myModifiers;
};

PARABOLA_NAMESPACE_END
#endif