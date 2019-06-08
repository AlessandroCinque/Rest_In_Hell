#pragma once
#include<map>
#include<iostream>
#include<string>
#include<glew.h>

class Texture
{
public:
	Texture();
	~Texture();
	bool Load(const std::string& filename,const std::string& textureID);
	void Unload();
	//===== modes stuff =======
	void Unload(std::string ModID);
	void Bind();
	GLuint GetID();
	static std::map<std::string, GLuint>* s_textureIDMap;
private:
	GLuint m_ID;
	//===== modes stuff =======
	
	GLuint m_textureAttribute;


	GLuint m_textureVBO;
	GLuint VAO = 0;


	
	//static belongs to all the objects
};

