#include "ParabolaCore/KinesisActors.h"
#include "ParabolaCore/KinesisWorld.h"
#include <Box2D/Box2D.h>

PARABOLA_NAMESPACE_BEGIN

/// Creates a body actor from a body
KinesisBodyActor::KinesisBodyActor(b2Body *body){
	myBody = body;
};

Vec2f KinesisBodyActor::getPosition(){
	return Vec2f(((KinesisWorld*)myBody->GetWorld())->ToPixels(myBody->GetPosition().x), ((KinesisWorld*)myBody->GetWorld())->ToPixels(myBody->GetPosition().y));
};

Vec2f KinesisBodyActor::getVelocity(){
	return Vec2f(myBody->GetLinearVelocity().x, myBody->GetLinearVelocity().y);
};

void KinesisBodyActor::setVelocity(Vec2f velocity){
	myBody->SetLinearVelocity(b2Vec2(velocity.x, velocity.y));
};

/// Set the angle of rotation of the body, it is 0.f by default and is facing right, expressed in radians
void KinesisBodyActor::setAngle(float radians){
	myBody->SetTransform(myBody->GetPosition(), radians);
};

/// Choose whether this body is allowed to rotate
void KinesisBodyActor::setFixedRotation(bool fixedRotation){
	myBody->SetFixedRotation(fixedRotation);
};

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

/// Construct the shape from the fixture
KinesisBodyShape::KinesisBodyShape(b2Fixture* fix){

};

PARABOLA_NAMESPACE_END