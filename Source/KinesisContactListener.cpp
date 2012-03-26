#include "ParabolaCore/KinesisContactListener.h"
#include <iostream>

PARABOLA_NAMESPACE_BEGIN
	/************************************************************************/
	/* CONTACT LISTENER                                                                     */
	/************************************************************************/
	void KinesisContactListener::BeginContact (b2Contact *contact){
		//std::cout<<"Started a colision"<<std::endl;
	};

	void KinesisContactListener::EndContact(b2Contact *contact){
		//std::cout<<"Ended a colision"<<std::endl;

	};

	void KinesisContactListener::PreSolve(b2Contact *contact, const b2Manifold *oldManifold){

	};

	void KinesisContactListener::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse){

	};
PARABOLA_NAMESPACE_END