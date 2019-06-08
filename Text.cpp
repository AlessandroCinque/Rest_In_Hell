#include "Text.h"



Text::Text()
{
	m_textCells = glm::vec2(0.0f);
	m_textDimen = glm::vec2(1.0f);
}


Text::~Text()
{
}


void Text::SetDimension(GLuint width, GLuint height)
{
	scale = glm::vec3(width, height, 1.0f);
}

void Text::SetCell(GLint column, GLint row)
{
	m_textCells = glm::vec2(column, row);
}

void Text::SetDim(GLint totCol, GLint totRow)
{
	m_textDimen = glm::vec2(totCol, totRow);
}

void Text::SetWord(std::string text)
{
	m_text = text;
}

void Text::GenBuffer()
{
	GLuint shaderProgramID = TheShader::Instance()->GetShaderProgram();
	vertexAttributeID = glGetAttribLocation(shaderProgramID, "vertexIn");
	colorAttributeID = glGetAttribLocation(shaderProgramID, "colorIn");
	modelUniformID = glGetUniformLocation(TheShader::Instance()->GetShaderProgram(), "model");
	m_textureAttribute = glGetAttribLocation(shaderProgramID, "textureIn");

	m_textureUnit1 = glGetUniformLocation(shaderProgramID, "textureImage_1");
	//m_textureUnit2 = glGetUniformLocation(shaderProgramID, "textureImage_2");

	//============= ALWAYS PUT IT IN THE NEW OBJECTS ========================
	texture_flag = glGetUniformLocation(TheShader::Instance()->GetShaderProgram(), "is_textured");
	texture_flag1 = glGetUniformLocation(TheShader::Instance()->GetShaderProgram(), "is_textured2");

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &vertexVBO);
	glGenBuffers(1, &colorVBO);
	glGenBuffers(1, &m_textureVBO);
	glGenBuffers(1, &EBO);

	m_texture.Load("Assets/2D/Calibri.png", "Word_TEST");


	//m_texture1.Load("Water.png", "WATER_TEST");

}

