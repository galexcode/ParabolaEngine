#include "ParabolaCore/Views.h"

PARABOLA_NAMESPACE_BEGIN

/// Set the view center as a position
void View::setCenter(Vec2f position){
	sf::View::setCenter(position.x, position.y);
};

/// Set the view center as a position
void View::setCenter(float x, float y){
	sf::View::setCenter(x,y);
};

/// Get the view center
Vec2f View::getCenter(){
	sf::Vector2f v = sf::View::getCenter();
	return Vec2f(v.x, v.y);
};

/// Set the viewport for the view.
/// (x,y) is the starting point of the viewport rect
/// width and height define the dimensions of the viewport rect
/// target is needed to know what are the total dimensions of the window/rendertexture/etc
void View::setViewportInPixels(float x, float y, float width, float height, RenderTarget &target){
	setViewport(sf::FloatRect(x / target.getSize().x, y / target.getSize().y, width / target.getSize().x, height / target.getSize().y));
};

/// Set the viewport from one of the presets
void View::setViewportPreset(int preset){
	switch((ViewportPreset)preset){
		case TopLeftQuarter:
			{
				setViewport(sf::FloatRect(0.f, 0.f, 0.5f, 0.5f));
			}
			break;
		case TopRightQuarter:
			{
				setViewport(sf::FloatRect(0.5f, 0.f, 0.5f, 0.5f));
			}
			break;
		case BottomLeftQuarter:
			{
				setViewport(sf::FloatRect(0.f, 0.5f, 0.5f, 0.5f));
			}
			break;
		case BottomRightQuarter:
			{
				setViewport(sf::FloatRect(0.5f, 0.5f, 0.5f, 0.5f));
			}
			break;
		case TopHalf:
			{
				setViewport(sf::FloatRect(0.f, 0.f, 1.f, 0.5f));
			}
			break;
		case BottomHalf:
			{
				setViewport(sf::FloatRect(0.f, 0.5f, 1.f, 0.5f));
			}
			break;
		case LeftHalf:
			{
				setViewport(sf::FloatRect(0.f, 0.0f, 0.5f, 1.f));
			}
			break;
		case RightHalf:
			{
				setViewport(sf::FloatRect(0.5f, 0.f, 0.5f, 1.0f));
			}
			break;
		case WideScreen:
			{
				setViewport(sf::FloatRect(0.f, 0.08f, 1.f, 0.92f));
			}
			break;
	}
};

/// Reset the view to this rect
void View::setRect(float x, float y, float width, float height){
	reset(sf::FloatRect(x, y, width, height));
};

PARABOLA_NAMESPACE_END