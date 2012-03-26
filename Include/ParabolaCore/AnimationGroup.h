#ifndef ANIMATIONGROUP_H
#define ANIMATIONGROUP_H

#include "Platform.h"
#include "Animation.h"
#include <vector>
using namespace std;

namespace pE{
	/**
		\class AnimationGroup
		\brief Base class for animation grouping utilities.


	*/
	class PARABOLA_API AnimationGroup : public AbstractAnimation{
	public:

	private:
		vector<AbstractAnimation*> Animations;
	};
};

#endif