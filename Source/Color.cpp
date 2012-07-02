#include "ParabolaCore/Color.h"

PARABOLA_NAMESPACE_BEGIN

Color::Color(){
	r = g = b = a = 1.f;
};

Color::Color(int byteRed, int byteGreen, int byteBlue, int byteAlpha){
	r = byteRed;
	g = byteGreen;
	b = byteBlue;
	a = byteAlpha;
};

PARABOLA_NAMESPACE_END