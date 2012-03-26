#ifndef PARABOLA_ANIMATIONSPRITE_H
#define PARABOLA_ANIMATIONSPRITE_H

#include "Platform.h"
#include "Animation.h"
#include "Sprite.h"
#include "BoundingBox.h"
#include "Textures.h"

PARABOLA_NAMESPACE_BEGIN

	class PARABOLA_API AnimationSpriteFrame{
	public:
		AnimationSpriteFrame();
		AnimationSpriteFrame(BoundingBox &box, Texture *texture, double time);
		double time;
		BoundingBox subRect;
		Texture *texture;

	};

	/**
		\ingroup Animation
		\class AnimationSprite
		\brief Represents an animation of image frames in a set of sprites

		Can animate a set of sprites at the same time and will set them with the
		right texture sub rect along time, to simulate movement.
	*/
	class PARABOLA_API AnimationSprite : public AnimationInterface{
	public:
		/// Creates a default sprite animation
		AnimationSprite();

		/// Adds a reference to the Sprite object to animate it
		/// \warning A pointer to the Sprite is stored, if the object becomes invalid
		/// and isnt removed from this list you may experience a crash.
		void addSprite(Sprite &animatedSprite);

		/// Add a new frame to the animation
		void addFrame(AnimationSpriteFrame &frame);

		/// Get the number of frames in this animation
		int getFrameCount();

		/// Applies one of the frames to all sprites
		void applyFrame(int index);

		/// Overload of AnimationInterface. Plays the animation.
		void play();
		/// Overload of AnimationInterface. Stops the animation.
		void stop();

		/// Reset the animation to the beginning
		void reset();

		/// Update the sprites over time. Essentially means changing its texture when needed!
		void update(float elapsedTime);

		/**
			Builds the frames from a sprite sheet, in this case only a one-line sprite sheet.

			Just specify the width of each frame, and how many you want, and from what texture, and it will do the work.
		*/
		int buildFromHorizontalSheet(float frameWidth, int frameCount, Texture* texture);

	private:
		std::vector<AnimationSpriteFrame> frames;
		std::vector<Sprite*> animationSprites;
		double currentTime;
		double totalTime;
		double localTime;
		int frameIndex;
	};

PARABOLA_NAMESPACE_END
#endif