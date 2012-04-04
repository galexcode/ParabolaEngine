#include "ParabolaCore/SceneRenderer.h"
#include "ParabolaCore/SceneGraph.h"
#include "ParabolaCore/RocketContext.h"
#include "ParabolaCore/Logger.h"
#include "ParabolaCore/Text.h"
#include "ParabolaCore/Window.h"

#ifdef PARABOLA_WINDOWS
#include <Windows.h>
#endif
#include <GL/gl.h>

PARABOLA_NAMESPACE_BEGIN

SceneRenderer::SceneRenderer(){	
	myTarget = NULL;
}

SceneRenderer::SceneRenderer(RenderTarget &target){
	myTarget = &target;
}

/// Returns the bound render target or NULL if none is assigned
RenderTarget* SceneRenderer::getRenderTarget(){
	return myTarget;
};

void SceneRenderer::setRenderTarget(RenderTarget &target){
	myTarget = &target;
};

Vec2i SceneRenderer::getTargetSize(){
	if(myTarget)return Vec2i(myTarget->getSize().x,myTarget->getSize().y);
	else return Vec2i(0,0);
};

/// Activate the window
void SceneRenderer::activateRenderTarget(){
	((Window*)getRenderTarget())->setActive(true);
};

/// Draws a debug circle
void SceneRenderer::drawDebugCircle(float x, float y, float r){
	sf::CircleShape c;
	c.setPosition(x,y);
	c.setRadius(r);
	c.setFillColor(Color::Red);
	draw(c);
};


/// Get the currently applied view
const View& SceneRenderer::getView(){
	return static_cast<const View&>(myTarget->getView());
};

/// Assign the view to the target directly
void SceneRenderer::setView(const View &view){
	if(myTarget){
		myTarget->setView(view);
	}
};

/// Sets the center of the view - the eye
/// in world coordinates
void SceneRenderer::setViewEye(Vec2f position){
	if(myTarget){
		sf::View view = myTarget->getView();
		view.setCenter(sf::Vector2f(position.x, position.y));
	}
};

/// Rotates the view by [angle]
/// In degrees
void SceneRenderer::setViewRotation(float angle){
	if(myTarget){
		sf::View view = myTarget->getView();
		view.setRotation(angle);
	}
};

/// Draw a text in the screen
void SceneRenderer::drawDebugText(const String &text, float x, float y){
	draw(Text(text,x,y));
};

/// Draws any SFML drawable or any inherited drawable into the target
void SceneRenderer::draw(sf::Drawable &drawable){
	if(myTarget){
		myTarget->draw(drawable);
	}
};

/// Draws a rocket context
void SceneRenderer::draw(RocketContext *rContext){
	//rContext->render();
	DEBUG_MESSAGE("WHAT THE FUCK");
};

/// Draws recursively a SceneGraph
/// The graph can contain your whole scene of objects and entities
/// Not all nodes need to have rendering behaviors
void SceneRenderer::draw(SceneGraph &scene){
	scene.render(this);
};

/// Draws a SFML inherited drawable into a different target
/// Use keepView to determine if the target will be used with the current target view
void SceneRenderer::drawAt(RenderTarget &target, Drawable &drawable, bool keepView){
	// backup the view
	View v = (View&)target.getView();

	if(keepView){
		if(myTarget){
			v = (View&)myTarget->getView();
			target.setView(v);
		}
	}	
	
	target.draw(drawable);

	//restore the view
	target.setView(v);
};


PARABOLA_NAMESPACE_END