#pragma once
#include <iostream>
#include <math.h>


#include <SDL.h>
#include <glew.h>
#include <glm.hpp>
#include<gtc/matrix_transform.hpp>

#include "ShaderManager.h"
#include "InputManager.h"

class Grid
{
public:
	Grid();
	~Grid();
	void Create();
	void Draw();
	void Destroy();

private:
	//========== set size ===============================================
	const int SIZE = 10; // 40 lines in total
	const int QUADRANTS = 4;
	const int BYTES_PER_LINE = 2 * 3 * sizeof(GLfloat);
	const int BYTES_PER_VERTEX = 3 * sizeof(GLfloat);
	//===========================================================
	GLuint texture_flag;
	GLuint texture_flag1;
	GLuint isLit_flag;

	GLfloat m_shininess = 1.0f;
	glm::vec3 m_ambient = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 m_diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 m_specular = glm::vec3(1.0f, 1.0f, 1.0f);

	GLuint vertexAttributeID = 0;
	GLuint colorAttributeID = 0;
	GLuint modelUniformID = 0; //= glGetUniformLocation(TheShader::Instance()->GetShaderProgram(), "model");
	GLuint vertexVBO = 0;
	GLuint colorVBO = 0;
	GLuint VAO = 0;
	glm::mat4 model = glm::mat4(1.0f);

};

