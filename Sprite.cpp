#include "Sprite.h"



Sprite::Sprite()
{
	m_textCells = glm::vec2(0.0f);
	m_textDimen = glm::vec2(1.0f);

	rotX = glm::mat4(1.0f);
	rotY = glm::mat4(1.0f);


	m_rotation = glm::vec3(0.0f,0.0f,0.8f);

}


Sprite::~Sprite()
{
}

void Sprite::SetDimension(GLuint width, GLuint height)
{
	scale = glm::vec3(width, height, 1.0f);
}

void Sprite::SetCell(GLint column, GLint row)
{
	m_textCells = glm::vec2(column, row);
}

void Sprite::SetDim(GLint totCol, GLint totRow)
{
	m_textDimen = glm::vec2(totCol, totRow);
}

void Sprite::GenBuffer()
{
	GLuint shaderProgramID = TheShader::Instance()->GetShaderProgram();
	vertexAttributeID = glGetAttribLocation(shaderProgramID, "vertexIn");
	colorAttributeID = glGetAttribLocation(shaderProgramID, "colorIn");

	m_textureAttribute = glGetAttribLocation(shaderProgramID, "textureIn");

	m_textureUnit1 = glGetUniformLocation(shaderProgramID, "textureImage_1");

	

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &vertexVBO);
	glGenBuffers(1, &colorVBO);
	glGenBuffers(1, &m_textureVBO);
	glGenBuffers(1, &EBO);

	m_texture.Load("Assets/2D/Transp_Axe.png", "Number_TEST");



}

void Sprite::FillBuffer()
{
	GLfloat vertices[] =
	{

		//back
		0.0f, 1.0f ,0.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,

	};
	GLfloat UVs[] =
	{
		0.0f,0.0f,
		1.0f,0.0f,
		1.0f,1.0f,
		0.0,1.0 };
	GLuint indices[] =
	{
		//front
		0,1,3,
		3,1,2,

	};
	GLfloat colors[] =
	{

		//back
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,


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
	glVertexAttribPointer(m_textureAttribute, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(m_textureAttribute);

	glBindVertexArray(0);

}

void Sprite::Render()
{
	model = glm::mat4(1.0f);
	model = glm::translate(model, position);

	model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 0.0f, -1.0f));
	glRotatef(45, 0, 0, 1);
	model = glm::scale(model, scale);

	//glm::vec2 celDimension = 1.0f / m_textDimen;
	////calculating the starting position of the new frame
	//glm::vec2 textOrigin = m_textCells * celDimension;
	
	
		//GLfloat UVs[] =
		//{
		//	textOrigin.x,                 textOrigin.y,
		//	textOrigin.x + celDimension.x,textOrigin.y,
		//	textOrigin.x + celDimension.x,textOrigin.y + celDimension.y,
		//	textOrigin.x,                 textOrigin.y + celDimension.y
		//};
		//glBindBuffer(GL_ARRAY_BUFFER, m_textureVBO);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(UVs), UVs, GL_STATIC_DRAW);
	/*}*/

		if (m_IAnimated == true)
		{
			time++;                  //that "0.05f" is the speed of the animation
			int texture_index = (int)(time * 0.05f) % (int)(m_textDimen.x * m_textDimen.y);
			m_textCells.x = (float)(texture_index % (int)m_textDimen.x);
			m_textCells.y = (float)(texture_index / (int)m_textDimen.x);
		}

		TheShader::Instance()->SendUniformData("model", model);
		TheShader::Instance()->SendUniformData("is_textured", true);
		TheShader::Instance()->SendUniformData("is_textured2", false);
		TheShader::Instance()->SendUniformData("isLit", false);
		TheShader::Instance()->SendUniformData("isDragon", false);
		TheShader::Instance()->SendUniformData("isDamaged", false);



	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture.GetID());
	glUniform1i(m_textureUnit1, 0);

	

	

	glBindVertexArray(VAO);
	
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);



	glBindVertexArray(0);

}

void Sprite::DestroyBuffer()
{
	glDeleteBuffers(1, &m_textureVBO);
	glDeleteBuffers(1, &vertexVBO);
	glDeleteBuffers(1, &colorVBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
}

void Sprite::Inputs()
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
	if (SDL_GetMouseState(NULL,NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		angle += 3.0f;
		if (angle >= 80.0f) 
		{
			angle = 0.0f;
		}
	}
	else 
	{
		angle = 0.0f;
	}
	/*if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT))
	{
		angle -= 1.0f;
	}*/

}

void Sprite::SetAmIAnim(bool animation)
{
	m_IAnimated = animation;
}

bool Sprite::GetAmIAnim()
{
	return m_IAnimated;
}


