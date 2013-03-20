#include "ParabolaCore/CGL.h"
#include "ParabolaCore/Math.h"
#include "ParabolaCore/3DView.h"

#include "LightingTest.h"

#include <iostream>
using namespace std;



View3D view;
View3D vv;

class GLFramebuffer
{
public:
	GLFramebuffer() : m_id(0)
	{
		
	}

	void create()
	{
		TESTLOG("Preparing framebuffer\n");
		glGenFramebuffersCGL(1, &m_id);

		bind();

		m_texture.create(480, 320);
		m_texture.m_pixelsFlipped = true;

		glFramebufferTexture2DCGL(GL_FRAMEBUFFER_CGL, GL_COLOR_ATTACHMENT0_CGL, GL_TEXTURE_2D, m_texture.m_texture, 0);

		GLenum DrawBuffers[2] = {GL_COLOR_ATTACHMENT0_CGL};
		//glDrawBuffers(1, DrawBuffers);

		if(glCheckFramebufferStatusCGL(GL_FRAMEBUFFER_CGL) == GL_FRAMEBUFFER_COMPLETE_CGL)
		{
			TESTLOG("Framebuffer is OK!\n");
		} 
	}

	void bind()
	{
		glBindFramebufferCGL(GL_FRAMEBUFFER_CGL, m_id);
	}

	void unbind()
	{
		glBindFramebufferCGL(GL_FRAMEBUFFER_CGL, 0);
	}

	GLuint m_id;
	Texture m_texture;
};
GLFramebuffer fbo;



class ParticleSystem
{
public:
	ParticleSystem()
	{

	}

	void create()
	{
		Image im;
		im.loadFromFile("part.png");
		im.createMaskFromColor(Color(0,0,0), 0);
		m_t.loadFromImage(im);
		m_timer.reset();
		actime = 0;


		gravity = Vec2f(1, -17);
	}

	void render(Renderer* renderer)
	{
		//update
		float elapsedTime = m_timer.getElapsedTime().asSeconds();
		m_timer.reset();
		actime += elapsedTime;

		float addInterval = 0.01f;
		while(actime > addInterval)
		{
			// 1 particle
			Sprite particle;
			particle.setPosition(m_pos.x + Math::random(-15,15), m_pos.y + Math::random(-15,15));
			particle.setTexture(m_t);
			particle.setOrigin(m_t.getSize().x / 2, m_t.getSize().y / 2);
			particle.resize(50,50);
			particle.setColor(Color(Math::random(150,255),Math::random(50,70),10,255));
			particle.m_blendMode = Blend::Add;
			m_particles.push_back(particle); 
			actime -= addInterval;
		}
		

		for(unsigned int i = 0; i < m_particles.size(); i++)
		{
			m_particles[i].setPosition(m_particles[i].getPosition().x + gravity.x * elapsedTime, m_particles[i].getPosition().y + gravity.y * elapsedTime);
		}

		for(unsigned int i = 0; i < m_particles.size(); i++)
		{			
			renderer->draw(m_particles[i]);
		}
	}
	 
	std::vector<Sprite> m_particles;

	float actime;
	Texture m_t;
	Clock m_timer;
	Vec2f m_pos;
	Vec2f gravity;
};

ParticleSystem spark;




static const char gVertexShader2[] =
	"#version 330\n"
	
	"in vec4 vPosition;\n"
	"in vec4 ccc;"
	"uniform mat4 projectionMatrix;"
	"uniform mat4 modelViewMatrix;"
	"out vec4 fcolor;"
	"void main() {\n"
	"  gl_Position = projectionMatrix * modelViewMatrix * vPosition;\n"
	"  fcolor = ccc;"
	"}\n";

static const char gFragmentShader2[] = 
	"#version 330\n"
	"in vec4 fcolor;"
	"out vec4 output;"
	"void main() {\n"
	"  output = fcolor;\n"
	"}\n";

