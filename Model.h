#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <glew.h>
#include <glm.hpp>
#include "ShaderManager.h"
#include "Texture.h"

//struct to store all three components of a vertex group, which is
//the grouping of verts, UVs and norms for each point in a triangle
struct Groups
{
	glm::vec3 vertex;
	glm::vec2 texture;
	glm::vec3 normal;
};

class Model
{

public:

	Model();

public:

	GLboolean& IsTextured();
	//made by me

public:

	void SetShininess(GLfloat shininess);
	
	void SetAmbient(GLfloat r, GLfloat g, GLfloat b);
	void SetDiffuse(GLfloat r, GLfloat g, GLfloat b);
	void SetSpecular(GLfloat r, GLfloat g, GLfloat b);

	void SetPosition(GLfloat x, GLfloat y, GLfloat z);
	glm::vec3 GetPosition() { return m_position; }

	void SetRotation(GLfloat x, GLfloat y, GLfloat z);
	void SetScale(GLfloat x, GLfloat y, GLfloat z);

public:

	bool LoadModel(const std::string& filename);
	bool LoadTexture(const std::string& filename, const std::string textureID);
	void UnloadTexture(const std::string textureID);
	
	void SetStrike(bool hit) { Hitted = hit; }
	void SetAngle(float angle) { m_angle = angle; }

public:

	void Create();
	void Update();
	void Draw();
	void Destroy();

private:
	float time;
	GLfloat m_shininess;
	GLboolean m_isTextured;

	GLuint m_VAO;
	GLuint m_EBO;
	GLuint m_vertexVBO;
	GLuint m_colorVBO;
	GLuint m_normalVBO;
	GLuint m_textureVBO;
	GLuint m_totalVertices;

	GLuint m_materialAmbientID;
	GLuint m_materialDiffuseID;
	GLuint m_materialSpecularID;
	GLuint m_materialShininessID;

	GLuint m_lightFlagID;
	GLuint m_textureFlagID;
	GLuint m_modelUniformID;
	GLuint m_normalUniformID;

	GLuint m_vertexAttributeID;
	GLuint m_colorAttributeID;
	GLuint m_normalAttributeID;
	GLuint m_textureAttributeID;

	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;

	glm::mat3 m_normal;
	glm::mat4 m_model = glm::mat4(1.0f);

	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
	glm::vec3 m_direction;

	glm::vec3 m_target;
	glm::mat4 Cam_rotX;
	glm::mat4 Cam_rotY;

	Texture m_texture;
	bool Hitted;
	float m_angle;
};

#endif