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

void KinesisBodyActor::setVelocity(Vec2f velocity){
	myBody->SetLinearVelocity(b2Vec2(velocity.x, velocity.y));
};

PARABOLA_NAMESPACE_END