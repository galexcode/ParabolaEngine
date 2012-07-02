#include "ParabolaCore/Renderer.h"
#include "ParabolaCore/Views.h"

#ifdef PARABOLA_DESKTOP
#include <ParabolaCore/RendererOpenGL.h>
#elif defined PARABOLA_ANDROID
#include <ParabolaCore/RendererGLES.h>
#endif

PARABOLA_NAMESPACE_BEGIN
/// Auto detects an appropriate renderer
Renderer* Renderer::createAutomaticRenderer(){

#ifdef PARABOLA_DESKTOP
	return new RendererOpenGL();
#elif defined PARABOLA_ANDROID
	return new RendererGLES();
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

/// Clear the bound buffer
void Renderer::clearBuffers(){

};

void Renderer::drawRocketContext(RocketContext* context){

}

void Renderer::drawVertexArray(VertexArray &vertexArray){

}
PARABOLA_NAMESPACE_END