
#ifndef ShaderMANAGER_H
#define ShaderMANAGER_H
#include <iostream>
#include <fstream>
#include<string>
#include <SDL.h>
#include <glew.h>
#include<gtc/matrix_transform.hpp>
#include <math.h>
#include "Singleton.h"
class ShaderManager
{
public:



		friend class Singleton<ShaderManager>;

	public:

		bool CreateProgram();
		bool CreateShader();

		void SendUniformData(std::string flag,bool true_false);
		void SendUniformData(std::string ID,glm::mat4 modelMatrix);
		void SendUniformData(std::string ID, glm::vec3 vector3);
		void SendUniformData(std::string ID, float valueF);

		bool CompileShader();
		void AttachShader();
		bool LinkProgram();

		void DetachShader();
		void DestroyShader();
		void DestroyProgram();

		GLuint GetShaderProgram();

	private:

		GLuint m_shaderProgramID;
		GLuint m_vertexShaderID;
		GLuint m_fragmentShaderID;
		
		

		ShaderManager() {}
		ShaderManager(const ShaderManager&);
		ShaderManager& operator=(const ShaderManager&);

};
	typedef Singleton<ShaderManager> TheShader;
#endif