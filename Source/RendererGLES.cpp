#include "ParabolaCore/Platform.h"
#include "ParabolaCore/Engine.h"
#include <stdlib.h>
#include <cmath>

#ifdef PARABOLA_GLES

#include <ParabolaCore/RendererGLES.h>

#ifdef PARABOLA_ANDROID
#include <GLES/gl.h>
#else
#include <OpenGLES/ES1/gl.h>
#endif

PARABOLA_NAMESPACE_BEGIN

RendererGLES::RendererGLES() : Renderer(){
	
};


void RendererGLES::applyView(const View &view){
	if(!m_renderTarget) return;
    
    
	IntRect viewport = ((Window*)m_renderTarget)->getViewport(view);
	int top = m_renderTarget->getSize().y - (viewport.top + viewport.height);
	glViewport(viewport.left, top, viewport.width, viewport.height);
    
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(45, (float)width / height, 0.5f, 150);
	FloatRect rect = view.getRect();
	//glOrtho(rect.left, rect.width , rect.height ,rect.top, -0.1f , 0.1f);
	glLoadMatrixf(view.getTransform().getMatrix());
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//TESTLOG("Changed camera.")

};

/// Clear the bound buffer
void RendererGLES::clear(){
	glClear(GL_COLOR_BUFFER_BIT);
	//m_clearColor = Color(255,0,0);
	glClearColor(m_clearColor.r/255,m_clearColor.g/255,m_clearColor.b/255,m_clearColor.a/255);
};


void RendererGLES::prepare(int w, int h){
	glViewport(0, 0, w, h);
	
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColorx((GLfixed)(0.3f * 65536),
		(GLfixed)(0.0f * 65536),
		(GLfixed)(0.1f * 65536), 0x10000);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(45, (float)width / height, 0.5f, 150);
	glOrthof(0,w,h,0, -1.f , 1.f);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
};

void RendererGLES::drawDebugQuad(float x, float y, float angle, float width, float height, Color color){
	glLoadIdentity();
	glPushMatrix();
	glTranslatef(x, y, 0.f);

	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//TESTLOG("DRAWING...")

	glRotatef( angle * (180.f/3.14159), 0 ,0, 1);
	//glTranslatef(30,40,0);
	glColor4f(color.r / 255.f, color.g / 255.f ,color.b / 255.f,color.a / 255.f);

	GLfloat vertices[] = {width/2,-height/2,0, -width/2,height/2,0, -width/2,-height/2,0,  width/2,-height/2,0,  width/2,height/2,0, -width/2, height/2,0 };


	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_BLEND);
	glPopMatrix();
}

void RendererGLES::drawDebugTriangleFan(Vec2f* vlist, int vcount, Color color){
	glPushMatrix();
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(0.8f * color.r / 255, 0.8f * color.g / 255, 0.8f * color.b / 255, color.a);
	
	glEnableClientState(GL_VERTEX_ARRAY); 
	glVertexPointer(2, GL_FLOAT, 0, &vlist[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, vcount);
	glDisableClientState(GL_VERTEX_ARRAY);

	glDisable(GL_BLEND);

	glColor4f(color.r/255, color.g/255, color.b/255, color.a);
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, &vlist[0]);
	glDrawArrays(GL_LINE_LOOP, 0, vcount);
	glDisableClientState(GL_VERTEX_ARRAY);

	glPopMatrix();
};

void RendererGLES::drawDebugLine(Vec2f begin, Vec2f end, Color color){
	glLoadIdentity();
	glPushMatrix();
//	glPushAttrib(GL_ENABLE_BIT); 
	/*glLineStipple(1, 0xAAAA);
	glEnable(GL_LINE_STIPPLE);*/

	glLineWidth(1);

	glColor4f(color.r / 255.f, color.g / 255.f ,color.b / 255.f,color.a / 255.f);
	GLfloat vertices[] = {begin.x,begin.y,0, end.x,end.y,0};

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glDrawArrays(GL_LINES, 0, 2);
	glDisableClientState(GL_VERTEX_ARRAY);
	//glPopAttrib();
	glPopMatrix();
};

void RendererGLES::drawDebugCircle(Vec2f center, float radius, Vec2f axis, Color color){
	const float k_segments = 16.0f;
	const float k_increment = 2.0f * 3.14159 / k_segments;
	float theta = 0.0f;
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(0.5f * color.r / 255, 0.5f * color.g / 255, 0.5f * color.b / 255, color.a);

	Vec2f* vlist = new Vec2f[16];
	for (int i = 0; i  < k_segments; ++i)
	{		
		vlist[i] = center + Vec2f(cosf(theta), sinf(theta)) * radius;
		theta += k_increment;
	}
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, &vlist[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, k_segments);
	glDisableClientState(GL_VERTEX_ARRAY);

	
	glBlendFunc (GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

	glDisable(GL_BLEND);

	theta = 0.0f;
	glColor4f(color.r/255, color.g/255, color.b/255, 0.78f);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, &vlist[0]);
	glDrawArrays(GL_LINE_LOOP, 0, k_segments);
	glDisableClientState(GL_VERTEX_ARRAY);
};


void RendererGLES::drawVertexArray(VertexArray &vertexArray){
		const char* data = reinterpret_cast<const char*>(&vertexArray.m_vertices[0]);

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
		glDrawArrays(GL_TRIANGLES, 0, vertexArray.m_vertices.size());
	else if(vertexArray.geometryType == TriangleFan)
		glDrawArrays(GL_TRIANGLE_FAN, 0, vertexArray.m_vertices.size());

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
};

/// Anything that inherits Drawable can be drawn using a renderer
void RendererGLES::draw(Drawable &drawable){
	drawable.onDraw(this);
};

void RendererGLES::drawRocketContext(RocketContext* context){
	RocketPlugin::instance().renderInterface()->myRenderer = this;
	context->Render();
	RocketPlugin::instance().renderInterface()->myRenderer = NULL;
}


void RendererGLES::display(){
#ifdef PARABOLA_ANDROID
	AndroidInterface::requestFrameRender();
#endif
};

PARABOLA_NAMESPACE_END
#endif