#ifndef PARABOLA_GRAPHICSRENDERER_H
#define PARABOLA_GRAPHICSRENDERER_H

#include "Platform.h"
#include "Vectors.h"
#include "Color.h"
#include "Drawable.h"
#include "VertexArray.h"
#include "Views.h"
#include "RenderTarget.h"

PARABOLA_NAMESPACE_BEGIN

class RocketContext;


class PARABOLA_API Renderer{
public:
	Renderer();

	View m_currentView;

	Color m_clearColor;

	/// Apply a view
	virtual void applyView(const View &view) = 0;

	/// Set the currently active view
	virtual void setView(const View &view);

	/// Clear the bound buffer
	virtual void clearBuffers();

	virtual void drawCube(float x, float y, float z, float len, Color color);


	/// Anything that inherits Drawable can be drawn using a renderer
	virtual void draw(Drawable &drawable) = 0;


	virtual void prepare(int w, int h) = 0;
	virtual void drawDebugQuad(float x, float y, float angle, float width, float height, Color color = Color(255,0,1)) = 0;
	virtual void display() = 0;
	virtual void drawDebugTriangleFan(Vec2f* vlist, int vcount, Color color) = 0;
	virtual void drawDebugCircle(Vec2f center, float radius, Vec2f axis, Color color) = 0;

	virtual void drawVertexArray(VertexArray &vertexArray);
	virtual void drawRocketContext(RocketContext* context);

	/// Auto detects an appropriate renderer
	static Renderer* createAutomaticRenderer(RenderTarget* target);

//protected:
	/// The bound render target, where geometry is drawn
	RenderTarget* m_renderTarget;
};

PARABOLA_NAMESPACE_END
#endif