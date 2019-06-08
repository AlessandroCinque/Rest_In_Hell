#include "SkyBox.h"



SkyBox::SkyBox()
{
}


SkyBox::~SkyBox()
{
}

void SkyBox::GenBuffer()
{
	GLuint shaderProgramID = TheShader::Instance()->GetShaderProgram();
	vertexAttributeID = glGetAttribLocation(shaderProgramID, "vertexIn");
	colorAttributeID = glGetAttribLocation(shaderProgramID, "colorIn");
	m_normalAttributeID = glGetAttribLocation(shaderProgramID, "normalIn");
	

	m_textureAttribute = glGetAttribLocation(shaderProgramID, "textureIn");
	m_textureUnit1 = glGetUniformLocation(shaderProgramID, "textureImage_1");


	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &vertexVBO);
	glGenBuffers(1, &colorVBO);
	glGenBuffers(1, &m_textureVBO);
	glGenBuffers(1, &m_normalVBO);

	glGenBuffers(1, &EBO);

	//========== trouble makers ==================
		//Link to the artist that made the texture
	//https://www.kisspng.com/png-space-skybox-texture-mapping-cube-mapping-night-sk-776480/download-png.html
	m_texture.Load("Assets/2D/Magma.jpg", "SKY_TEST");
}

void SkyBox::FillBuffer()
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
	GLfloat UVs[] =
	{
		//front
		0.25f,0.3f,
		0.50f,0.3f,
		0.50f,0.6f,
		0.25f,0.6f,

		//back
		0.75f,0.3f,
		1.00f,0.3f,
		1.00f,0.6f,
		0.75f,0.6f,

		//right
		0.50f,0.3f,
		1.00f,0.3f,
		1.00f,0.6f,
		0.50f,0.6f,

		//left
		0.00f,0.3f,
		0.25f,0.3f,
		0.25f,0.6f,
		0.00f,0.6f,

		//top
		0.25f,0.6f,
		0.50f,0.6f,
		0.50f,0.9f,
		0.25f,0.9f,

		//bottom
		0.25f,0.1f,
		0.50f,0.1f,
		0.50f,0.3f,
		0.25f,0.3f,

	};
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
	GLfloat normals[] = 
	{
		0.0f, 0.0f, -1.0f,	 0.0f, 0.0f, -1.0f, //front face
		0.0f, 0.0f,- 1.0f,	 0.0f, 0.0f, -1.0f,

		0.0f, 0.0f, 1.0f,	 0.0f, 0.0f, 1.0f, //back face
		0.0f, 0.0f, 1.0f,	 0.0f, 0.0f, 1.0f,

		-1.0f, 0.0f, 0.0f,	 -1.0f, 0.0f, 0.0f, //right face
		-1.0f, 0.0f, 0.0f,	 -1.0f, 0.0f, 0.0f,


		1.0f, 0.0f, 0.0f,	 1.0f, 0.0f, 0.0f, //left face
		1.0f, 0.0f, 0.0f,	 1.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f,	 0.0f, 1.0f, 0.0f, //bottom face
		0.0f, 1.0f, 0.0f,	 0.0f, 1.0f, 0.0f,


		0.0f, -1.0f, 0.0f,	 0.0f, -1.0f, 0.0f, //top face
		0.0f, -1.0f, 0.0f,	 0.0f, -1.0f, 0.0f
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

	glBindBuffer(GL_ARRAY_BUFFER, m_normalVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);
	glVertexAttribPointer(m_normalAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(m_normalAttributeID);

	glBindVertexArray(0);

	
}

void SkyBox::Render()
{
	model = glm::mat4(1.0f);
	model = glm::translate(model, position);

	model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 0.0f, -1.0f));
	model = glm::scale(model, scale);

//============= Sending Flags and other details to the shader,needed for every object ========================
	
	TheShader::Instance()->SendUniformData("model", model);

	TheShader::Instance()->SendUniformData("is_textured", true);
	TheShader::Instance()->SendUniformData("is_textured2", false);
	TheShader::Instance()->SendUniformData("isLit", true);
	TheShader::Instance()->SendUniformData("isDragon", false);
	TheShader::Instance()->SendUniformData("isDamaged", false);

	TheShader::Instance()->SendUniformData("Material.shininess", m_shininess);
	TheShader::Instance()->SendUniformData("Material.ambient", m_ambient);
	TheShader::Instance()->SendUniformData("Material.diffuse", m_diffuse);
	TheShader::Instance()->SendUniformData("Material.specular", m_specular);

	glUniform1i(m_textureUnit1, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture.GetID());

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


}

void SkyBox::DestroyBuffer()
{
	glDeleteBuffers(1, &m_textureVBO);
	glDeleteBuffers(1, &vertexVBO);
	glDeleteBuffers(1, &colorVBO);
	glDeleteBuffers(1, &m_normalVBO);

	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
}


