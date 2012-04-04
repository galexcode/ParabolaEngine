#include "ParabolaCore/ParticleSystem.h"

#include <iostream>
using namespace std;

#include "SPARK.h"
#include "SPARK_GL.h"

PARABOLA_NAMESPACE_BEGIN
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////// TEXTURE

bool ParticleTexture::loadTexture(const String &path){

	GLuint texture = 0;
	{
		Image image;
		if (!image.loadFromFile(path))
			return false;

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, image.getSize().x, image.getSize().y, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	}

	myTextureID = texture;
	return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////// SYSTEM

ParticleSystem::ParticleSystem(){
	SPK::System::setClampStep(true,0.1f);			// clamp the step to 100 ms
	SPK::System::useAdaptiveStep(0.001f,0.01f);
	sparkSystem = SPK::System::create(true);
};

/// Overload of the assignment operator, for copying systems
ParticleSystem& ParticleSystem::operator=(const ParticleSystem &other){
	sparkSystem = other.sparkSystem;
	return *this;
};

/// Adds a new group to the system
ParticleGroup& ParticleSystem::addGroup(const String &name, int capacity){
	SPK::Ref<SPK::Group> group = sparkSystem->createGroup(capacity);
	group->setName(name);
	return *(new ParticleGroup(group, this));
};

String ParticleSystem::getName(){
	return myName;
}

ParticleRenderer& ParticleSystem::createPointRenderer(const String &name, float pointSize){
	ParticleRenderer *pRend = new ParticleRenderer();
	pRend->myRenderer = SPK::GL::GLPointRenderer::create(pointSize);
	myRenderers[name] = pRend;
	return *pRend;
}


/// A simple system
void ParticleSystem::createBasicSystem(){
	renderer = SPK::GL::GLQuadRenderer::create(5,5);

	SPK::Ref<SPK::Group> effectgroup = sparkSystem->createGroup(4000);

	effectgroup->setName("Cool");
	SPK::Ref<SPK::GL::GLPointRenderer> rn = SPK::GL::GLPointRenderer::create(9);	
	rn->setType(SPK::POINT_TYPE_CIRCLE);
	rn->setBlendMode(SPK::BLEND_MODE_ADD);
	effectgroup->setRenderer(rn);
	//effectgroup->setRenderer(SPK::GL::GLLineRenderer::create(10, 5));

	mySphere = SPK::Sphere::create(SPK::Vector3D(300.f,300.f,0.f),4.0f);

	//effectgroup->setRenderer(renderer);
	effectgroup->setLifeTime(0.9f,1.7f);
	effectgroup->setColorInterpolator(SPK::ColorRandomInterpolator::create(SPK::Color(0,0,0,255),SPK::Color(0,15,0,255),SPK::Color(0,30,40,255),SPK::Color(50,0,0,255)));
	effectgroup->addEmitter(SPK::SphericEmitter::create(SPK::Vector3D(1.0f,0.0f,0.0f),0.0f,2*3.14159f,mySphere,true,-1,3000.0f,70.2f,100.5f));

	effectgroup->addModifier(SPK::Gravity::create(SPK::Vector3D(0.0f, -1,0.0f)));
	//effectgroup->addParticles(100, SPK::Vector3D(200,200,0), SPK::Vector3D(0,0,0));
	//effectgroup->addParticles(100, SPK::Vector3D(200,200,0), SPK::Vector3D(20,30,0));

	//effectgroup->addParticles(100, SPK::Vector3D(500,200,0), SPK::Vector3D(200,30,0));


};


void ParticleSystem::render(){
	SPK::GL::GLRenderer::saveGLStates();
	glDisableClientState(GL_COLOR_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	sparkSystem->renderParticles();
	SPK::GL::GLRenderer::restoreGLStates();
};	
	

	
void ParticleSystem::UpdateSystem(float DeltaTime){
	sparkSystem->updateParticles(DeltaTime);
};



//////////////////////////////////////////////////////////////////////////

void ParticleGroup::defaultGroup1(){

	ParticleTexture *tt = new ParticleTexture();
	if(!tt->loadTexture("part.png"))cout<<"COULD NOT LOAD TEXTURE"<<endl;

	SPK::Ref<SPK::GL::GLPointRenderer> rn = SPK::GL::GLPointRenderer::create(50);
	rn->setTexture(tt->myTextureID);

	rn->setBlendMode(SPK::BLEND_MODE_ADD);
	//rn->setAlphaTestThreshold()
	rn->setType(SPK::POINT_TYPE_SPRITE);
	myGroup->setRenderer(rn);
	//effectgroup->setRenderer(SPK::GL::GLLineRenderer::create(10, 5));
	
	//mySphere = SPK::Sphere::create(SPK::Vector3D(300.f,300.f,0.f),4.0f);

	myParent->mySphere = SPK::Sphere::create(SPK::Vector3D(500.f,700.f,0.f),4.0f);

	//effectgroup->setRenderer(renderer);
	myGroup->setLifeTime(3,6);
	myGroup->setColorInterpolator(SPK::ColorRandomInterpolator::create(SPK::Color(255,0,0,255),SPK::Color(255,50,0,255),SPK::Color(255,30,40,255),SPK::Color(255,0,160,255)));
	myGroup->addEmitter(SPK::SphericEmitter::create(SPK::Vector3D(1.0f,0.0f,0.0f),0.0f,2*3.14159f,myParent->mySphere,true,-1,300.0f,70.2f,100.5f));
	myGroup->setParamInterpolator(SPK::PARAM_TEXTURE_INDEX,SPK::FloatRandomInitializer::create(0.0f,4.0f));
	myGroup->setParamInterpolator(SPK::PARAM_ROTATION_SPEED,SPK::FloatRandomInitializer::create(-0.1f,1.0f));
	myGroup->setParamInterpolator(SPK::PARAM_ANGLE,SPK::FloatRandomInitializer::create(0.0f,2.0f * 3.14159f));
	myGroup->addModifier(SPK::Gravity::create(SPK::Vector3D(0.0f, -1,0.0f)));
	myGroup->setColorInterpolator(SPK::ColorSimpleInterpolator::create(0xFF802080,0xFF000000));
	myGroup->setRadius(30.f);
	myGroup->setPhysicalRadius(1);
	myGroup->addModifier(SPK::Rotator::create());
	myGroup->setGraphicalRadius(50);
	//myGroup->set

	ParticleTexture *tt2 = new ParticleTexture();
	if(!tt2->loadTexture("explosion.png"))cout<<"COULD NOT LOAD TEXTURE"<<endl;

	SPK::Ref<SPK::GL::GLQuadRenderer> rnquad = SPK::GL::GLQuadRenderer::create();
	rnquad->setTexture(tt2->myTextureID);
	rnquad->setAtlasDimensions(2,2);
	rnquad->setBlendMode(SPK::BLEND_MODE_NONE);
	rnquad->setTexturingMode(SPK::TEXTURE_MODE_2D);
	rnquad->enableBlending(true);
	rnquad->enableRenderingOption(SPK::RENDERING_OPTION_DEPTH_WRITE, false);
	//rnquad->setOrientation(SPK::OrientationPreset::);
	//myGroup->setRenderer(rnquad);

	SPK::Ref<SPK::GL::GLQuadRenderer> rnquad2 = SPK::GL::GLQuadRenderer::create(10,10);
	//rnquad2->setBlendMode(SPK::BLEND_MODE_ADD);
	rnquad2->enableRenderingOption(SPK::RENDERING_OPTION_DEPTH_WRITE,false);
	rnquad2->setTexture(tt2->myTextureID);
	rnquad2->setTexturingMode(SPK::TEXTURE_MODE_2D);
	rnquad2->setAtlasDimensions(2,2);
	rnquad2->setScale(20,20);
//	rnquad2->
	//myGroup->setRenderer(rnquad2);

	
	//myGroup->set
}


PARABOLA_NAMESPACE_END