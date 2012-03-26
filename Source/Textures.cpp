#include "ParabolaCore/Textures.h"

PARABOLA_NAMESPACE_BEGIN
	/************************************************************************/
	/* Texture                                                              */
	/************************************************************************/
	void Texture::maskColor(const Color &color, unsigned char alpha){
		sf::Image img = this->CopyToImage();
		img.CreateMaskFromColor(color, alpha);
		LoadFromImage(img);
	};

PARABOLA_NAMESPACE_END