void Text::FillBuffer()
{

	glBindVertexArray(VAO);



	for (int i = 0; i < m_text.size(); i++)
	{

		GLuint vertices[] =
		{

			//back
			0 + i, 1 ,0,
			1.0f, 1.0f, 1.0f,
			1.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,

		};
		glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
		glBufferSubData(GL_ARRAY_BUFFER, offsetVert, sizeof(vertices), vertices);

		glVertexAttribPointer(vertexAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(vertexAttributeID);

		offsetVert += sizeof(vertices);
	}

	for (int i = 0; i < m_text.size(); i++)
	{
		GLfloat colors[] =
		{

			//back
			1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,


		};
		glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
		glBufferSubData(GL_ARRAY_BUFFER, offsetColor, sizeof(colors), colors);

		glVertexAttribPointer(colorAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(colorAttributeID);

		offsetColor += sizeof(colors);

	}

	for (int i = 0; i < m_text.size(); i++)
	{
		int textureIndex = m_text[i]; //getting the ascii value
		m_textCells.s = textureIndex % 16;
		m_textCells.t = textureIndex / 16;

		glm::vec2 celDimension(1.0f / 16.0f, 1.0f / 16.0f);
		glm::vec2 textOrigin = m_textCells * celDimension;

		GLfloat UVs[] =
		{
			textOrigin.x,                 textOrigin.y,
			textOrigin.x + celDimension.x,textOrigin.y,
			textOrigin.x + celDimension.x,textOrigin.y + celDimension.y,
			textOrigin.x,                 textOrigin.y + celDimension.y
		};
		glBindBuffer(GL_ARRAY_BUFFER, m_textureVBO);
		glBufferSubData(GL_ARRAY_BUFFER, offsetText, sizeof(UVs), UVs);

		glVertexAttribPointer(m_textureAttribute, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(m_textureAttribute);

		offsetText += sizeof(UVs);
	}


	for (int i = 0; i < m_text.size(); i++) 
	{
		//GLuint vertices[] =
		//{

		//	//back
		//	0+ i, 1 ,0,
		//	1.0f, 1.0f, 1.0f,
		//	1.0f, 0.0f, 1.0f,
		//	0.0f, 0.0f, 1.0f,

		//};
		//glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
		//glBufferSubData(GL_ARRAY_BUFFER, offsetVert, sizeof(vertices), vertices);

		//glVertexAttribPointer(vertexAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);
		//glEnableVertexAttribArray(vertexAttributeID);

		//offsetVert += sizeof(vertices);

		//GLfloat colors[] =
		//{

		//	//back
		//	1.0f, 0.0f, 0.0f,
		//	1.0f, 0.0f, 0.0f,
		//	1.0f, 0.0f, 0.0f,
		//	1.0f, 0.0f, 0.0f,


		//};
		//glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
		//glBufferSubData(GL_ARRAY_BUFFER, offsetColor, sizeof(colors), colors);

		//glVertexAttribPointer(colorAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);
		//glEnableVertexAttribArray(colorAttributeID);

		//offsetColor += sizeof(colors);

		//int textureIndex = m_text[i]; //getting the ascii value
		//m_textCells.s = textureIndex % 16;
		//m_textCells.t = textureIndex / 16;

		//glm::vec2 celDimension(1.0f / 16.0f, 1.0f / 16.0f);
		//glm::vec2 textOrigin = m_textCells * celDimension;

		//GLfloat UVs[] =
		//{
		//	textOrigin.x,                 textOrigin.y,
		//	textOrigin.x + celDimension.x,textOrigin.y,
		//	textOrigin.x + celDimension.x,textOrigin.y + celDimension.y,
		//	textOrigin.x,                 textOrigin.y + celDimension.y
		//};
		//glBindBuffer(GL_ARRAY_BUFFER, m_textureVBO);
		//glBufferSubData(GL_ARRAY_BUFFER, offsetText, sizeof(UVs), UVs);

		//glVertexAttribPointer(m_textureAttribute, 2, GL_FLOAT, GL_FALSE, 0, 0);
		//glEnableVertexAttribArray(m_textureAttribute);

		GLuint indices[] =
		{
			//front
			0 + 4 * i,
			1 + 4 * i,
			3 + 4 * i,

			3 + 4 * i,
			1 + 4 * i,
			2 + 4 * i,

		};
		glBindBuffer(GL_ARRAY_BUFFER, EBO);
		glBufferSubData(GL_ARRAY_BUFFER, offsetIndex, sizeof(indices),indices);

		offsetIndex += sizeof(indices);
	}

	glBindVertexArray(0);
	



	glBindVertexArray(VAO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 10000, nullptr, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	glBufferData(GL_ARRAY_BUFFER, 10000, nullptr, GL_STATIC_DRAW);
	glVertexAttribPointer(vertexAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vertexAttributeID);

	glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
	glBufferData(GL_ARRAY_BUFFER, 10000, nullptr, GL_STATIC_DRAW);
	glVertexAttribPointer(colorAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(colorAttributeID);

	glBindBuffer(GL_ARRAY_BUFFER, m_textureVBO);
	glBufferData(GL_ARRAY_BUFFER, 10000, nullptr, GL_STATIC_DRAW);
	glVertexAttribPointer(m_textureAttribute, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(m_textureAttribute);

	glBindVertexArray(0);

}

void Text::Render()
{
	model = glm::mat4(1.0f);
	model = glm::translate(model, position);

	//model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 0.0f, -1.0f));
	model = glm::scale(model, scale);


	glm::vec2 celDimension = 1.0f / m_textDimen;
	//calculating the starting position of the new frame
	
	/*}*/



	glUniformMatrix4fv(modelUniformID, 1, GL_FALSE, &model[0][0]);
	//============= ALWAYS PUT IT IN THE NEW OBJECTS ========================
	glUniform1i(texture_flag, true);
	glUniform1i(texture_flag1, false);



	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture.GetID());
	glUniform1i(m_textureUnit1, 0);





	glBindVertexArray(VAO);

	glDrawElements(GL_TRIANGLES,10000 /*6* m_text.length()*/, GL_UNSIGNED_INT, 0);



	glBindVertexArray(0);

}

void Text::DestroyBuffer()
{
	glDeleteBuffers(1, &m_textureVBO);
	glDeleteBuffers(1, &vertexVBO);
	glDeleteBuffers(1, &colorVBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
}

void Text::Inputs()
{
	if (TheInputManager::Instance()->GetKey() == SDLK_i && TheInputManager::Instance()->isKeyPressed())
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
	//there is a misterious reason why there is only an & and not two
	/*if (SDL_GetMouseState(NULL,NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
	scale += 0.1f;
	}
	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT))
	{
	scale -= 0.1f;
	}*/
	if (TheInputManager::Instance()->IsScrollUP())
	{
		scale += 0.1f;
	}
	if (TheInputManager::Instance()->IsScrollDOWN())
	{
		scale -= 0.1f;
	}
}


