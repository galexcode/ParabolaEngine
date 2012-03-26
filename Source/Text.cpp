#include "ParabolaCore/Text.h"

PARABOLA_NAMESPACE_BEGIN
	Text::Text(){

	};

	Text::Text(String text, int x, int y){
		SetString(text);
		SetPosition(x, y);
	};

	/// Align the text to be centered between x and y - Horizontal Coordinates
	void Text::alignCenterH(int x, int y){

	};
	/// Align the text to be centered between x and y - Vertical Coordinates
	void Text::alignCenterV(int x, int y){

	};

PARABOLA_NAMESPACE_END