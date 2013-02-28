#include "ParabolaCore/ReferenceCountable.h"

#include <iostream>
using namespace std;

PARABOLA_NAMESPACE_BEGIN
/// Sets the reference count to 1
RefCountable::RefCountable(){
	refCount = 1;
};

RefCountable::~RefCountable()
{

}

/// For AngelScript, the constructor won't do, need another function to set to 1 the refCount
void RefCountable::factoryConstructor(){
	refCount = 1;
};

/// Adds a reference
void RefCountable::addReference(){
	refCount++;
	cout<<"[RefCount] Add: "<<refCount <<endl;
};

/// Removes a reference and destroys if necessary
void RefCountable::removeReference(){
	cout<<"[RefCount] Released: "<<refCount - 1<<endl;
	if(--refCount == 0){
		delete this;
	}
};

PARABOLA_NAMESPACE_END