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
		\brief A Drawable sprite.
*/
class PARABOLA_API Sprite: public sf::Sprite{
public:
		//Sprite();

		void SetPosition(Vec2f Position);
		void SetPosition(float x, float y);

		void SetCenterPosition(float x, float y);

		Vec2f GetPosition();

		void Resize(float x, float y);
	
		bool ContainsPoint(Vec2f Point);

		//void SetActiveAnimation(KeyFrameAnimation *Animation);
		//KeyFrameAnimation* CreateAnimation(string AnimationName);

	private:

		//KeyFrameAnimation *CurrentAnimation;
		//vector<KeyFrameAnimation*> Animations;

		//bool StaticFlag;
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


	/**
		\class MultiSprite
		\brief A special Sprite with the ability to draw big images

		This class exists to go around GPU texture size limitations.
		Since in some older laptops and equivalent hardware the gpu won't support textures bigger than 1024x1024 or worse, this class provides a easy way to take a few smaller images and render them as if they were one.

		This is useful to support older graphic cards when deploying an application. 

	*/
	class MultiSprite{
	public:
		/**
			\brief Loads and prepares a Sprite to draw

		*/
		//bool LoadSprite(string FileName, int RowCount, int ColumnCount);
		//bool LoadSprite(string MultiSpriteFileName);
	};



PARABOLA_NAMESPACE_END
#endif