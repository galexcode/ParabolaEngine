#ifndef PARABOLA_COLOR_H
#define PARABOLA_COLOR_H

#include "Platform.h"

PARABOLA_NAMESPACE_BEGIN

class PARABOLA_API Color{
public:
	Color();
	Color(int byteRed, int byteGreen, int byteBlue, int byteAlpha = 255);

	Uint8 r,g,b,a;
};

PARABOLA_NAMESPACE_END
#endif