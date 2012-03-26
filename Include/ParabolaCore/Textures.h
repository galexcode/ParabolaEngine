#ifndef PARABOLA_IMAGETEXTURE_H
#define PARABOLA_IMAGETEXTURE_H

#include "Platform.h"
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Texture.hpp>


PARABOLA_NAMESPACE_BEGIN	
	typedef sf::Color Color;
	/**
		\ingroup Graphics
		\class Image
		\brief Extends sf::Image
	*/
	class Image: public sf::Image{
	public:

	};

	/**
		\ingroup Graphics
		\class Texture
		\brief Extends sf::Texture
	*/
	class Texture: public sf::Texture{
	public:
		/// Converts all the pixels with the specified to color to the desired alpha
		/// In practice, it converts the texture to an Image, applies changes and brings it back to a Texture
		void maskColor(const Color &color, unsigned char alpha = 0 );
	};

	/**
		\ingroup Graphics
		\class RenderImage
		\brief Extends sf::RenderImage
	*/
	class RenderImage: public sf::RenderTexture{
	public:
		
	};

PARABOLA_NAMESPACE_END
#endif