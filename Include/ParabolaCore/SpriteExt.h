#ifndef PARABOLA_SPRITEEXT_H
#define PARABOLA_SPRITEEXT_H

#include "Platform.h"
#include "Drawable.h"
#include "AnimationSprite.h"


PARABOLA_NAMESPACE_BEGIN
/**
	\ingroup Graphics
	\class SpriteExt
	\brief Represents a special kind of sprite, that has animation support by default
*/
class PARABOLA_API SpriteExt : public Drawable{
public:
	/// Creates a ready sprite, that is only a colored square
	SpriteExt();

	/// Check if the sprite contains a point within its rect
	bool containsPoint(float x, float y);

	/// Check if the sprite contains a point within its rect
	bool containsPoint(Vec2f point);

	/// Check if the sprite is flipped in x axis
	bool getFlippedX();

	/// Check if the sprite is flipped in y axis
	bool getFlippedY();

	/// Flip both axes optionally
	/// Flipping is simply multiplying the scale by -1
	void flip(bool flipX, bool flipY);

	/// Set the origin of the sprite, relative to the top-left
	void setOrigin(float x, float y);

	/// Set the origin of the sprite, relative to the top-left
	void setOrigin(Vec2f origin);

	/// Set the position of the sprite
	void setPosition(float x, float y);

	/// Set the position of the sprite
	void setPosition(Vec2f position);

	/// Resize the sprite, using the scale factor
	void resize(float x, float y);

	/// Orders the start of a new animation
	void triggerAnimation(const String &name);

	/// Update the sprite state
	void update(float elapsedTime);

	/// Same as the other overload, with no option to load with content banks
	bool loadFromTextFile(const String &path);

	/// Loads the sprite from a text definition
	bool loadFromTextFile(const String &path, ContentBank *bank);

	/// Parse sprite settings from the code
	void parseSettings(String &code);

	/// Parse an animation from the code
	void parseAnimation(String &code);

	/// Parse a texture from the code
	void parseTexture(String &code, ContentBank* bank);


	bool bake(const String &fileName, bool bakeTextures);

protected:
	/// Making the sprite a drawable
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
	Sprite mySprite;
	AnimationSprite* myCurrentAnimation;
	std::map<String, AnimationSprite> myAnimations;
	std::map<String, std::shared_ptr<Texture> > myTextures;
	typedef std::map<String, std::shared_ptr<Texture> >::iterator TextureIterator;
	String myDefaultAnimation;

};

PARABOLA_NAMESPACE_END
#endif