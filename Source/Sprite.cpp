#include "ParabolaCore/Sprite.h"
#include "ParabolaCore/ContentBank.h"
#include "ParabolaCore/Renderer.h"

#include <iostream>

#ifdef PARABOLA_IPHONE
#include <OpenGLES/ES1/gl.h>
#endif


PARABOLA_NAMESPACE_BEGIN

/// Default sprite
Sprite::Sprite() : m_vertices(TriangleFan,4) , m_texture(NULL){
	m_vertices[0].color = Color(255,255,255,255);
	m_vertices[1].color = Color(255,255,255,255);
	m_vertices[2].color = Color(255,255,255,255);
	m_vertices[3].color = Color(255,255,255,255);
};

/// Safe destruction
Sprite::~Sprite(){
	
};

/// Set the texture rect to show
void Sprite::setTextureRect(const FloatRect &rect){
	m_vertices[0].position = Vec2f(0.f,0.f);
	m_vertices[1].position = Vec2f(rect.width,0.f);
	m_vertices[2].position = Vec2f(rect.width,rect.height);
	m_vertices[3].position = Vec2f(0.f,rect.height);

	float texture_width = static_cast<float>(const_cast<Texture*>(m_texture)->getSize().x);
	float texture_height = static_cast<float>(const_cast<Texture*>(m_texture)->getSize().y);

	float left   = static_cast<float>(rect.left);
	float right  = left + rect.width;
	float top    = static_cast<float>(rect.top);
	float bottom = top + rect.height;

	/*left /= texture_width;
	right /= texture_width;
	top /= texture_height;
	bottom /= texture_height;*/

	m_vertices[0].texCoords = Vec2f(left, top);
	m_vertices[1].texCoords = Vec2f(right, top);
	m_vertices[2].texCoords = Vec2f(right, bottom);
	m_vertices[3].texCoords = Vec2f(left, bottom);

	m_textureRect = FloatRect(left, top, right, bottom);
};

/// Set the texture of the sprite
void Sprite::setTexture(const Texture &texture, bool resetRect){	
	m_texture = &texture;

	setTextureRect(FloatRect(0.f,0.f, texture.getSize().x, texture.getSize().y));
};

/// Get the binded texture
const Texture& Sprite::getTexture(){
	return *m_texture;
};

void Sprite::resize(float x, float y){
	setScale((x / m_texture->getSize().x ),(y / m_texture->getSize().y)); 
};

/// Set the color of the sprite
void Sprite::setColor(const Color& color){
	m_vertices[0].color = color;
	m_vertices[1].color = color;
	m_vertices[2].color = color;
	m_vertices[3].color = color;
};


////////////////////////////////////////////////////////////
FloatRect Sprite::getLocalBounds() const
{
	float width = static_cast<float>(m_textureRect.width);
	float height = static_cast<float>(m_textureRect.height);

	return FloatRect(0.f, 0.f, width, height);
}


////////////////////////////////////////////////////////////
FloatRect Sprite::getGlobalBounds() const
{
	return getTransform().transformRect(getLocalBounds());
}


/// Called to order rendering, when the drawing was issued in the traditional way ( m_renderer->draw(m_sprite) )
void Sprite::onDraw(Renderer* renderer){
	if(!m_texture) return; //invalid texture

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glMatrixMode(GL_TEXTURE_MATRIX);
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glMultMatrixf(getTransform().getMatrix());
	
	m_texture->bind(Texture::Pixels);
	renderer->drawVertexArray(m_vertices);
	glMatrixMode(GL_TEXTURE_MATRIX);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
};

/// Animation properties
void Sprite::animable_set_alpha(int alpha){
	setColor(Color(m_vertices[0].color.r, m_vertices[0].color.g, m_vertices[0].color.b, alpha));
};

/*
/// Set the position from a vec2f
void Sprite::setPosition(Vec2f position){
	sf::Sprite::setPosition(position.x, position.y);
};

/// Set the position from a vec2f
/// Position is the top-left coordinate
void Sprite::setPosition(float x, float y){
	sf::Sprite::setPosition(x, y);
};

void Sprite::setCenterPosition(float x, float y){
	sf::Sprite::setPosition(x - (getLocalBounds().width/2), y - (getLocalBounds().height/2));
};

/// Sets the position of the sprite, considering its center instead
/// Is considered as the center the middle of the local bounding box
void Sprite::setCenterPosition(Vec2f position){
	sf::Sprite::setPosition(position.x - (getLocalBounds().width/2), position.y - (getLocalBounds().height/2));
};



/// Check if a point is contained in the sprite
bool Sprite::containsPoint(Vec2f point){
	return getGlobalBounds().contains(point.x, point.y);
};

/// Check if a point is contained in the sprite
bool Sprite::containsPoint(float x, float y){
	return getGlobalBounds().contains(x, y);
};

/// Check if the scale factor is negative
bool Sprite::isFlippedHorizontally(){
	if(getScale().x < 0.f)return true;
	else return false;
};

/// Flip the sprite horizontally
void Sprite::flipHorizontal(){
	scale(-1, 1);
};

/// Check if the scale factor is negative
bool Sprite::isFlippedVertically(){
	if(getScale().y < 0.f)return true;
	else return false;
};

/// Flip the sprite horizontally
void Sprite::flipVertical(){
	scale(1, -1);
};
*/

PARABOLA_NAMESPACE_END
