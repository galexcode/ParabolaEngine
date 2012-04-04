#include "ParabolaCore/Text.h"

PARABOLA_NAMESPACE_BEGIN

Text::Text(){

};

/// Creates a text with the desired font at the specified position
Text::Text(const Font &font, String text, float x, float y){
	setFont(font);
	setString(text);
	setPosition(x, y);
};

Text::Text(String text, float x, float y){
	setString(text);
	setPosition(x, y);
};

/// Align the text to be centered between x and y - Horizontal Coordinates
void Text::alignCenterH(float x, float y){
	float xx, yy;
	xx = (x+y)/2 - getLocalBounds().width/2;
	yy = getPosition().y;
	setPosition(xx, yy);	
};

/// Align the text to be centered between x and y - Vertical Coordinates
void Text::alignCenterV(float x, float y){
	float xx, yy;
	xx = getPosition().x;
	yy = (x+y)/2 - getLocalBounds().height/2;
	setPosition(xx, yy);
};

PARABOLA_NAMESPACE_END