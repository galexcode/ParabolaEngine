#ifndef PARABOLA_REFERENCECOUNTABLE_H
#define PARABOLA_REFERENCECOUNTABLE_H

#include "Platform.h"

PARABOLA_NAMESPACE_BEGIN

/**
	\ingroup Foundation
	\class RefCountable
	\brief Made for registering AngelScript objects

	Every object who will be registered in the AngelScript code, 
	needs to be reference counted, so this class was made for utility.

	You can use this class if you wish to make ref counted objects :)
*/
class PARABOLA_API RefCountable{
public:
	/// Sets the reference count to 1
	RefCountable();

	/// For AngelScript, the constructor won't do, need another function to set to 1 the refCount
	void factoryConstructor();

	/// Adds a reference
	void addReference();

	/// Removes a reference and destroys if necessary
	void removeReference();

private:
	int refCount;
};

PARABOLA_NAMESPACE_END

#endif