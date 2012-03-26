#ifndef PARABOLA_VIEWS_H
#define PARABOLA_VIEWS_H

#include "Platform.h"
#include <SFML/Graphics.hpp>

PARABOLA_NAMESPACE_BEGIN
	
	/**
		\ingroup Graphics
		\class View
		\brief Represents a 2D camera

		In practice, it is a 2D projection of your scene, orthogonal, which you can configure to taste.
	*/
	class PARABOLA_API View : public sf::View{
	public:
		
	};
	
	/// Typedef of View to Camera2D to suit tastes
	typedef View Camera2D;
PARABOLA_NAMESPACE_END

#endif