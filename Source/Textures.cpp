#include "ParabolaCore/Textures.h"
#include "ParabolaCore/Logger.h"
#include "ParabolaCore/FileInterface.h"


#ifdef PARABOLA_ANDROID

namespace privNS{
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"
};

//#include <ParabolaCore/RendererGLES.h>


namespace
{
	// Convert a string to lower case
	std::string toLower(std::string str)
	{
		for (std::string::iterator i = str.begin(); i != str.end(); ++i)
			*i = static_cast<char>(std::tolower(*i));
		return str;
	}

	// stb_image callbacks that operate on a sf::InputStream
	int read(void* user, char* data, int size)
	{
		pE::ScopedFile* stream = static_cast<pE::ScopedFile*>(user);
		return static_cast<int>(stream->read(data, size));
	}
	void skip(void* user, unsigned int size)
	{
		pE::ScopedFile* stream = static_cast<pE::ScopedFile*>(user);
		stream->seek(stream->tell() + size);
	}
	int eof(void* user)
	{
		pE::ScopedFile* stream = static_cast<pE::ScopedFile*>(user);
		return stream->tell() >= stream->getSize();
	}
}

#endif

#ifdef PARABOLA_ANDROID

#include <GLES/gl.h>
#include <GLUES/glu.h>
#endif

#include <iostream>
#include <map>



PARABOLA_NAMESPACE_BEGIN

std::map<Texture*, Image> m_aliveTextures;

void reloadTextures(){
	for(std::map<Texture*, Image>::iterator it = m_aliveTextures.begin(); it != m_aliveTextures.end(); it++){
		(*it).first->loadFromImage((*it).second);
	}
};


bool Image::loadFromFile(const String &path){
#ifdef PARABOLA_ANDROID

	//in android load through a stream
	ScopedFile* fp = new ScopedFile();	
	if(FileInterface::getAssetFile(fp, path, true)){
		loadFromStream(fp);
		return true;
	}
	delete fp;


	// Clear the array (just in case)
	m_pixels.clear();

	// Load the image and get a pointer to the pixels in memory
	int width, height, channels;
	unsigned char* ptr = privNS::stbi_load(path.c_str(), &width, &height, &channels,privNS::STBI_rgb_alpha);

	if (ptr && width && height)
	{
		// Assign the image properties
		m_size.x = width;
		m_size.y = height;

		// Copy the loaded pixels to the pixel buffer
		m_pixels.resize(width * height * 4);
		memcpy(&m_pixels[0], ptr, m_pixels.size());

		// Free the loaded pixels (they are now in our own pixel buffer)
		privNS::stbi_image_free(ptr);
		// Error, failed to load the image
		std::cout << "Loaded \"" << path << "\". Reason : " << privNS::stbi_failure_reason() << std::endl;
		return true;
	}
	else
	{
		// Error, failed to load the image
		std::cout << "Failed to load image \"" << path << "\". Reason : " << privNS::stbi_failure_reason() << std::endl;

		return false;
	}

#elif defined PARABOLA_DESKTOP
	return myImage.loadFromFile(path);
#endif

}

bool Image::loadFromStream(ScopedFile* stream){
#ifdef PARABOLA_ANDROID

	TESTLOG("Now loading a texture...")
	// Clear the array (just in case)
	m_pixels.clear();

	// Setup the stb_image callbacks
	privNS::stbi_io_callbacks callbacks;
	callbacks.read = &read;
	callbacks.skip = &skip;
	callbacks.eof  = &eof;

	// Load the image and get a pointer to the pixels in memory
	int width, height, channels;
	unsigned char* ptr = privNS::stbi_load_from_callbacks(&callbacks, stream, &width, &height, &channels, privNS::STBI_rgb_alpha);

	if (ptr && width && height)
	{
		// Assign the image properties
		m_size.x = width;
		m_size.y = height;

		// Copy the loaded pixels to the pixel buffer
		m_pixels.resize(width * height * 4);
		memcpy(&m_pixels[0], ptr, m_pixels.size());

		// Free the loaded pixels (they are now in our own pixel buffer)
		privNS::stbi_image_free(ptr);

		return true;
	}
	else
	{
		// Error, failed to load the image
		TESTLOG("Failed to load image from stream. Reason : "/* + privNS::stbi_failure_reason())).c_str()*/);

		return false;
	}
#endif
	return true;
};


void Image::create(unsigned int width, unsigned int height,const Uint8* pixels){
#ifdef PARABOLA_ANDROID
	m_pixels.resize(width*height*4);
	memcpy(&m_pixels[0], pixels, m_pixels.size());
	m_size.x = width;
	m_size.y = height;
#elif defined PARABOLA_DESKTOP
	myImage.create(width, height, pixels);
#endif
}


Vec2i Image::getSize() const{
#ifdef PARABOLA_ANDROID
	return m_size;
#elif defined PARABOLA_DESKTOP
	return Vec2i(myImage.getSize().x, myImage.getSize().y);
#endif
};

