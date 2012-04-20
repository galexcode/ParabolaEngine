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

/// Get the size of the texture
Vec2f Texture::getSize(){
	return Vec2f(sf::Texture::getSize().x,sf::Texture::getSize().y);
};

PARABOLA_NAMESPACE_END