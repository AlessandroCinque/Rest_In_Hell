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
class SkyBox
{
public:
	SkyBox();
	~SkyBox();
	void GenBuffer();
	void FillBuffer();
	void Render();
	void DestroyBuffer();

private:
	Texture m_texture;

	GLuint texture_flag;
	GLuint texture_flag1;
	GLuint isLit_flag;

	GLuint m_textureUnit1;

	GLuint vertexAttributeID;
	GLuint colorAttributeID;
	GLuint m_textureAttribute;
	GLuint m_normalAttributeID;

	GLuint modelUniformID; //= glGetUniformLocation(TheShader::Instance()->GetShaderProgram(), "model");
	

	GLuint m_normalVBO;
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
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 scale = glm::vec3(100.0f, 100.0f, 100.0f);

	float angle = 0.0f;
};

