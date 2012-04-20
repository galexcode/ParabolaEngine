#ifndef PARABOLA_VIEWS_H
#define PARABOLA_VIEWS_H

#include "Platform.h"
#include "Vectors.h"
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

PARABOLA_NAMESPACE_BEGIN

enum ViewportPreset{
	TopLeftQuarter = 0,
	TopRightQuarter,
	BottomLeftQuarter,
	BottomRightQuarter,
	LeftHalf,
	RightHalf,
	TopHalf,
	BottomHalf,
	WideScreen
};

typedef sf::RenderTarget RenderTarget;
/**
		\ingroup Graphics
		\class View
		\brief Represents a 2D camera

		In practice, it is a 2D projection of your scene, orthogonal, which you can configure to taste.
*/
class PARABOLA_API View : public sf::View{
public:
		/// Set the view center as a position
		void setCenter(Vec2f position);
		/// Set the view center as a position
		void setCenter(float x, float y);

		/// Set the viewport from one of the presets
		void setViewportPreset(int preset);

		/// Set the viewport for the view.
		/// (x,y) is the starting point of the viewport rect
		/// width and height define the dimensions of the viewport rect
		/// target is needed to know what are the total dimensions of the window/rendertexture/etc
		void setViewportInPixels(float x, float y, float width, float height, RenderTarget &target);

		/// Get the view center
		Vec2f getCenter();

		/// Reset the view to this rect
		void setRect(float x, float y, float width, float height);
	};
	
	/// Typedef of View to Camera2D to suit tastes
	typedef View Camera2D;
PARABOLA_NAMESPACE_END

#endif