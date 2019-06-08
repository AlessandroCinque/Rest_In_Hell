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
class Cube
{
public:
	Cube();
	~Cube();
	void GenBuffer();
	void FillBuffer();
	void Render();
	void DestroyBuffer();
	void Inputs();

private:
	Texture texture;
	GLuint texture_flag;
	GLuint m_textureVBO;
	GLuint m_textureAttributeID;

	GLuint vertexAttributeID;
	GLuint colorAttributeID;
	GLuint modelUniformID; //= glGetUniformLocation(TheShader::Instance()->GetShaderProgram(), "model");
	GLuint vertexVBO = 0;
	GLuint colorVBO = 0;
	GLuint EBO = 0;
	GLuint VAO = 0;
	glm::mat4 model = glm::mat4(1.0f);
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
	float angle = 0.0f;
};

