#pragma once
#include <iostream>
#include <math.h>


#include <SDL.h>
#include <glew.h>
#include <glm.hpp>
#include<gtc/matrix_transform.hpp>

#include"ShaderManager.h"
#include "InputManager.h"
#include "ScreenManager.h"

#include "Interactions.h"
#include "Model.h"
#include "Wall.h"
class Camera
{
public:
	Camera();
	~Camera();

	enum ViewType {ORTHO,PERSP};
	void GenBuffer();
	void Render();

	glm::vec3 GetPosition() { return CamPos; }
	glm::mat4 GetYRot() { return rotY; }
	glm::mat4 GetXRot() { return rotX; }
	//rotation functions
	//zoom function
	void Inputs();
	void SetOrtho();
	void SetPersp();
	void D_SetPos(Model * D_Pos) { demon = D_Pos; };
private:

	Interactions inter;
	Model* demon;
	Wall* wall;
	ViewType m_ViewType;
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);

	glm::mat4 rotX;
	glm::mat4 rotY;

	glm::vec3 CamPos = glm::vec3(5.0f, 1.0f, 0.0f);
	glm::vec3 PrevCamPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 target = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 m_direction;
	glm::vec2 m_rotation;

	float axe_reach = 2.9f;
	float arena_radius = 13.0f;
	float demon_radius = 2.5f;
	glm::vec3 middle_arena = glm::vec3(0.0f, 0.0f, -2.0f);
	float wait = 0.0f;

	GLuint m_velocity;
	float m_fieldView;
	bool my_key = false;
	GLuint m_sensitivity;
	GLuint viewUniformID;
	GLuint projUniformID;
};

