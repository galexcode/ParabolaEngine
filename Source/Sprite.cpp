#include "ParabolaCore/Sprite.h"
#include "ParabolaCore/ContentBank.h"

#include <iostream>

PARABOLA_NAMESPACE_BEGIN

/// Default sprite
Sprite::Sprite() : sf::Sprite(){

};

/// Safe destruction
Sprite::~Sprite(){
	
};

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

void Sprite::resize(float x, float y){
	setScale((x / getGlobalBounds().width),(y / getGlobalBounds().height)); 
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


PARABOLA_NAMESPACE_END