const Uint8* Image::getPixelsPtr() const{
#ifdef PARABOLA_ANDROID
	return &m_pixels[0];
#elif defined PARABOLA_DESKTOP
	return myImage.getPixelsPtr();
#endif
};

/// Sets the desired transparency on all pixels with the selected color
void Image::createMaskFromColor(const Color &color, Uint8 alpha){
#ifdef PARABOLA_ANDROID
	// Make sure that the image is not empty
	if (!m_pixels.empty())
	{
		// Replace the alpha of the pixels that match the transparent color
		Uint8* ptr = &m_pixels[0];
		Uint8* end = ptr + m_pixels.size();
		while (ptr < end)
		{
			if ((ptr[0] == color.r) && (ptr[1] == color.g) && (ptr[2] == color.b) && (ptr[3] == color.a))
				ptr[3] = alpha;
			ptr += 4;
		}
	}
#else 
	TESTLOG("attempting to change transparency\n")
	TESTLOG(String::number(color.g).c_str())
	myImage.createMaskFromColor(sf::Color(color.r,color.g,color.b), alpha);

#endif
};

/// Create an uninitialised texture
Texture::Texture() : m_size(0,0), m_actualSize(0,0), m_texture(0), m_pixelsFlipped(false){

	

};

/// RAII release of the texture
Texture::~Texture(){
	//delete the texture if exists
	if(m_texture){
		glDeleteTextures(1, &m_texture);
		PRINTLOG("ParabolaEngine", "Released texture with id: %d\n", m_texture);
		m_aliveTextures.erase(m_aliveTextures.find(this));
	}
};


void Texture::loadFromImage(Image &image){
	m_size = image.getSize();
	m_actualSize = m_size;
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, image.getSize().x, image.getSize().y, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE,  image.getPixelsPtr());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	m_aliveTextures[this] = image;
}

bool Texture::loadFromFile(const String &path){
	TESTLOG(path.c_str())
	Image image;  
#ifdef PARABOLA_ANDROID
	//in android load through a stream
	ScopedFile* fp = new ScopedFile();
	if(FileInterface::getAssetFile(fp, path, true)){
		image.loadFromStream(fp);
	}
	delete fp;
#elif defined PARABOLA_DESKTOP
	image.loadFromFile(path);
#endif
	// STUPID DEBUG THING
	//image.createMaskFromColor(Color(0,128,0, 255), 0);
	loadFromImage(image);
	return true;
}

/// Copy the texture buffer to an image
Image Texture::copyToImage(){

	// Easy case: empty texture
	/*if (!m_texture)
		return Image();

	//ensureGlContext();

	// Make sure that the current texture binding will be preserved
	//priv::TextureSaver save;

	// Create an array of pixels
	std::vector<Uint8> pixels(m_size.x * m_size.y * 4);

	if ((m_size == m_actualSize) && !m_pixelsFlipped)	
	{
		// Texture is not padded nor flipped, we can use a direct copy
		glBindTexture(GL_TEXTURE_2D, m_texture);
		glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, &pixels[0]);


	}
	else
	{
		// Texture is either padded or flipped, we have to use a slower algorithm

		// All the pixels will first be copied to a temporary array
		std::vector<Uint8> allPixels(m_actualSize.x * m_actualSize.y * 4);
		glBindTexture(GL_TEXTURE_2D, m_texture);
		glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, &allPixels[0]);

		// Then we copy the useful pixels from the temporary array to the final one
		const Uint8* src = &allPixels[0];
		Uint8* dst = &pixels[0];
		int srcPitch = m_actualSize.x * 4;
		int dstPitch = m_size.x * 4;
		
		// Handle the case where source pixels are flipped vertically
		if (m_pixelsFlipped)
		{
			src += srcPitch * (m_size.y - 1);
			srcPitch = -srcPitch;
		}

		for (unsigned int i = 0; i < m_size.y; ++i)
		{
			std::memcpy(dst, src, dstPitch);
			src += srcPitch;
			dst += dstPitch;
		}
	}
	*/
	// Create the image
	Image image;
//	image.create(m_size.x, m_size.y, &pixels[0]);

	return image;

	 
};


Vec2i Texture::getSize() const{
	return m_size;
}

/// Sets the desired transparency on all pixels with the selected color
void Texture::createMaskFromColor(const Color &color, Uint8 alpha){
	Image img = this->copyToImage();
	img.createMaskFromColor(color, alpha);
	loadFromImage(img); 
};

void Texture::bind() const{
	glBindTexture(GL_TEXTURE_2D, m_texture);
};

/************************************************************************/
/* Texture                                                              */
/************************************************************************/
/*void Texture::maskColor(const Color &color, unsigned char alpha){
	sf::Image img = this->copyToImage();
	img.createMaskFromColor(color, alpha);
	loadFromImage(img);
};

/// Get the size of the texture
Vec2f Texture::getSize(){
	return Vec2f(sf::Texture::getSize().x,sf::Texture::getSize().y);
};*/

PARABOLA_NAMESPACE_END