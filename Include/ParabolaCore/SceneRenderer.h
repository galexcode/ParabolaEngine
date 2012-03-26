#ifndef PARABOLA_SCENERENDERER_H
#define PARABOLA_SCENERENDERER_H

#include "Platform.h"
#include "SFML/Graphics.hpp"
#include "LinkedPointer.h"
#include "Strings.h"
#include "Drawable.h"
#include "Vectors.h"
#include "Views.h"

PARABOLA_NAMESPACE_BEGIN
	class SceneGraph;
	class RocketContext;
	
	typedef sf::RenderTarget RenderTarget;
	typedef sf::RenderStates RenderStates;

	/**
		\ingroup Graphics
		\class SceneRenderer
		\brief Responsible to draw everything in the scene

		Renderers need to point to a RenderTarget in order to be able to draw anything.

		A RenderTarget can be a window, a texture,etc and it will be completely transparent
		to draw to one or another.

		For ultimate flexibility, you will be able to stuff all your scene in a SceneGraph
		and draw the whole thing with one call. 

		By doing this, you could even draw your scene to multiple windows and/or textures,
		just by reassigning targets and redrawing the graph.

		Rendering process will be split into two ways:
			- Component based SceneGraph (Entities with a GraphicsComponent)
			- Loose graphic objects (such as Text,Sprite,etc)

		Both ways are very useful and can be mixed together.
		Also, using one or the other depends on how you decide 
		to design your game. The most simple games should be really
		fine with holding graphic objects the old traditional way,
		while complex scenes would certainly take advantage of
		using SceneGraph structures.

	*/
	class PARABOLA_API SceneRenderer{
	public:
		/// Creates a renderer with no render target
		SceneRenderer();
		/// Creates a renderer bound to [target]
		/// Version uses a raw pointer. Internally it is converted to a smart pointer
		/// Though, it will be invalid if the pointer is destroyed with delete.
		/// Recommended use: SceneRenderer renderer(new RenderTarget());
		/// In order to assure safety
		SceneRenderer(RenderTarget &target);
		/// Creates a renderer bound to [target]
		/// Version uses smart pointers, so it is just another
		/// safe reference to that target.
		SceneRenderer(linked_ptr<RenderTarget> &target);


		/// Returns the bound render target or NULL if none is assigned
		linked_ptr<RenderTarget> renderTarget();

		/// Binds the target to the renderer
		/// Version uses a raw pointer. Internally it is converted to a smart pointer
		/// Though, it will be invalid if the pointer is destroyed with delete.
		/// Recommended use: SceneRenderer renderer(new RenderTarget());
		/// In order to assure safety
		void setRenderTarget(RenderTarget *target);

		/// Binds the target to the renderer
		/// Creates a renderer bound to [target]
		/// Version uses smart pointers, so it is just another
		/// safe reference to that target.
		void setRenderTarget(linked_ptr<RenderTarget> &target);

		/// Get the size of the target
		Vec2i getSize();

		/// Sets a default camera to the target
		/// View port is all the render target
		/// The size of the view is equal to the render size(resolution) and has (0,0) origin
		/// The center of the view is (target width)/2 and (target height)/2
		void setFullView();

		/// Assign the view to the target directly
		void setView(const View &view);

		/// Get the currently applied view
		const View& getView();

		/// Sets the center of the view - the eye
		/// in world coordinates
		void setViewEye(Vec2f position);

		/// Rotates the view by [angle]
		/// In degrees
		void setViewRotation(float angle);

		/// Draws any SFML drawable or any inherited drawable into the target
		void draw(Drawable &drawable);

		/// Draws a rocket context
		void draw(RocketContext *rContext);

		/// Draws recursively a SceneGraph
		/// The graph can contain your whole scene of objects and entities
		/// Not all nodes need to have rendering behaviors
		void draw(SceneGraph &scene);

		/// Draws a SFML inherited drawable into a different target
		/// Use keepView to determine if the target will be used with the current target view
		void drawAt(RenderTarget &target, Drawable &drawable, bool keepView);

	private:
		linked_ptr<RenderTarget> myTarget;
	};

	
	

PARABOLA_NAMESPACE_END
#endif