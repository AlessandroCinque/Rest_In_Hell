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
class Text
{
public:
	Text();
	~Text();
	void SetDimension(GLuint width, GLuint height);
	void SetCell(GLint column, GLint row);
	void SetDim(GLint totCol, GLint totRow);
	void SetWord(std::string text);
	void GenBuffer();
	void FillBuffer();
	void Render();
	void DestroyBuffer();
	void Inputs();

private:
	Texture m_texture;
	Texture m_texture1;

	GLuint m_textureUnit1;
	GLuint m_textureUnit2;

	GLuint texture_flag;
	GLuint texture_flag1;

	glm::vec3 m_dimension;

	GLuint vertexAttributeID;
	GLuint colorAttributeID;
	GLuint m_textureAttribute;

	GLuint modelUniformID; //= glGetUniformLocation(TheShader::Instance()->GetShaderProgram(), "model");

	//===============
	glm::vec2 m_textCoord;
	glm::vec2 m_textCells;
	glm::vec2 m_textDimen;

	std::string m_text;

	//===============
	GLuint offsetVert = 0;
	GLuint offsetColor = 0;
	GLuint offsetText = 0;
	GLuint offsetIndex = 0;
	int textureIndex ;

	GLuint vertexVBO = 0;
	GLuint colorVBO = 0;
	GLuint m_textureVBO;
	GLuint EBO = 0;
	GLuint VAO = 0;

	glm::mat4 model = glm::mat4(1.0f);
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 scale;

	float angle = 0.0f;

};