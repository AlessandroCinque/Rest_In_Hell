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
//===========================

class Interactions
{
public:
	Interactions();
	~Interactions();
	int Collision(glm::vec3 A, glm::vec3 B, float radius);
	int AABBCollision(glm::vec3 A, glm::vec3 B, glm::vec3 scale);
private:
	glm::vec3 m_nextP;
	glm::vec3 m_direction = glm::vec3(0.0f, 0.0f, 0.0f);
	float m_speed;
	float moveSpeed2 = 5.0f;
};

