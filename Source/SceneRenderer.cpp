#include "ParabolaCore/SceneRenderer.h"
#include "ParabolaCore/SceneGraph.h"
#include "ParabolaCore/RocketContext.h"
#include "ParabolaCore/Logger.h"

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

SceneRenderer::SceneRenderer(linked_ptr<RenderTarget> &target){
	myTarget = target;
};


/// Returns the bound render target or NULL if none is assigned
linked_ptr<RenderTarget> SceneRenderer::renderTarget(){
	return myTarget;
}

void SceneRenderer::setRenderTarget(RenderTarget *target){
	myTarget = target;
};

void SceneRenderer::setRenderTarget(linked_ptr<RenderTarget> &target){
	myTarget = target;
};

Vec2i SceneRenderer::getSize(){
	if(myTarget)return Vec2i(myTarget->GetWidth(),myTarget->GetHeight());
	else return Vec2i(0,0);
};

/// Sets a default camera to the target
/// View port is all the render target
/// The size of the view is equal to the render size(resolution) and has (0,0) origin
/// The center of the view is (target width)/2 and (target height)/2
void SceneRenderer::setFullView(){
	if(myTarget){
		sf::View view = myTarget->GetView();
		view.Reset(sf::FloatRect(0.f, 0.f, myTarget->GetWidth(), myTarget->GetHeight()));
		view.SetViewport(sf::FloatRect(0.f,0.f,1.f,1.f));
	}
};

/// Get the currently applied view
const View& SceneRenderer::getView(){
	return static_cast<const View&>(myTarget->GetView());
};

/// Assign the view to the target directly
void SceneRenderer::setView(const View &view){
	if(myTarget){
		myTarget->SetView(view);
	}
};

/// Sets the center of the view - the eye
/// in world coordinates
void SceneRenderer::setViewEye(Vec2f position){
	if(myTarget){
		sf::View view = myTarget->GetView();
		view.SetCenter(sf::Vector2f(position.x, position.y));
	}
};

/// Rotates the view by [angle]
/// In degrees
void SceneRenderer::setViewRotation(float angle){
	if(myTarget){
		sf::View view = myTarget->GetView();
		view.SetRotation(angle);
	}
};

/// Draws any SFML drawable or any inherited drawable into the target
void SceneRenderer::draw(sf::Drawable &drawable){
	if(myTarget){
		myTarget->Draw(drawable);
	}
};

/// Draws a rocket context
void SceneRenderer::draw(RocketContext *rContext){
	rContext->Render();
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
	View v = (View&)target.GetView();

	if(keepView){
		if(myTarget){
			v = (View&)myTarget->GetView();
			target.SetView(v);
		}
	}	
	
	target.Draw(drawable);

	//restore the view
	target.SetView(v);
};


PARABOLA_NAMESPACE_END