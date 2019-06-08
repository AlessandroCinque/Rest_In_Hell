#include "Quad.h"



Quad::Quad()
{
}


Quad::~Quad()
{
}

void Quad::GenBuffer()
{
	GLuint shaderProgramID = TheShader::Instance()->GetShaderProgram();
	vertexAttributeID = glGetAttribLocation(shaderProgramID, "vertexIn");
	colorAttributeID = glGetAttribLocation(shaderProgramID, "colorIn");
	m_textureAttribute = glGetAttribLocation(shaderProgramID, "textureIn");

	m_textureUnit1 = glGetUniformLocation(shaderProgramID, "textureImage_1");
	m_textureUnit2 = glGetUniformLocation(shaderProgramID, "textureImage_2");
	
	

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &vertexVBO);
	glGenBuffers(1, &colorVBO);
	glGenBuffers(1, &m_textureVBO);
	glGenBuffers(1, &EBO);

	//Link to the artist that made the texture
	//https://it.depositphotos.com/215959514/stock-photo-river-magma-lava-background-texture.html
	m_texture.Load("Assets/2D/Magma2.jpg", "MAGMA");
	//Link to the artist that made the texture
	//https://www.vecteezy.com/vector-art/116067-vector-stone-texture-vector-background
	m_texture1.Load("Assets/2D/Rock.jpg", "ROCK");
	
}

void Quad::FillBuffer()
{
	GLfloat vertices[] =
	{
	
		//back
		-0.5f , 0.5f , -1.0f,
		0.5f, 0.5f, -1.0f,
		0.5f, -0.5f, -1.0f,
		-0.5f, -0.5f, -1.0f,

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
		//The third parameter is a POINTER, although you can put the ARRAY'S NAME cause the name of an array IS A POINTER TO ITS FIRST VALUE!!!!!
		glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(vertexAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(vertexAttributeID);
		//The third parameter is a POINTER, although you can put the ARRAY'S NAME cause the name of an array IS A POINTER TO ITS FIRST VALUE!!!!!
		glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
		glVertexAttribPointer(colorAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(colorAttributeID);
		//The third parameter is a POINTER, although you can put the ARRAY'S NAME cause the name of an array IS A POINTER TO ITS FIRST VALUE!!!!!
		glBindBuffer(GL_ARRAY_BUFFER, m_textureVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(UVs), UVs, GL_STATIC_DRAW);
		glVertexAttribPointer(m_textureAttribute, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(m_textureAttribute);

	glBindVertexArray(0);
	
}

void Quad::Render()
{
	model = glm::mat4(1.0f);
	model = glm::translate(model, position);

	model = glm::rotate(model, glm::radians(angle), glm::vec3(90.0f, 0.0f, 0.0f));
	model = glm::scale(model, scale);
//============= Sending Flags and other details to the shader,needed for every object ========================
	TheShader::Instance()->SendUniformData("model", model);
	
	TheShader::Instance()->SendUniformData("is_textured", true);
	TheShader::Instance()->SendUniformData("is_textured2", true);
	TheShader::Instance()->SendUniformData("isLit", true);
	TheShader::Instance()->SendUniformData("isDragon", false);
	TheShader::Instance()->SendUniformData("isDamaged", false);

	TheShader::Instance()->SendUniformData("Material.shininess", m_shininess);
	TheShader::Instance()->SendUniformData("Material.ambient", m_ambient);
	TheShader::Instance()->SendUniformData("Material.diffuse", m_diffuse);
	TheShader::Instance()->SendUniformData("Material.specular", m_specular);


	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture.GetID());
	glUniform1i(m_textureUnit1, 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_texture1.GetID());
	glUniform1i(m_textureUnit2, 1);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);



	glBindVertexArray(0);

}

void Quad::DestroyBuffer()
{
	glDeleteBuffers(1, &m_textureVBO);
	glDeleteBuffers(1, &vertexVBO);
	glDeleteBuffers(1, &colorVBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
}
