#pragma once
#include <iostream>
#include <math.h>


#include <SDL.h>
#include <glew.h>
#include <glm.hpp>
#include<gtc/matrix_transform.hpp>

#include "ShaderManager.h"
#include "InputManager.h"
#include "Texture.h"
class Quad
{
public:
	Quad();
	~Quad();
	void GenBuffer();
	void FillBuffer();
	void Render();
	void DestroyBuffer();

private:
	Texture m_texture;
	Texture m_texture1;

	

	GLuint m_textureUnit1;
	GLuint m_textureUnit2;

	GLuint texture_flag;
	//sky
	GLuint texture_flag1;

	GLuint isLit_flag;
	
	GLuint vertexAttributeID;
	GLuint colorAttributeID;
	GLuint m_textureAttribute;

	GLuint modelUniformID;
	
	GLuint vertexVBO = 0;
	GLuint colorVBO = 0;
	GLuint m_textureVBO;
	GLuint EBO = 0;
	GLuint VAO = 0;

	GLfloat m_shininess = 1.0f;
	glm::vec3 m_ambient = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 m_diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 m_specular = glm::vec3(1.0f, 1.0f, 1.0f);

	glm::mat4 model = glm::mat4(1.0f);
	glm::vec3 position = glm::vec3(0.0f, -1.2f, 0.0f);
	glm::vec3 scale = glm::vec3(46.0f, 35.0f, 1.0f);
	
	float angle = 90.0f;

};



