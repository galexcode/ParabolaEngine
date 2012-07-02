#ifndef PARABOLA_TEXTRENDERING_H
#define PARABOLA_TEXTRENDERING_H

#include "Platform.h"
#include "Strings.h"
#include "Drawable.h"
#include "Font.h"
#include "Color.h"
#include "VertexArray.h"
#include "BoundingBox.h"


PARABOLA_NAMESPACE_BEGIN

class UString : public std::basic_string<Uint32>{
public:

};

class Font;

/**
		\ingroup Graphics
		\class Text
		\brief Extends sf::Text

		Inherits all sf::Text functionality and extends it for some more utility functions

*/
class PARABOLA_API Text : public Drawable{
public:		
		/// Creates a text with default font and content text positioned at (x,y) as top-left coordinate
		Text(String text, float x, float y);
		/// Creates a text with the desired font at the specified position
		Text(const Font &font, String text, float x, float y);
		/// Default text
		Text();

		/// Draws the text
		virtual void onDraw(Renderer* renderer);

		/// Align the text to be centered between x and y - Horizontal Coordinates
		void alignCenterH(float x, float y);
		/// Align the text to be centered between x and y - Vertical Coordinates
		void alignCenterV(float x, float y);


	////////////////////////////////////////////////////////////
    /// \brief Enumeration of the string drawing styles
    ///
    ////////////////////////////////////////////////////////////
    enum Style
    {
        Regular    = 0,      ///< Regular characters, no style
        Bold       = 1 << 0, ///< Bold characters
        Italic     = 1 << 1, ///< Italic characters
        Underlined = 1 << 2  ///< Underlined characters
    };
private:
	/// The string with the graphical text content
	UString m_string;
	/// The font to use to draw this text
	const Font* m_font;
	/// Size of the characters
	unsigned int m_characterSize;
	/// Style of text
	Uint32 m_style;
	/// Color of the text
	Color m_color;
	/// Text geometry
	VertexArray m_vertices;
	/// Bounds of the text
	BoundingBox m_bounds;
};

PARABOLA_NAMESPACE_END
#endif