#ifndef PARABOLA_SPRITE_H
#define PARABOLA_SPRITE_H

#include "Platform.h"
#include "Strings.h"
#include "Vectors.h"
#include <vector>
#include <SFML/Graphics/Sprite.hpp>

PARABOLA_NAMESPACE_BEGIN

/**
		\ingroup Graphics
		\class Sprite
		\brief Extends sf::Sprite and implements more functionality.
*/
class PARABOLA_API Sprite: public sf::Sprite{
public:
	/// Default sprite
	Sprite();

	/// Set the position from a vec2f
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

	/// Resizes the sprite to the selected dimensions using the scale.
	void resize(float x, float y);
	
	/// Check if a point is contained in the sprite
	bool containsPoint(Vec2f point);

	/// Check if a point is contained in the sprite
	bool containsPoint(float x, float y);

};


/**
	\ingroup Graphics
	\class SpriteExt
	\brief Represents a special kind of sprite, that has animation support by default
*/
class PARABOLA_API SpriteExt{
public:
	/// Creates a ready sprite, that is only a colored square
	SpriteExt();

	bool bake(const String &fileName, bool bakeTextures);

private:
	Sprite mySprite;

	/// Holds private textures, loaded from a baked sprite, cannot be shared with anyone else
	//std::vector<Texture*> myTextures;

};

PARABOLA_NAMESPACE_END
#endif