static const char gVertexShader[] = 
	"attribute vec4 vPosition;\n"
	"attribute vec4 ccc;"
	"varying vec4 finalColor;"
	"uniform mat4 projectionMatrix;"
	"uniform mat4 modelViewMatrix;"
	"void main() {\n"
	"  gl_Position = projectionMatrix * modelViewMatrix * vPosition;\n"
	"  finalColor = ccc;"
	"}\n";

static const char gFragmentShader[] = 
	"precision mediump float;\n"
	"varying vec4 finalColor;"
	"void main() {\n"
	"  gl_FragColor = finalColor;\n"
	"}\n";

class Shader
{
public:
	unsigned int id;




	GLuint loadShader(GLenum shaderType, const char* pSource) {
		GLuint shader = glCreateShader(shaderType);
		if (shader) {
			glShaderSource(shader, 1, &pSource, NULL);
			glCompileShader(shader);
			GLint compiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
			if (!compiled) {
				GLint infoLen = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
				if (infoLen) {
					char* buf = (char*) malloc(infoLen);
					if (buf) {
						glGetShaderInfoLog(shader, infoLen, NULL, buf);
						PRINTLOG("GLES 2.0", "Failed to load shader: %s\n", buf);							
						free(buf);
					}
					glDeleteShader(shader);
					shader = 0;
				}
			}
		}
		return shader;
	}

	GLuint createProgram(const char* pVertexSource, const char* pFragmentSource) {
		GLuint vertexShader = loadShader(GL_VERTEX_SHADER, pVertexSource);
		if (!vertexShader) {
			return 0;
		}

		GLuint pixelShader = loadShader(GL_FRAGMENT_SHADER, pFragmentSource);
		if (!pixelShader) {
			return 0;
		}

		GLuint program = glCreateProgram();
		if (program) {
			glAttachShader(program, vertexShader);
		
			glAttachShader(program, pixelShader);
			
			glLinkProgram(program);
			GLint linkStatus = GL_FALSE;
			glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
			if (linkStatus != GL_TRUE) {
				GLint bufLength = 0;
				glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
				if (bufLength) {
					char* buf = (char*) malloc(bufLength);
					if (buf) {
						glGetProgramInfoLog(program, bufLength, NULL, buf);
						PRINTLOG("GLES 2.0", "Failed to link shader program: %s\n", buf);
						free(buf);
					}
				}
				glDeleteProgram(program);
				program = 0;
			}
		}
		return program;
	}
	void create()
	{
#if defined PARABOLA_ANDROID
		id = createProgram(gVertexShader, gFragmentShader);
#else
		id = createProgram(gVertexShader2, gFragmentShader2);
#endif

		position = glGetAttribLocation(id, "vPosition");
		colors = glGetAttribLocation(id, "ccc");
		projection = glGetUniformLocation(id, "projectionMatrix");
		modelview = glGetUniformLocation(id, "modelViewMatrix");
		if(projection == -1)
		{
			TESTLOG("FAILED TO FIND PROJECTION MATRIX IN THE SHADER")
		}
		glViewport(0,0,480,320);
	}

	unsigned int colors;
	unsigned int projection;
	unsigned int position;
	unsigned int modelview;
};

Shader program;

void LightingTest::onCreate()
{
	cout<<"[Lighting] Started."<<endl;
	m_render = Renderer::createAutomaticRenderer(&getWindow());

	carTexture.loadFromFile("zonda.jpg");
	carSprite.setTexture(carTexture);
	carSprite.resize(480,320);

	spark.create();

	m_lighting = true;

	spark.m_pos = m_pos = Vec2f(200,200);

	cglPrepareExtensions();
	fbo.create();

	view.m_eye = Vec3f(0,0,-40);
	view.m_center = Vec3f(0,0,40);
	view.m_up = Vec3f(0,1,0);

	vv.m_center = Vec3f(0, 40 , 0);
	vv.m_eye = Vec3f(0, 40 , -250);
	vv.m_up = Vec3f(0, 1, 0);

	const GLubyte* s = glGetString(GL_SHADING_LANGUAGE_VERSION);
	PRINTLOG("p", "GLSL: %s\n", s);

	program.create();
}

