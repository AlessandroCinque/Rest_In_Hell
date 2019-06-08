#include "Camera.h"

Camera::Camera()
{
	rotX = glm::mat4(1.0f);
	rotY = glm::mat4(1.0f);


	m_rotation = glm::vec2(0.0f);

	m_velocity = (GLuint)1;
	m_fieldView = 45.0f;
	m_sensitivity = (GLuint)1;
}


Camera::~Camera()
{
}

void Camera::GenBuffer()
{
	GLuint shaderProgramID = TheShader::Instance()->GetShaderProgram();
	viewUniformID = glGetUniformLocation(TheShader::Instance()->GetShaderProgram(), "view");
}

void Camera::SetOrtho()
{
	m_ViewType = ORTHO;
}

void Camera::SetPersp()
{
	m_ViewType = PERSP;
}

void Camera::Render()
{
	TheShader::Instance()->SendUniformData("CamPos", CamPos);
	if (m_ViewType == PERSP)
	{
		view = glm::mat4(1.0);
		view = glm::lookAt(CamPos, CamPos + target, glm::vec3(0.0f, 1.0f, 0.0f));

		glUniformMatrix4fv(viewUniformID, 1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(projUniformID, 1, GL_FALSE, &proj[0][0]);

		//=====================================

		projUniformID = glGetUniformLocation(TheShader::Instance()->GetShaderProgram(), "proj");
	//do not touch the "GL_DEPTH_TEST part!!!
	glEnable(GL_DEPTH_TEST);

	proj = glm::mat4(1.0f);
	proj = glm::perspective(m_fieldView, 1280.0f / 720.0f, 0.1f, 1000.0f);
	glUniformMatrix4fv(projUniformID, 1, GL_FALSE, &proj[0][0]);
	SDL_SetRelativeMouseMode(SDL_TRUE);

	}
	else
	{
		view = glm::mat4(1.0f);
		glUniformMatrix4fv(viewUniformID, 1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(projUniformID, 1, GL_FALSE, &proj[0][0]);

		//=====================================

		projUniformID = glGetUniformLocation(TheShader::Instance()->GetShaderProgram(), "proj");
		//do not touch the "GL_DEPTH_TEST part!!!
		glDisable(GL_DEPTH_TEST);

		proj = glm::mat4(1.0f);
		proj = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f);

		glUniformMatrix4fv(projUniformID, 1, GL_FALSE, &proj[0][0]);
		SDL_SetRelativeMouseMode(SDL_TRUE);


	}
}

void Camera::Inputs()
{
	float dt = SDL_GetTicks() /100.0f;
	wait -= dt;
	m_direction = glm::vec3(0.0f, 0.0f, 0.0f);
	PrevCamPos = CamPos;

	if (TheInputManager::Instance()->GetKey() == SDLK_w && TheInputManager::Instance()->isKeyPressed() && (inter.Collision(CamPos,demon->GetPosition(), demon_radius) !=1) && (inter.Collision(CamPos, middle_arena, arena_radius) == 1))
	{
		m_direction = glm::vec3(0.0f, 0.0f, -0.1f);
		//For preventing players to fly
		if (CamPos.y > 1.0f || CamPos.y < 1.0f)
		{
			CamPos.y = 1.0f;
		}
	}
	if (TheInputManager::Instance()->GetKey() == SDLK_a && TheInputManager::Instance()->isKeyPressed() && (inter.Collision(CamPos, demon->GetPosition(), demon_radius) != 1) && (inter.Collision(CamPos, middle_arena, arena_radius) == 1))
	{	
		m_direction = glm::vec3(-0.1f, 0.0f, 0.0f);
	}
	if (TheInputManager::Instance()->GetKey() == SDLK_s && TheInputManager::Instance()->isKeyPressed() && (inter.Collision(CamPos, demon->GetPosition(), demon_radius) != 1) && (inter.Collision(CamPos, middle_arena, arena_radius) == 1))
	{
		m_direction = glm::vec3(0.0f, 0.0f, 0.1f);
		//For preventing players to fly
		if (CamPos.y > 1.0f || CamPos.y < 1.0f)
		{
			CamPos.y = 1.0f;
		}
	}
	if (TheInputManager::Instance()->GetKey() == SDLK_d && TheInputManager::Instance()->isKeyPressed() && (inter.Collision(CamPos, demon->GetPosition(), demon_radius) != 1) && (inter.Collision(CamPos, middle_arena, arena_radius) == 1))
	{
		m_direction = glm::vec3(0.1f, 0.0f, 0.0f);
	}

	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT) && ( inter.Collision(CamPos, demon->GetPosition(), axe_reach) == 1))
	{
		wait = 3.0f;
		demon->SetStrike(true);
	}
	if (wait <= 0)
	{
		demon->SetStrike(false);
	}

	//rotation
	glm::vec2 mouseMotion = TheInputManager::Instance()->GetMouseMotion();
	m_rotation.x += mouseMotion.x / 10;
	m_rotation.y += mouseMotion.y / 10;

	//rotation matrix
	rotX = glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.x), glm::vec3(0.0f, -1.0f, 0.0f)); //yaw
	rotY = glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.y), glm::vec3(-1.0f, 0.0f, 0.0f)); //pitch

	glm::mat4 totalRotation = rotX * rotY; // DO NOT CHANGE THE ORDER!!!

	target = glm::vec3(0.0f, 0.0f, -1.0f);
	target = totalRotation * glm::vec4(target, 1.0f);

	// transform movement
	m_direction = totalRotation * glm::vec4(m_direction, 1.0f);

	//calculate postion
	CamPos += m_direction;
	if (inter.Collision(CamPos, demon->GetPosition(), demon_radius) == 1)
	{
		CamPos = PrevCamPos;
	}
	if (inter.Collision(CamPos, middle_arena, arena_radius) != 1)
	{
		CamPos = PrevCamPos;
	}
}
