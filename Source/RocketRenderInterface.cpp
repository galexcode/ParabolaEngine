
#include "ParabolaCore/RocketRenderInterface.h"
#include "ParabolaCore/Vectors.h"
#include "ParabolaCore/SceneRenderer.h"

#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

#ifdef PARABOLA_WINDOWS
#include <windows.h>
#endif
#include <GL/GL.h>

using namespace std;

#define GL_CLAMP_TO_EDGE 0x812F

PARABOLA_NAMESPACE_BEGIN

	/*class RocketOpenGLRendererGeometryHandler
	{
	public:
		unsigned int VertexID, IndexID, ImageID;
		int NumVertices;
	    Rocket::Core::TextureHandle Image;

		RocketOpenGLRendererGeometryHandler() : VertexID(0), IndexID(0), ImageID(0), NumVertices(0)
		{
		};

		~RocketOpenGLRendererGeometryHandler()
		{
			if(VertexID)
				glDeleteBuffers(1, &VertexID);

			if(IndexID)
				glDeleteBuffers(1, &IndexID);

			VertexID = IndexID = 0;
		};
	};*/

	/*class RocketOpenGLRendererVertex
	{
	public:
		RocketOpenGLRendererVertex(){}
		Vec2f Position, TexCoord;
		Vec4f Color;
	};*/


	RocketRenderInterface::RocketRenderInterface(){
		states = NULL;
		target = NULL;
	}

	RocketRenderInterface::~RocketRenderInterface(){
		
	};


	// Called by Rocket when it wants to render geometry that it does not wish to optimise.
	void RocketRenderInterface::RenderGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, const Rocket::Core::TextureHandle Image, const Rocket::Core::Vector2f& translation)
	{
	

		if(!target)return;

		target->SetView(target->GetDefaultView());

		target->PushGLStates();
		//glPushMatrix();
		
		sf::VertexArray v(sf::Triangles, num_indices);
		for(int j = 0; j < num_indices; j++){ //iterate indices
			int i = indices[j]; //i is the vertex position.
			v[j].Position = sf::Vector2f(vertices[i].position.x, vertices[i].position.y);
			v[j].Color = sf::Color(vertices[i].colour.red,vertices[i].colour.green,vertices[i].colour.blue, vertices[i].colour.alpha);
			if(Image){
				v[j].TexCoords = sf::Vector2f(vertices[i].tex_coord.x*((sf::Texture*)Image)->GetWidth(), vertices[i].tex_coord.y*((sf::Texture*)Image)->GetHeight());
			}
			//std::cout<<"tx: "<<v[j].TexCoords.x<<";"<<v[j].TexCoords.y<<std::endl;
		}
		states->BlendMode = sf::BlendAlpha;
		states->Texture = (sf::Texture*)Image;
		states->Transform = sf::Transform::Identity;
		states->Transform.Translate(translation.x, translation.y);

		target->Draw(v, *states);

		target->PopGLStates();
		


	/*	glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, 1024, 768,0, -1, 1 );
		glMatrixMode(GL_MODELVIEW);
		glViewport(0, 0, 1024, 768);*/


		/*
		glPushMatrix();
		glLoadIdentity();
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
		
		glTranslatef(translation.x, translation.y, 0);		

		glVertexPointer(2, GL_FLOAT, sizeof(Rocket::Core::Vertex), &vertices[0].position);
		glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Rocket::Core::Vertex), &vertices[0].colour);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		if (Image == NULL)
		{
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		else
		{
			sf::Texture *image = (sf::Texture *)Image;
			image->Bind();
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(2, GL_FLOAT, sizeof(Rocket::Core::Vertex), &vertices[0].tex_coord);
		}
		
		glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, indices);
		glDisable(GL_BLEND);


		glBindTexture(GL_TEXTURE_2D, 0);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);

		glPopMatrix();*/

	}
 
	// Called by Rocket when it wants to compile geometry it believes will be static for the forseeable future.		
	Rocket::Core::CompiledGeometryHandle RocketRenderInterface::CompileGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, const Rocket::Core::TextureHandle Image)
	{
	
		//if(!GLEE_VERSION_2_0)			
			return (Rocket::Core::CompiledGeometryHandle)NULL;		

/*
		vector<RocketOpenGLRendererVertex> Data;
		Data.resize(num_vertices);

		for(int i = 0; i < num_vertices; i++)
		{
			Data[i].Position = *(Vec2f*)&vertices[i].position;
			Data[i].TexCoord = *(Vec2f*)&vertices[i].tex_coord;
			Data[i].Color = Vec4f(float(vertices[i].colour.red) * 255, float(vertices[i].colour.green) * 255,
				float(vertices[i].colour.blue) * 255, float(vertices[i].colour.alpha) * 255);
		}

		RocketOpenGLRendererGeometryHandler *Geometry = new RocketOpenGLRendererGeometryHandler();
		Geometry->NumVertices = num_indices;

		glGenBuffers(1, &Geometry->VertexID);
		glBindBuffer(GL_ARRAY_BUFFER, Geometry->VertexID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(RocketOpenGLRendererVertex) * num_vertices, &Data[0],
			GL_STATIC_DRAW);

		glGenBuffers(1, &Geometry->IndexID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Geometry->IndexID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * num_indices, indices, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		Geometry->Image = Image;

		return (Rocket::Core::CompiledGeometryHandle)Geometry;*/
	};

	// Called by Rocket when it wants to render application-compiled geometry.		
	void RocketRenderInterface::RenderCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry, const Rocket::Core::Vector2f& translation)
	{
		/*RocketOpenGLRendererGeometryHandler *RealGeometry = (RocketOpenGLRendererGeometryHandler *)geometry;

		
		glPushMatrix();
		glTranslatef(translation.x, translation.y, 0);
		//glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		sf::Texture *image = (sf::Texture*)RealGeometry->Image;

		if(image)
		{
			image->Bind();
		}
		else
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		};

		glEnable(GL_VERTEX_ARRAY);
		glEnable(GL_TEXTURE_COORD_ARRAY);
		glEnable(GL_COLOR_ARRAY);

	#define BUFFER_OFFSET(x) ((char*)0 + x)

		glBindBuffer(GL_ARRAY_BUFFER, RealGeometry->VertexID);
		glVertexPointer(2, GL_FLOAT, sizeof(RocketOpenGLRendererVertex), BUFFER_OFFSET(0));
		glTexCoordPointer(2, GL_FLOAT, sizeof(RocketOpenGLRendererVertex), BUFFER_OFFSET(sizeof(Vec2f)));
		glColorPointer(4, GL_FLOAT, sizeof(RocketOpenGLRendererVertex), BUFFER_OFFSET(sizeof(Vec4f)));

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RealGeometry->IndexID);
		glDrawElements(GL_TRIANGLES, RealGeometry->NumVertices, GL_UNSIGNED_INT, BUFFER_OFFSET(0));

		glBindBuffer(GL_ARRAY_BUFFER, 0);


		glDisable(GL_COLOR_ARRAY);
		glDisable(GL_TEXTURE_COORD_ARRAY);
		glDisable(GL_VERTEX_ARRAY);

		//glColor4f(1, 1, 1, 1);

		glPopMatrix();*/
	}

	// Called by Rocket when it wants to release application-compiled geometry.		
	void RocketRenderInterface::ReleaseCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry)
	{
		//delete (RocketOpenGLRendererGeometryHandler *)geometry;
	}

	// Called by Rocket when it wants to enable or disable scissoring to clip content.		
	void RocketRenderInterface::EnableScissorRegion(bool enable)
	{
		if (enable)
			glEnable(GL_SCISSOR_TEST);
		else
			glDisable(GL_SCISSOR_TEST);
	}

	// Called by Rocket when it wants to change the scissor region.
	void RocketRenderInterface::SetScissorRegion(int x, int y, int width, int height)
	{
		glScissor(x, 768 - (y + height), width, height);
	}

	// Called by Rocket when a Image is required by the library.		
	bool RocketRenderInterface::LoadTexture(Rocket::Core::TextureHandle& Image_handle, Rocket::Core::Vector2i& Image_dimensions, const Rocket::Core::String& source)
	{
		

		
		sf::Texture *texture = new sf::Texture();

		if(!texture->LoadFromFile(source.CString()))
		{
			delete texture;

			return false;
		};

		Image_handle = (Rocket::Core::TextureHandle) texture;
		Image_dimensions = Rocket::Core::Vector2i(texture->GetWidth(), texture->GetHeight());

		return true;
	}

	// Called by Rocket when a Image is required to be built from an internally-generated sequence of pixels.
	bool RocketRenderInterface::GenerateTexture(Rocket::Core::TextureHandle& Image_handle, const Rocket::Core::byte* source, const Rocket::Core::Vector2i& source_dimensions)
	{
		sf::Image *image = new sf::Image();
		sf::Texture *texture = new sf::Texture();

		image->Create(source_dimensions.x, source_dimensions.y, source);

		texture->LoadFromImage(*image);
		Image_handle = (Rocket::Core::TextureHandle)texture;

		return true;
	}

	// Called by Rocket when a loaded Image is no longer required.		
	void RocketRenderInterface::ReleaseTexture(Rocket::Core::TextureHandle Image_handle)
	{
		delete (sf::Texture*)Image_handle;
	}

PARABOLA_NAMESPACE_END