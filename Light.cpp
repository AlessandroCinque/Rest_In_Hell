#include "Light.h"



Light::Light()
{
}


Light::~Light()
{
}

void Light::Create()
{
	//===================================================================
	GLuint shaderProgramID = TheShader::Instance()->GetShaderProgram();
	vertexAttributeID = glGetAttribLocation(shaderProgramID, "vertexIn");
	colorAttributeID = glGetAttribLocation(shaderProgramID, "colorIn");
	
	LightUniformID = glGetUniformLocation(TheShader::Instance()->GetShaderProgram(), "lightColor");

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &vertexVBO);
	glGenBuffers(1, &colorVBO);

	

}


void Light::Draw()
{
	glBindVertexArray(VAO);


	GLfloat vertices[] = { m_position.x,m_position.y,m_position.z };
	GLfloat colors[] = { 0.0f,0.0f,0.0f,1.0 };



	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	//The third parameter is a POINTER, although you can put the ARRAY'S NAME cause the name of an array IS A POINTER TO ITS FIRST VALUE!!!!!
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(vertexAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vertexAttributeID);

	//The third parameter is a POINTER, although you can put the ARRAY'S NAME cause the name of an array IS A POINTER TO ITS FIRST VALUE!!!!!
	glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glVertexAttribPointer(colorAttributeID, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(colorAttributeID);

	glBindVertexArray(0);

	TheShader::Instance()->SendUniformData("model", model);
	TheShader::Instance()->SendUniformData("is_textured", false);
	TheShader::Instance()->SendUniformData("is_textured2", false);
	TheShader::Instance()->SendUniformData("isLit", false);
	TheShader::Instance()->SendUniformData("isDragon", false);
	TheShader::Instance()->SendUniformData("isDamaged", false);

	TheShader::Instance()->SendUniformData("Light.position", m_position);
	TheShader::Instance()->SendUniformData("Light.ambient", m_ambient);
	TheShader::Instance()->SendUniformData("Light.diffuse", m_diffuse);
	TheShader::Instance()->SendUniformData("Light.specular", m_specular);

	glUniform3fv(LightUniformID,1, &m_lightColor.x);
	//---------------------------
	glPointSize(20.0f);
	glBindVertexArray(VAO);
	glDrawArrays(GL_POINTS, 0, 1);
	glBindVertexArray(0);

}

void Light::Destroy()
{
	glDeleteBuffers(1, &vertexVBO);
	glDeleteBuffers(1, &colorVBO);
	glDeleteVertexArrays(1, &VAO);
}

void Light::SetColor(GLfloat r, GLfloat g, GLfloat b)
{
	m_color = glm::vec3(r, g, b);
}

void Light::Inputs()
{
	//m_direction = glm::vec3(0.0f, 0.0f, 0.0f);

	if (TheInputManager::Instance()->GetKey() == SDLK_i && TheInputManager::Instance()->isKeyPressed())
	{
		//y += 0.01;
		//CamPos.y += 0.01;
		m_position += glm::vec3(0.0f, 0.0f, -0.5f);

	}
	if (TheInputManager::Instance()->GetKey() == SDLK_j && TheInputManager::Instance()->isKeyPressed())
	{
		//CamPos.x -= 0.01;
		m_position += glm::vec3(-0.5f, 0.0f, 0.0f);

	}
	if (TheInputManager::Instance()->GetKey() == SDLK_k && TheInputManager::Instance()->isKeyPressed())
	{
		//CamPos.y -= 0.01;
		m_position += glm::vec3(0.0f, 0.0f, 0.5f);
	}
	if (TheInputManager::Instance()->GetKey() == SDLK_l && TheInputManager::Instance()->isKeyPressed())
	{
		//CamPos.x += 0.01;
		m_position += glm::vec3(0.5f, 0.0f, 0.0f);
	}
	if (TheInputManager::Instance()->GetKey() == SDLK_u && TheInputManager::Instance()->isKeyPressed())
	{
		//CamPos.z -= 0.5;
		m_position.y -= 0.5;
	}
	if (TheInputManager::Instance()->GetKey() == SDLK_o && TheInputManager::Instance()->isKeyPressed())
	{
		//CamPos.z += 0.5;
		m_position.y += 0.5;
	}


}
