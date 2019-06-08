#include "Cube.h"



Cube::Cube()
{
}


Cube::~Cube()
{
}

void Cube::GenBuffer()
{
	GLuint shaderProgramID = TheShader::Instance()->GetShaderProgram();
	vertexAttributeID = glGetAttribLocation(shaderProgramID, "vertexIn");
	colorAttributeID = glGetAttribLocation(shaderProgramID, "colorIn");
	modelUniformID = glGetUniformLocation(TheShader::Instance()->GetShaderProgram(), "model");
	//============= ALWAYS PUT IT IN THE NEW OBJECTS ========================
	//is not a bool but a flag!!!
	texture_flag = glGetUniformLocation(TheShader::Instance()->GetShaderProgram(), "is_textured");


	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VAO);
	glGenBuffers(1, &vertexVBO);
	glGenBuffers(1, &colorVBO);
	glGenBuffers(1, &m_textureVBO);
	glGenBuffers(1, &EBO);
}

void Cube::FillBuffer()
{
	GLfloat vertices[] =
	{
		//front
		-0.5f , 0.5f , 1.0f,
		0.5f, 0.5f, 1.0f,
		0.5f, -0.5f, 1.0f,
		-0.5f, -0.5f, 1.0f,
		//back
		-0.5f , 0.5f , -1.0f,
		0.5f, 0.5f, -1.0f,
		0.5f, -0.5f, -1.0f,
		-0.5f, -0.5f, -1.0f,
		//right
		0.5f, 0.5f, 1.0f,
		0.5f, 0.5f, -1.0f,
		0.5f, -0.5f, -1.0f,
		0.5f, -0.5f, 1.0f,
		//left
		-0.5f, 0.5f, 1.0f,
		-0.5f, 0.5f, -1.0f,
		-0.5f, -0.5f, -1.0f,
		-0.5f, -0.5f, 1.0f,
		//bottom
		-0.5f , -0.5f , 1.0f,
		-0.5f, -0.5f, -1.0f,
		0.5f, -0.5f, -1.0f,
		0.5f, -0.5f, 1.0f,
		//top
		-0.5f , 0.5f , 1.0f,
		-0.5f, 0.5f, -1.0f,
		0.5f, 0.5f, -1.0f,
		0.5f, 0.5f, 1.0f,

	};
	GLfloat UVs[] = { 0.0f,0.0f,
					1.0f,0.0f,
					1.0f,1.0f,
					0.0,1.0 };
	GLuint indices[] =
	{
		//front
		0,1,3,
		3,1,2,
		//back
		4,5,7,
		7,5,6,
		//right
		8,9,11,
		11,9,10,
		//right
		12,13,15,
		15,13,14,
		//bottom
		16,17,19,
		19,17,18,
		//top
		20,21,23,
		23,21,22,
	};
	GLfloat colors[] =
	{
		//front
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		//back
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		//right
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		//left
		0.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f,
		//bottom
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		//top
		1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,

	};

	glBindVertexArray(VAO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(vertexAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vertexAttributeID);

	glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glVertexAttribPointer(colorAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(colorAttributeID);

	glBindBuffer(GL_ARRAY_BUFFER, m_textureVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(UVs), UVs, GL_STATIC_DRAW);
	glVertexAttribPointer(m_textureAttributeID, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(m_textureAttributeID);

	glBindVertexArray(0);
}

void Cube::Render()
{
	model = glm::mat4(1.0f);
	model = glm::translate(model, position);

	//angle = 35.5f;
	model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 0.0f, -1.0f));
	//scale = glm::vec3(2.0f, 0.4f, 1.0f);
	model = glm::scale(model, scale);

	glUniformMatrix4fv(modelUniformID, 1, GL_FALSE, &model[0][0]);

	glBindTexture(GL_TEXTURE_2D, texture.GetID());
	
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	//m_textureAttributeID.Load("Textures/Crate_1.png", "CRATE_TEST");
	
}

void Cube::DestroyBuffer()
{
	glDeleteBuffers(1, &vertexVBO);
	glDeleteBuffers(1, &colorVBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
}

void Cube::Inputs()
{
	if(TheInputManager::Instance()->GetKey() == SDLK_i && TheInputManager::Instance()->isKeyPressed())
	{
	position.y += 0.01;
	}
	if (TheInputManager::Instance()->GetKey() == SDLK_j && TheInputManager::Instance()->isKeyPressed())
	{
		position.x -= 0.01;
	}
	if (TheInputManager::Instance()->GetKey() == SDLK_k && TheInputManager::Instance()->isKeyPressed())
	{
		position.y -= 0.01;
	}
	if (TheInputManager::Instance()->GetKey() == SDLK_l && TheInputManager::Instance()->isKeyPressed())
	{
		position.x += 0.01;
	}
}

