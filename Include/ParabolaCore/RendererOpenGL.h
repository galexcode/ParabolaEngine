#ifndef PARABOLA_RENDEREROPENGL_H
#define PARABOLA_RENDEREROPENGL_H

#include "Platform.h"
#include "Renderer.h"

PARABOLA_NAMESPACE_BEGIN

class PARABOLA_API RendererOpenGL : public Renderer{
public:
	RendererOpenGL();

	/// Clear the bound buffer
	virtual void clearBuffers();

	void applyView(const View &view);

	/// Anything that inherits Drawable can be drawn using a renderer
	virtual void draw(Drawable &drawable);

	virtual void prepare(int w, int h);
	virtual void drawDebugQuad(float x, float y, float angle, float width, float height, Color color);
	virtual void display();
	virtual void drawDebugTriangleFan(Vec2f* vlist, int vcount, Color color);
	virtual void drawDebugCircle(Vec2f center, float radius, Vec2f axis, Color color);
	virtual void drawVertexArray(VertexArray &vertexArray);
	virtual void drawRocketContext(RocketContext* context);
};

PARABOLA_NAMESPACE_END

#endif