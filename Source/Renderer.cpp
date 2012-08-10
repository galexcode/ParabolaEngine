#include "ParabolaCore/Renderer.h"
#include "ParabolaCore/Views.h"

#ifdef PARABOLA_DESKTOP
#include <ParabolaCore/RendererOpenGL.h>
#elif defined PARABOLA_ANDROID || defined PARABOLA_IPHONE
#include <ParabolaCore/RendererGLES.h>
#endif

PARABOLA_NAMESPACE_BEGIN
/// Auto detects an appropriate renderer
Renderer* Renderer::createAutomaticRenderer(RenderTarget* target){
	
#ifdef PARABOLA_DESKTOP
	RendererOpenGL* renderer = new RendererOpenGL();
	renderer->m_renderTarget = target;
	return renderer;
#elif defined PARABOLA_ANDROID	|| defined PARABOLA_IPHONE
	RendererGLES* renderer = new RendererGLES();
	renderer->m_renderTarget = target;
	return renderer;
#else
	return NULL;
#endif
};

Renderer::Renderer(){
	m_clearColor.r = 100;
	m_clearColor.g = 10;
};


/// Set the currently active view
void Renderer::setView(const View &view){
	m_currentView = view;
	applyView(m_currentView);
};

void Renderer::drawCube(float x, float y, float z, float len, Color color){

};

/// Clear the bound buffer
void Renderer::clearBuffers(){

};

void Renderer::drawRocketContext(RocketContext* context){

}

void Renderer::drawVertexArray(VertexArray &vertexArray){

}
PARABOLA_NAMESPACE_END