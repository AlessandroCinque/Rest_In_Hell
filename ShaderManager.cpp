#include "ShaderManager.h"


bool ShaderManager::CreateProgram()
{
	m_shaderProgramID = glCreateProgram();

	if (m_shaderProgramID == 0) 
	{
		std::cout << "Error creating shader program!" << std::endl;
		return false;
	}
	return true;
	
}


bool ShaderManager::CreateShader()
{
	m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (m_vertexShaderID == 0) 
	{
		std::cout<<"Error creating Fragment Shader!" <<std::endl;
		return false;
	}

	m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (m_fragmentShaderID == 0)
	{
		std::cout << "Error creating Fragment Shader!" << std::endl;
		return false;
	}
	return true;
}

void ShaderManager::SendUniformData(std::string flag, bool true_false)
{
	GLuint dataFlag = glGetUniformLocation(TheShader::Instance()->GetShaderProgram(), flag.c_str());
	glUniform1i(dataFlag, true_false);
	
}

void ShaderManager::SendUniformData(std::string ID, glm::mat4 modelMatrix)
{
	GLuint dataFlag = glGetUniformLocation(TheShader::Instance()->GetShaderProgram(), ID.c_str());
	glUniformMatrix4fv(dataFlag,1,GL_FALSE, &(modelMatrix)[0][0]);
}

void ShaderManager::SendUniformData(std::string ID, glm::vec3 vector3)
{
	GLuint dataFlag = glGetUniformLocation(TheShader::Instance()->GetShaderProgram(), ID.c_str());
	glUniform3fv(dataFlag, 1, &vector3.x);
}

void ShaderManager::SendUniformData(std::string ID, float valueF)
{
	GLuint dataFlag = glGetUniformLocation(TheShader::Instance()->GetShaderProgram(), ID.c_str());
	glUniform1f(dataFlag, valueF);
}


bool ShaderManager::CompileShader()
{
	std::fstream file; //file pointer or handler
	std::string lineText; //where each line of text is read into
	std::string finalString; //the compete source code in one string!
	GLint compileStatus;
	//=============Here alll file handling

	file.open("Main.vert");
	if (!file) 
	{
		std::cout << "File could not be opened" << std::endl;
	}
	while (!file.eof()) 
	{
		std::getline(file, lineText);
		finalString += lineText + '\n';
	}
	file.close();
	//---------------------------------------------
	const GLchar* sourceCode = (const GLchar*)finalString.c_str();

	//binding the source code shader

	glShaderSource(m_vertexShaderID, 1, &sourceCode, NULL);

	//compile the source code
	glCompileShader(m_vertexShaderID);

	//get error code for compilation
	glGetShaderiv(m_vertexShaderID, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus == GL_TRUE)
	{
		std::cout<<"Vertex shader compiled sucessfully!"<<std::endl;
	}
	else
	{
		GLchar errorText[1000];
		GLsizei lenght;
		std::cout << "There were vertex shader errors:" << std::endl;
		glGetShaderInfoLog(m_vertexShaderID, 1000, &lenght, errorText);
		std::cout<<errorText<< std::endl;
		return false;
	}
	lineText.clear();
	finalString.clear();
//====================== FRAGMENT SHADER!!! =========
	file.open("Main.frag");
	if (!file)
	{
		std::cout << "File could not be opened" << std::endl;
	}
	while (!file.eof())
	{
		std::getline(file, lineText);
		finalString += lineText + '\n';
	}
	file.close();
	sourceCode = (const GLchar*)finalString.c_str();

	glShaderSource(m_fragmentShaderID, 1, &sourceCode, NULL);

	//compile the source code
	glCompileShader(m_fragmentShaderID);

	//get error code for compilation
	glGetShaderiv(m_fragmentShaderID, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus == GL_TRUE)
	{
		std::cout << "Fragment shader compiled sucessfully!" << std::endl;
	}
	else
	{
		GLchar errorText[1000];
		GLsizei lenght;
		std::cout << "There were fragment shader errors:" << std::endl;
		glGetShaderInfoLog(m_fragmentShaderID, 1000, &lenght, errorText);
		std::cout << errorText << std::endl;
		return false;
	}
	return true;
}

void ShaderManager::AttachShader()
{
	glAttachShader(m_shaderProgramID, m_vertexShaderID);
	glAttachShader(m_shaderProgramID, m_fragmentShaderID);


}


bool ShaderManager::LinkProgram()
{
	GLint linkStatus = 0;
	glLinkProgram(m_shaderProgramID);
	glUseProgram(m_shaderProgramID);
	glGetProgramiv(m_shaderProgramID, GL_LINK_STATUS, &linkStatus);

	if (linkStatus == GL_FALSE)
	{
		GLchar errorText[1000];
		GLsizei lenght;
		std::cout << "There were linker errors" << std::endl;
		glGetProgramInfoLog(m_shaderProgramID, 1000, &lenght, errorText);
		std::cout << errorText << std::endl;
	return false;
	}
	return true;
}

void ShaderManager::DetachShader()
{
	glDetachShader(m_shaderProgramID, m_vertexShaderID);
	glDetachShader(m_shaderProgramID, m_fragmentShaderID);
}

void ShaderManager::DestroyShader()
{
	glDeleteShader(m_fragmentShaderID);
	glDeleteShader(m_vertexShaderID);
}

void ShaderManager::DestroyProgram()
{
	glDeleteProgram(m_shaderProgramID);
}

GLuint ShaderManager::GetShaderProgram()
{
	return m_shaderProgramID;
}
