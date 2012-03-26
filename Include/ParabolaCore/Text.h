#ifndef PARABOLA_TEXTRENDERING_H
#define PARABOLA_TEXTRENDERING_H

#include "Platform.h"
#include "Strings.h"
#include <SFML/Graphics/Text.hpp>

PARABOLA_NAMESPACE_BEGIN

	typedef sf::Color Color;

	/**
		\ingroup Graphics
		\class Text
		\brief Extends sf::Text

		Inherits all sf::Text functionality and extends it for some more utility functions

	*/
	class PARABOLA_API Text : public sf::Text{
	public:		
		/// Creates a text with default font and content text positioned at (x,y) as top-left coordinate
		Text(String text, int x, int y);
		/// Creates an empty text
		Text();

		/// Align the text to be centered between x and y - Horizontal Coordinates
		void alignCenterH(int x, int y);
		/// Align the text to be centered between x and y - Vertical Coordinates
		void alignCenterV(int x, int y);
	};

PARABOLA_NAMESPACE_END
#endif