void drawRect(float x, float y, float angle, float width, float height, Color color, bool withShader = false)
{
	glLoadIdentity();
	glPushMatrix();
	glTranslatef(x, y, 0.f);

	if(withShader)
	{
		Transform translation;
		translation.translate(x,y);
		glUniformMatrix4fv(program.modelview, 1, GL_FALSE, translation.getMatrix());		
	}

	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFunc(GL_DST_COLOR, GL_SRC_ALPHA);
	//glBlendFunc(GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFunc( GL_SRC_ALPHA, GL_ONE);
	//glBlendFunc(GL_DST_COLOR, GL_ZERO);
	glRotatef( angle * (180.f/3.14159), 0 ,0, 1);
//	glColor4f(color.r / 255.f, color.g / 255.f ,color.b / 255.f,color.a / 255.f);
	GLfloat vertices[] = {width/2,-height/2,0, -width/2,height/2,0, -width/2,-height/2,0,  width/2,-height/2,0,  width/2,height/2,0, -width/2, height/2,0 };
	GLfloat colors[] = {color.r / 255.f, color.g / 255.f ,color.b / 255.f,color.a / 255.f,color.r / 255.f, color.g / 255.f ,color.b / 255.f,color.a / 255.f,color.r / 255.f, color.g / 255.f ,color.b / 255.f,color.a / 255.f,color.r / 255.f, color.g / 255.f ,color.b / 255.f,color.a / 255.f,color.r / 255.f, color.g / 255.f ,color.b / 255.f,color.a / 255.f,color.r / 255.f, color.g / 255.f ,color.b / 255.f,color.a / 255.f};

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);


	if(withShader)
	{
		glEnableVertexAttribArray(program.colors);
		glVertexAttribPointer(program.colors, 4, GL_FLOAT, GL_FALSE, 0, colors);

		glEnableVertexAttribArray(program.position);
		glVertexAttribPointer(program.position, 3, GL_FLOAT, GL_FALSE, 0, vertices);
	}
	else
	{
		glVertexPointer(3, GL_FLOAT, 0, vertices);
		glColorPointer(4, GL_FLOAT, 0, colors);
	}

	glDrawArrays(GL_TRIANGLES, 0, 6);

	if(withShader)
	{
		//glDisableVertexAttribArray(program.position);
		glDisableVertexAttribArray(program.position);
		glDisableVertexAttribArray(program.colors);
	}

	glDisable(GL_BLEND);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	glPopMatrix();
}

Vec2f currMouse;
bool movingF = false;
void LightingTest::onEvent(Event &event)
{
	if(event.type == Event::KeyPressed && event.key.code == Keyboard::A) m_pos.x -= 10;
	if(event.type == Event::KeyPressed && event.key.code == Keyboard::D) m_pos.x += 10;
	if(event.type == Event::KeyPressed && event.key.code == Keyboard::W) m_pos.y += 10;
	if(event.type == Event::KeyPressed && event.key.code == Keyboard::S) m_pos.y -= 10;
	if(event.type == Event::TouchMoved){m_pos.x = event.x;m_pos.y = event.y;}
	if(event.type == Event::KeyPressed && event.key.code == Keyboard::Space) m_lighting = !m_lighting;


	if(event.type == Event::KeyPressed && event.key.code == Keyboard::W) movingF = true;
	if(event.type == Event::KeyReleased && event.key.code == Keyboard::W) movingF = false;
	if(event.type == Event::KeyPressed && event.key.code == Keyboard::S) view.backward(5);
	if(event.type == Event::KeyPressed && event.key.code == Keyboard::A) view.strafe(-1);
	if(event.type == Event::KeyPressed && event.key.code == Keyboard::D) view.strafe(1);


	if(event.type == Event::KeyPressed && event.key.code == Keyboard::W) { vv.m_center.y += 5; vv.m_eye.y += 5;};
	if(event.type == Event::KeyPressed && event.key.code == Keyboard::S) { vv.m_center.y -= 5; vv.m_eye.y -= 5;};
	if(event.type == Event::KeyPressed && event.key.code == Keyboard::A) { vv.m_center.x += 5; vv.m_eye.x += 5;};
	if(event.type == Event::KeyPressed && event.key.code == Keyboard::D) { vv.m_center.x -= 5; vv.m_eye.x -= 5;};

	if(event.type == Event::MouseMoved)
	{
		currMouse.x = event.mouseMove.x;
		currMouse.y = event.mouseMove.y;

		m_pos = currMouse;
/*
		if(currMouse.x < 235)
		{
			view.rotateH(-0.05);

			//reset
			getWindow().setMousePosition(Vec2i(240,160));
		}
		else if(currMouse.x > 245)
		{
			view.rotateH(0.05);

			//reset
			getWindow().setMousePosition(Vec2i(240,160));
		}*/

		
	}

	if(event.type == Event::Closed || event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) close();

	spark.m_pos = m_pos;
}

