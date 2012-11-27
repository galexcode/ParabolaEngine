#ifndef PARABOLA_SPRITE_H
#define PARABOLA_SPRITE_H

#include "Platform.h"
#include "Strings.h"
#include "Animation.h"
#include "Vectors.h"
#include "Drawable.h"
#include "Transformable.h"
#include "VertexArray.h"
#include "Textures.h"
#include <vector>


PARABOLA_NAMESPACE_BEGIN

class ContentBank;
/**
		\ingroup Graphics
		\class Sprite
		\brief Extends sf::Sprite and implements more functionality.
*/
class PARABOLA_API Sprite: public Drawable, public Animable, public Transformable{
public:
	/// Default sprite
	Sprite();

	/// Safe destruction
	virtual ~Sprite();

	/// Called to order rendering, when the drawing was issued in the traditional way ( m_renderer->draw(m_sprite) )
	virtual void onDraw(Renderer* renderer);

	/// Set the texture of the sprite
	void setTexture(const Texture &texture, bool resetRect = false);

	/// Set the texture rect to show
	void setTextureRect(const FloatRect &rect);

	/// Set the color of the sprite
	void setColor(const Color& color);

	FloatRect getGlobalBounds() const;

	/// Get the binded texture
	const Texture& getTexture();

	/// Resizes the sprite to the selected dimensions using the scale.
	void resize(float x, float y);

	FloatRect getLocalBounds() const;

	const Texture* m_texture;
	VertexArray m_vertices;
	FloatRect m_textureRect;

protected:
	/// Animation properties
	void animable_set_alpha(int alpha);

	/*/// Set the position from a vec2f
	/// Position is the top-left coordinate
	void setPosition(Vec2f position);

	/// Set the position from a vec2f
	/// Position is the top-left coordinate
	void setPosition(float x, float y);

	/// Sets the position of the sprite, considering its center instead
	/// Is considered as the center the middle of the local bounding box
	void setCenterPosition(float x, float y);

	/// Sets the position of the sprite, considering its center instead
	/// Is considered as the center the middle of the local bounding box
	void setCenterPosition(Vec2f position);


	
	/// Check if a point is contained in the sprite
	bool containsPoint(Vec2f point);

	/// Check if a point is contained in the sprite
	bool containsPoint(float x, float y);

	/// Check if the scale factor is negative
	bool isFlippedHorizontally();

	/// Flip the sprite horizontally
	void flipHorizontal();

	/// Check if the scale factor is negative
	bool isFlippedVertically();

	/// Flip the sprite horizontally
	void flipVertical();

	void animable_set_position(float x, float y){
		setPosition(x,y);
	}

	Vec2f animable_get_position(){
		return Vec2f(getPosition().x, getPosition().y);
	};

	void animable_set_color(int r, int g, int b, int a){
		//setColor(Color(r,g,b,a));
	}*/
};

PARABOLA_NAMESPACE_END
#endif