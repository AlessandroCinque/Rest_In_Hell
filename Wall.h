#pragma once
#include <iostream>
#include<string>
#include <math.h>
#include<vector>

#include <SDL.h>
#include <glew.h>
#include <glm.hpp>
#include<gtc/matrix_transform.hpp>

#include "ShaderManager.h"
#include "InputManager.h"
#include "Texture.h"
class Wall
{
public:
	Wall();
	~Wall();
public:

	void GenBuffer();
	void FillBuffer();
	void Render(glm::vec3 W_position, float W_angle);
	void DestroyBuffer();
	void SetPosition(glm::vec3 W_position) { position = W_position; };
	glm::vec3 GetPosition() { return position; };
	glm::vec3 GetScale() { return scale; };
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

	GLuint modelUniformID; //= glGetUniformLocation(TheShader::Instance()->GetShaderProgram(), "model");

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
	glm::vec3 position = glm::vec3(-5.0f, 2.0f, 0.0f);
	glm::vec3 scale = glm::vec3(20.0f, 5.0f, 1.0f);

	float angle = 90.0f;
};

static std::vector<Wall*> master_wall;