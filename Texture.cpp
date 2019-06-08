#include "Texture.h"
#include <SDL_image.h>



Texture::Texture()
{
}


Texture::~Texture()
{
}
//create map on the heap
std::map<std::string, GLuint>* Texture::s_textureIDMap= new std::map<std::string,GLuint>;
//load textures into memory
bool Texture::Load(const std::string & filename, const std::string & textureID)
{
	//var for image data
	unsigned char* pixels = nullptr;
	unsigned int width = 0;
	unsigned int height = 0;
	unsigned int depth = 0;
	unsigned int format = 0;
	//pointer to raw image data
	SDL_Surface* textureData;
	// c_str make a string an arrays of char
	textureData = IMG_Load(filename.c_str());

	if (!textureData) 
	{
		std::cout << "Could not load the image" << std::endl;
	}
	//assigning images to our varibles
	pixels = (unsigned char*)textureData->pixels;
	width = textureData->w;
	height = textureData->h;
	depth = textureData->format->BytesPerPixel;
	format = (depth == 4) ? GL_RGBA : GL_RGB;
	//Text obj
	glGenTextures(1, &m_ID);

	//check out TEXTURE FILTERING; FOR MORE CREDITS make a better version of this

	//setting magnification and minification + filtering
	glBindTexture(GL_TEXTURE_2D, m_ID);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//set wrap filtering
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//creating the actual obj
	glTexImage2D(GL_TEXTURE_2D, 0,format,width,height,0,format,GL_UNSIGNED_BYTE,pixels);

	//setting free the SDl image
	SDL_FreeSurface(textureData);

	glBindTexture(GL_TEXTURE_2D, 0);

	//add texture ID
	s_textureIDMap->insert(std::pair<std::string, GLuint>(textureID, m_ID));


	return true;
}

void Texture::Unload()
{
	glDeleteTextures(1, &m_ID);
}
//========================= MODELS STUFF ====================================
void Texture::Unload(std::string ModID)
{
	//use the functionalities of the map for cancel that element
	s_textureIDMap->erase(ModID);
}

void Texture::Bind()
{
	
	glBindTexture(GL_TEXTURE_2D, 0);

}

GLuint Texture::GetID()
{
	return m_ID;
}
