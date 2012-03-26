#ifndef PARABOLA_DRAWABLE_H
#define PARABOLA_DRAWABLE_H

#include "Platform.h"
#include <SFML/Graphics.hpp>

PARABOLA_NAMESPACE_BEGIN

typedef sf::Color Color;

/**	
	\ingroup Graphics
	Typedef of sf::Drawable to belong to the engine's namespace
 */
typedef sf::Drawable Drawable;

/**
	\ingroup Graphics
	\class PainterDrawable
	\brief Graphics API base class for drawable objects.

	Every class that can be drawn to the quad tree structure
	must implement this interface.

	Different than the SFML drawables. Under development. Ignore.

*/	
class PARABOLA_API PainterDrawable{
public:

};

PARABOLA_NAMESPACE_END
#endif