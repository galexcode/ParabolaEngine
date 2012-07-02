#include "ParabolaCore/Views.h"
#include "ParabolaCore/MathTools.h"

#include <cmath>

PARABOLA_NAMESPACE_BEGIN

View::View() : m_transformUpdated(false), m_invTransformUpdated(false), m_rotation(0){

}

/// Get the view center
Vec2f View::getCenter(){
	return Vec2f(m_rect.Position.x + m_rect.Size.x/2, m_rect.Position.y + m_rect.Size.y/2);
};

void View::move(float x, float y){
	 setCenter(m_center.x + x, m_center.y + y);
};


/// Set the view center as a position
void View::setCenter(Vec2f position){
	m_center = position;
	m_rect.set(position.x - m_rect.Size.x/2, position.y - m_rect.Size.y/2, m_rect.Size.x, m_rect.Size.y);
};

/// Set the view center as a position
void View::setCenter(float x, float y){
	setCenter(Vec2f(x,y));
};
/*
/// Get the view center
Vec2f View::getCenter(){

};*/

/// Set the viewport for the view.
/// (x,y) is the starting point of the viewport rect
/// width and height define the dimensions of the viewport rect
/// target is needed to know what are the total dimensions of the window/rendertexture/etc
/*void View::setViewportInPixels(float x, float y, float width, float height, RenderTarget &target){
	
};*/

/// Set the viewport from one of the presets
void View::setViewportPreset(int preset){
	switch((ViewportPreset)preset){
		case TopLeftQuarter:
			{
				//setViewport(sf::FloatRect(0.f, 0.f, 0.5f, 0.5f));
			}
			break;
		case TopRightQuarter:
			{
				//setViewport(sf::FloatRect(0.5f, 0.f, 0.5f, 0.5f));
			}
			break;
		case BottomLeftQuarter:
			{
				//setViewport(sf::FloatRect(0.f, 0.5f, 0.5f, 0.5f));
			}
			break;
		case BottomRightQuarter:
			{
				//setViewport(sf::FloatRect(0.5f, 0.5f, 0.5f, 0.5f));
			}
			break;
		case TopHalf:
			{
				//setViewport(sf::FloatRect(0.f, 0.f, 1.f, 0.5f));
			}
			break;
		case BottomHalf:
			{
				//setViewport(sf::FloatRect(0.f, 0.5f, 1.f, 0.5f));
			}
			break;
		case LeftHalf:
			{
				//setViewport(sf::FloatRect(0.f, 0.0f, 0.5f, 1.f));
			}
			break;
		case RightHalf:
			{
				//setViewport(sf::FloatRect(0.5f, 0.f, 0.5f, 1.0f));
			}
			break;
		case WideScreen:
			{
				//setViewport(sf::FloatRect(0.f, 0.08f, 1.f, 0.92f));
			}
			break;
	}
};

BoundingBox View::getRect() const{
	return m_rect;
};


/// Reset the view to this rect
void View::setRect(float x, float y, float width, float height){
	//reset(sf::FloatRect(x, y, width, height));
	m_rect.Position.x = x;
	m_rect.Position.y = y;
	m_rect.Size.x = width;
	m_rect.Size.y = height;
	m_center = Vec2f(m_rect.Position.x + m_rect.Size.x/2, m_rect.Position.y + m_rect.Size.y/2);
};

/// Get the dimensions of the view rect
Vec2f View::getSize(){
	return m_rect.Size;
};

/// Set the size of the view rect, perserving its center
void View::setSize(float width, float height){
	m_rect.Position.x = getCenter().x - width/2;
	m_rect.Position.y = getCenter().y - height/2;
	m_rect.Size.x = width;
	m_rect.Size.y = height;
};

/// Zoom the view by a factor
void View::zoom(float factor){
	setSize(getSize().x * factor , getSize().y * factor);
};

////////////////////////////////////////////////////////////
const Transform& View::getTransform() const
{
	// Recompute the matrix if needed
	if (!m_transformUpdated)
	{
		// Rotation components
		m_center = Vec2f(m_rect.Position.x + (m_rect.Size.x / 2), m_rect.Position.y + (m_rect.Size.y / 2));
		Vec2f m_size(m_rect.Size.x,m_rect.Size.y);

		float angle  = m_rotation * 3.141592654f / 180.f;
		float cosine = static_cast<float>(std::cos(angle));
		float sine   = static_cast<float>(std::sin(angle));
		float tx     = -m_center.x * cosine - m_center.y * sine + m_center.x;
		float ty     =  m_center.x * sine - m_center.y * cosine + m_center.y;

		// Projection components
		float a =  2.f / m_size.x;
		float b = -2.f / m_size.y;
		float c = -a * m_center.x;
		float d = -b * m_center.y;

		// Rebuild the projection matrix
		m_transform = Transform( a * cosine, a * sine,   a * tx + c,
			-b * sine,   b * cosine, b * ty + d,
			0.f,        0.f,        1.f);
		//m_transformUpdated = true;
	}

	return m_transform;
}


////////////////////////////////////////////////////////////
const Transform& View::getInverseTransform() const
{
	// Recompute the matrix if needed
	if (!m_invTransformUpdated)
	{
		m_inverseTransform = getTransform().getInverse();
		m_invTransformUpdated = true;
	}

	return m_inverseTransform;
}


PARABOLA_NAMESPACE_END