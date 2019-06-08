#include "Grid.h"



Grid::Grid()
{
}


Grid::~Grid()
{
}

void Grid::Create()
{
	GLuint offset = 0;
	
	//===================================================================
	GLuint shaderProgramID = TheShader::Instance()->GetShaderProgram();
	vertexAttributeID = glGetAttribLocation(shaderProgramID, "vertexIn");
	colorAttributeID = glGetAttribLocation(shaderProgramID, "colorIn");


	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &vertexVBO);
	glGenBuffers(1, &colorVBO);
//==========================================
	glBindVertexArray(VAO);

	
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, SIZE * QUADRANTS*BYTES_PER_LINE, nullptr, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	glBufferData(GL_ARRAY_BUFFER, (1 + SIZE) * QUADRANTS*BYTES_PER_LINE, nullptr , GL_STATIC_DRAW);
	glVertexAttribPointer(vertexAttributeID, 3, GL_INT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vertexAttributeID);

	glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
	glBufferData(GL_ARRAY_BUFFER,(1+SIZE) * QUADRANTS*BYTES_PER_LINE, nullptr, GL_STATIC_DRAW);
	glVertexAttribPointer(colorAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(colorAttributeID);

	glBindVertexArray(0);
	//create all negative x
	for (int i = 0; i < 1 + SIZE * 2; i++)
	{
		GLint vertices[] = { -SIZE + i,0,-SIZE, 
							-SIZE + i, 0, SIZE };
		GLfloat colors[] = { 1.0f,1.0f,1.0f,
							 1.0f,1.0f,1.0f };
		glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
		//The third parameter is a POINTER, although you can put the ARRAY'S NAME cause the name of an array IS A POINTER TO ITS FIRST VALUE!!!!!
		glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(vertices), vertices);

		glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
		//The third parameter is a POINTER, although you can put the ARRAY'S NAME cause the name of an array IS A POINTER TO ITS FIRST VALUE!!!!!
		glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(colors), colors);
		offset += BYTES_PER_LINE;
	}
	for (int i = 0; i < 1 + SIZE * 2; i++)
	{
		GLint vertices[] = { -SIZE,0,-SIZE + i,
							SIZE, 0, -SIZE + i };
		GLfloat colors[] = { 1.0f,0.0f,0.0f,
							1.0f,0.0f,0.0f };
		glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
		//The third parameter is a POINTER, although you can put the ARRAY'S NAME cause the name of an array IS A POINTER TO ITS FIRST VALUE!!!!!
		glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(vertices), vertices);

		glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
		//The third parameter is a POINTER, although you can put the ARRAY'S NAME cause the name of an array IS A POINTER TO ITS FIRST VALUE!!!!!
		glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(colors), colors);
		offset += BYTES_PER_LINE;
	}
	GLint vertices[] = { 0,20,0,
					0,-20,0 };
	GLfloat colors[] = { 0.0f,1.0f,0.0f,
		0.0f,1.0f,0.0f };
	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	//The third parameter is a POINTER, although you can put the ARRAY'S NAME cause the name of an array IS A POINTER TO ITS FIRST VALUE!!!!!
	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(vertices), vertices);

	glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
	//The third parameter is a POINTER, although you can put the ARRAY'S NAME cause the name of an array IS A POINTER TO ITS FIRST VALUE!!!!!
	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(colors), colors);
	offset += BYTES_PER_LINE;
}

void Grid::Draw()
{
	TheShader::Instance()->SendUniformData("model", model);
	//TheShader::Instance()->SendUniformData("LightColor", false);

	TheShader::Instance()->SendUniformData("is_textured", false);
	TheShader::Instance()->SendUniformData("is_textured2", false);
	TheShader::Instance()->SendUniformData("isLit", true);
	TheShader::Instance()->SendUniformData("isDragon", false);
	TheShader::Instance()->SendUniformData("isDamaged", false);

	TheShader::Instance()->SendUniformData("Material.shininess", m_shininess);
	TheShader::Instance()->SendUniformData("Material.ambient", m_ambient);
	TheShader::Instance()->SendUniformData("Material.diffuse", m_diffuse);
	TheShader::Instance()->SendUniformData("Material.specular", m_specular);
	// imcrease just the width
	glLineWidth(4.0f);
	//---------------------------
	glBindVertexArray(VAO);
	glDrawArrays(GL_LINES, 0,SIZE * 8 + 6 );
	glBindVertexArray(0);
}

void Grid::Destroy()
{
	glDeleteBuffers(1, &vertexVBO);
	glDeleteBuffers(1, &colorVBO);
	glDeleteVertexArrays(1, &VAO);
}
