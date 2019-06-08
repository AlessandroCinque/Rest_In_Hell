#pragma once
#include <iostream>
#include <math.h>


#include <SDL.h>
#include <glew.h>
#include <glm.hpp>
#include<gtc/matrix_transform.hpp>

#include "ShaderManager.h"
#include "InputManager.h"
class Light
{
public:
	Light();
	~Light();
	void Create();
	void Draw();
	void Destroy();
	void SetColor(GLfloat r, GLfloat g, GLfloat b);
	void Inputs();
	//For testing purposes
	glm::vec3 GetPosition() { return m_position; }
private:

	GLuint texture_flag;
	GLuint texture_flag1;
	GLuint isLit_flag;

	GLuint vertexAttributeID = 0;
	GLuint colorAttributeID = 0;
	GLuint modelUniformID = 0; //= glGetUniformLocation(TheShader::Instance()->GetShaderProgram(), "model");
	GLuint LightUniformID = 0;

	//=======================================================
	glm::vec3 m_lightColor = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 m_ambient = glm::vec3(0.1f, 0.1f, 0.1f);
	glm::vec3 m_diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
	glm::vec3 m_specular = glm::vec3(1.0f, 1.0f, 1.0f);

	GLuint vertexVBO = 0;
	GLuint colorVBO = 0;
	GLuint VAO = 0;
	glm::vec3 m_position = glm::vec3(0.0f, 54.0f, -27.5f);
	glm::vec3 m_color = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::mat4 model = glm::mat4(1.0f);
};