float mAngle = 0.f;

void LightingTest::onUpdate(Time time)
{
	float elapsedTime = time.asSeconds();


	/*
	/// Increment the angle a bit every frame
	mAngle += elapsedTime * 0.2f;

	// Perform calculations for hover camera
	float dist = Vec3f(view.m_center - view.m_eye).length();

	view.m_eye.x = cos(mAngle) * 60;
	view.m_eye.z = sin(mAngle) * 60;

	if(mAngle > 360.f) mAngle -= 360.f;*/

	if(movingF)
	{
		view.forward(elapsedTime * 10);
	}
}
const GLfloat gTriangleVertices[] = { 0.0f, 0.5f, -0.5f, -0.5f,
	0.5f, -0.5f };


void LightingTest::onRender()
{
	m_render->clearBuffers();
	glClear(GL_DEPTH_BUFFER_BIT);

	glUseProgram(0);

	View mView;
	mView.setRect(0,0,480,320);
	m_render->setView(mView);

	//glUseProgram(0);

	//drawRect(0,0,0,100,100,Color::Red);

	

	m_render->draw(carSprite);

	spark.render(m_render);
	
	fbo.bind();

		glClear(GL_COLOR_BUFFER_BIT);

		/// Full darkness
		m_render->drawDebugQuad(240,160,0,480,320,Color(0,0,0,255));

		// Lighting
		drawRect(m_pos.x, m_pos.y, 0, 100, 100, Color(255,255,255,200));

		drawRect(0,0,Math::pi/4, 400,150, Color(240,200,240, 200));

	fbo.unbind();
	
	if(m_lighting)
	{
		Sprite overlay;
		overlay.m_blendMode = Blend::Multiply;
		overlay.setTexture(fbo.m_texture);
		m_render->draw(overlay);
	}
	
	Text t;
	t.setString("Particle Count: " + String::number(spark.m_particles.size()));
	m_render->draw(t);




	/*

	vv.apply();
	
	m_render->draw(carSprite);
	m_render->drawDebugCircle(Vec2f(vv.m_center.x, vv.m_center.y), 8, Vec2f(1,0), Color::White);
	//m_render->drawCube(0,0,-50, 100, Color::Red);

	for(int i = 0; i < 100; i++)
	{
		for(int j = 0; j < 100; j++)
		{

			m_render->drawCube(i * 180,j * 140,-50, 100, Color::Red);
		}
	}
	
	*/
	

	//glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	
	//glUseProgram(program.id);
	//glEnableVertexAttribArray(program.position);
//	glVertexAttribPointer(program.position, 2, GL_FLOAT, GL_FALSE, 0, gTriangleVertices);
	
	/*glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, gTriangleVertices);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, 3);*/
	//glDisableVertexAttribArray(0);
	
	glUseProgram(program.id);

	// lets get the projection matrix
	glUniformMatrix4fv(program.projection, 1, GL_FALSE, mView.getTransform().getMatrix());
	//glUniformMatrix4fv(program.projection, 1, GL_FALSE, Transform::Identity.getMatrix());
	
	drawRect(480 / 2,320 / 2, 0, 200, 200, Color(200,100,150, 200), true);

	m_render->display();
	getWindow().swapBuffers();
}
