#include <ParabolaCore/Platform.h>
#ifndef PARABOLA_ANDROID
#include <ParabolaCore/RendererOpenGL.h>
#include "ParabolaCore/RocketContext.h"
#include "ParabolaCore/RocketPlugin.h"
#include "ParabolaCore/RocketRenderInterface.h"
#include "ParabolaCore/Views.h"

#include <ParabolaCore/Engine.h>

#ifdef PARABOLA_WINDOWS
#include <windows.h>
#endif
#include <GL/GL.h>

PARABOLA_NAMESPACE_BEGIN

RendererOpenGL::RendererOpenGL() : Renderer(){

};


void RendererOpenGL::applyView(const View &view){
	glViewport(0, 0, Engine::instance()->getWindow().getWidth(), Engine::instance()->getWindow().getHeight());

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(45, (float)width / height, 0.5f, 150);
	BoundingBox rect = view.getRect();
	//glOrtho(rect.Position.x, rect.Size.x , rect.Size.y ,rect.Position.y, -0.1f , 0.1f);
	glLoadMatrixf(view.getTransform().getMatrix());
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//TESTLOG("Changed camera.")

};

/// Clear the bound buffer
void RendererOpenGL::clearBuffers(){
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glClearColor(m_clearColor.r/255,m_clearColor.g/255,m_clearColor.b/255,m_clearColor.a);
};


void RendererOpenGL::prepare(int w, int h){
	glViewport(0, 0, w, h);

	
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glClearColor(0.1f,0.f,0.3f,0.3f);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(45, (float)width / height, 0.5f, 150);
	glOrtho(0.f,w,h,0.f, -0.1f , 0.1f);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
};

void RendererOpenGL::drawDebugQuad(float x, float y, float angle, float width, float height, Color color){
	glLoadIdentity();
	glPushMatrix();
	glTranslatef(x, y, 0.f);

	glRotatef( angle * (180.f/3.14159), 0 ,0, 1);
	glColor4f(color.r / 255.f, color.g / 255.f ,color.b / 255.f,color.a / 255.f);
	GLfloat vertices[] = {width/2,-height/2,0, -width/2,height/2,0, -width/2,-height/2,0,  width/2,-height/2,0,  width/2,height/2,0, -width/2, height/2,0 };

	glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, vertices);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableClientState(GL_VERTEX_ARRAY);
	glPopMatrix();
}

void RendererOpenGL::drawDebugTriangleFan(Vec2f* vlist, int vcount, Color color){
	glPushMatrix();
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4ub(0.5f * color.r , 0.5f * color.g , 0.5f * color.b, color.a);
	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i < vcount; ++i)
	{
		glVertex2f(vlist[i].x, vlist[i].y);
	}
	glEnd();
	glDisable(GL_BLEND);

	glColor4ub(color.r, color.g, color.b, color.a);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < vcount; ++i)
	{
		glVertex2f(vlist[i].x, vlist[i].y);
	}
	glEnd();
	glPopMatrix();
}

void RendererOpenGL::drawDebugCircle(Vec2f center, float radius, Vec2f axis, Color color){
	const float k_segments = 16.0f;
	const float k_increment = 2.0f * 3.14159 / k_segments;
	float theta = 0.0f;
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4ub(0.5f * color.r, 0.5f * color.g, 0.5f * color.b, color.a);
	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i < k_segments; ++i)
	{		
		Vec2f v = center + Vec2f(cosf(theta), sinf(theta)) * radius;
		glVertex2f(v.x, v.y);
		theta += k_increment;
	}
	glEnd();
	glBlendFunc (GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

	glDisable(GL_BLEND);

	theta = 0.0f;
	glColor4ub(color.r, color.g, color.b, color.a);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < k_segments; ++i)
	{
		Vec2f v = center + Vec2f(cosf(theta), sinf(theta)) * radius;
		glVertex2f(v.x, v.y);
		theta += k_increment;
	}
	glEnd();

	/*Vec2f p = center + radius * axis;
	glBegin(GL_LINES);
	glVertex2f(center.x, center.y);
	glVertex2f(p.x, p.y);
	glEnd();*/
};

void RendererOpenGL::drawVertexArray(VertexArray &vertexArray){
	const char* data = reinterpret_cast<const char*>(&vertexArray.myVertices[0]);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(2, GL_FLOAT, sizeof(Vertex), data + 0);
	glColorPointer(4, GL_UNSIGNED_BYTE,sizeof(Vertex), data + 8);
	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), data + 12);

	/*glCheck(glVertexPointer(2, GL_FLOAT, sizeof(Vertex), data + 0));
	glCheck(glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex), data + 8));
	glCheck(glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), data + 12));*/

	if(vertexArray.geometryType == Triangles)
		glDrawArrays(GL_TRIANGLES, 0, vertexArray.myVertices.size());
	else if(vertexArray.geometryType == TriangleFan)
		glDrawArrays(GL_TRIANGLE_FAN, 0, vertexArray.myVertices.size());

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
};

/// Anything that inherits Drawable can be drawn using a renderer
void RendererOpenGL::draw(Drawable &drawable){
	drawable.onDraw(this);
};

void RendererOpenGL::drawRocketContext(RocketContext* context){
	RocketPlugin::instance().renderInterface()->myRenderer = this;
	context->Render();
	RocketPlugin::instance().renderInterface()->myRenderer = NULL;
}

void RendererOpenGL::display(){
	Engine::instance()->getWindow().swapBuffers();
};

PARABOLA_NAMESPACE_END
#endif