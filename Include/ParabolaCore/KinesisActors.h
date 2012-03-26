#ifndef PARABOLA_KINESISACTORS_H
#define PARABOLA_KINESISACTORS_H

#include "Platform.h"

#include <Box2D/Box2D.h>
#include "Vectors.h"
class b2Body;
PARABOLA_NAMESPACE_BEGIN

/**
	\ingroup Kinesis
	\class KinesisBodyActor
	\brief Represents a body in a simulation
	
	Every body in the kinesis world has a 1:1 relationship with a KinesisBodyActor

*/
class PARABOLA_API KinesisBodyActor{
public:
	

	/// Creates a body actor from a body
	KinesisBodyActor(b2Body *body);
};

PARABOLA_NAMESPACE_END
#endif