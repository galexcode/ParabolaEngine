#include "ParabolaCore/Textures.h"

PARABOLA_NAMESPACE_BEGIN
	/************************************************************************/
	/* Texture                                                              */
	/************************************************************************/
	void Texture::maskColor(const Color &color, unsigned char alpha){
		sf::Image img = this->copyToImage();
		img.createMaskFromColor(color, alpha);
		loadFromImage(img);
	};

PARABOLA_NAMESPACE_END