#ifndef PARABOLA_ROCKETANIMATIONCONTROLLER_H
#define PARABOLA_ROCKETANIMATIONCONTROLLER_H

#include "Platform.h"
#include "RocketContext.h"
#include "RocketDocument.h"
#include "Animation.h"

PARABOLA_NAMESPACE_BEGIN

/**
	\ingroup Animation
	\class RocketAnimationController
	\brief Makes any rocket element animable by the engine
*/
class PARABOLA_API RocketAnimationController : public Animable{
public:
	RocketAnimationController(){
		myElement = NULL;
	}
	RocketAnimationController(RocketElement* element){
		myElement = element;
	}


	void animable_set_position(float x, float y){
		if(myElement){
			myElement->SetProperty("left", String(String::number(x) + "px").c_str());
			myElement->SetProperty("top", String(String::number(y) + "px").c_str());
		}
	}

	Vec2f animable_get_position(){
		Vec2f v;
		if(myElement){
			v.x = myElement->GetProperty<float>("left");
			v.y = myElement->GetProperty<float>("top");
		}
		return v;
	}

	virtual Vec2f animable_get_size(){
		Vec2f v;
		if(myElement){
			v.x = myElement->GetProperty<float>("width");
			v.y = myElement->GetProperty<float>("height");
		}
		return v;
	}
	virtual void animable_set_size(float x, float y){
		if(myElement){
			myElement->SetProperty("width", String(String::number(x) + "px").c_str());
			myElement->SetProperty("height", String(String::number(y) + "px").c_str());
		}
	}

	virtual void animable_add_character(char c){
		if(myElement){
			Rocket::Core::String s = myElement->GetInnerRML();
			s.Append(c);
			myElement->SetInnerRML(s);
		}
	}


	Rocket::Core::Element *myElement;
};

PARABOLA_NAMESPACE_END
#endif