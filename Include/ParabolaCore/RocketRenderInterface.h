#ifndef PARABOLA_ROCKETRENDERINTERFACE_H
#define PARABOLA_ROCKETRENDERINTERFACE_H

#include "Platform.h"

#include <Rocket/Core.h>
#include <Rocket/Core/RenderInterface.h>

//#include <SFML/Graphics.hpp>

PARABOLA_NAMESPACE_BEGIN

class Renderer;
	/**
		\ingroup libRocket
		\ingroup Graphics
		\class RocketRenderInterface
		\brief Custom render interface for libRocket.

		This is a general renderer of libRocket ui, as in it is used by all contexts.

		Each time a context renders, it adapts this interface at will.

		It won't need to be used directly.
	*/
	class PARABOLA_API RocketRenderInterface : public Rocket::Core::RenderInterface{
	public:
		/// Instances the renderer for use
		RocketRenderInterface();

		/// Destructs the renderer
		~RocketRenderInterface();

		Renderer* myRenderer;

		//temp
		//sf::RenderTarget *target;
		//sf::RenderStates *states;


	protected:
		/// Called by Rocket when it wants to render geometry that it does not wish to optimise.
		virtual void RenderGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture, const Rocket::Core::Vector2f& translation);

		/// Called by Rocket when it wants to compile geometry it believes will be static for the forseeable future.
		virtual Rocket::Core::CompiledGeometryHandle CompileGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture);

		/// Called by Rocket when it wants to render application-compiled geometry.
		virtual void RenderCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry, const Rocket::Core::Vector2f& translation);
		
		/// Called by Rocket when it wants to release application-compiled geometry.
		virtual void ReleaseCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry);

		/// Called by Rocket when it wants to enable or disable scissoring to clip content.
		virtual void EnableScissorRegion(bool enable);
		
		/// Called by Rocket when it wants to change the scissor region.
		virtual void SetScissorRegion(int x, int y, int width, int height);

		/// Called by Rocket when a texture is required by the library.
		virtual bool LoadTexture(Rocket::Core::TextureHandle& texture_handle, Rocket::Core::Vector2i& texture_dimensions, const Rocket::Core::String& source);
		
		/// Called by Rocket when a texture is required to be built from an internally-generated sequence of pixels.
		virtual bool GenerateTexture(Rocket::Core::TextureHandle& texture_handle, const Rocket::Core::byte* source, const Rocket::Core::Vector2i& source_dimensions);
		
		/// Called by Rocket when a loaded texture is no longer required.
		virtual void ReleaseTexture(Rocket::Core::TextureHandle texture_handle);

	};
		
PARABOLA_NAMESPACE_END
#endif