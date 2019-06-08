#include <iostream>
#include <string>
#include <math.h>

#include <SDL.h>
#include <glew.h>
#include <glm.hpp>
#include<gtc/matrix_transform.hpp>

#include<vector>

#include "InputManager.h"
#include "ScreenManager.h"
#include "ShaderManager.h"
#include "Quad.h"
#include"Camera.h"
#include "SkyBox.h"
#include "Sprite.h"
#include "Wall.h"
#include "Text.h"
#include "Light.h"
#include "Model.h"

#include "Interactions.h"

bool isGameRunning = true;
Model model;
Quad quad;
Camera camera;
SkyBox sky;
Sprite sprite;
Light light;

Interactions inter;

Wall wall1;
Wall wall2;
Wall wall3;
Wall wall4;
Wall wall5;
Wall wall6;


void GenBuffers()
{
	
	master_wall.push_back(&wall1);
	master_wall.push_back(&wall2);
	master_wall.push_back(&wall3);
	master_wall.push_back(&wall4);
	master_wall.push_back(&wall5);
	master_wall.push_back(&wall6);

	quad.GenBuffer();
	camera.GenBuffer();
	camera.SetPersp();
	light.Create();
	sky.GenBuffer();
	sprite.GenBuffer();	
	for (auto it = master_wall.begin(); it != master_wall.end(); it++)
	{
		(*it)->GenBuffer();
	}
	//==============
	model.Create();
	model.IsTextured();
	model.SetShininess(10.0f);
	model.SetAmbient(0.25f, 0.25f, 0.25f);
	model.SetDiffuse(0.45f, 0.45f, 0.45f);
	model.SetSpecular(0.5f,0.5f,0.5f);
	model.SetScale(0.3f,0.3f,0.3f);
	model.SetRotation(0.0f,0.0f,0.0f);

	model.SetPosition(1.0f,-0.1f,-10.0f);
	camera.D_SetPos(&model);
	// Model kindly given by the Artist Florin-Eugen Balea.
	model.LoadModel("Assets/3D/Florin/move/minotaur_move_07.obj");
	model.IsTextured()= false;
	//================
	GLenum errorCode = glGetError();
	if (errorCode == GL_NO_ERROR)
	{
		std::cout << "all goood" << std::endl;
	}
	else if (errorCode == GL_INVALID_OPERATION)
	{
		std::cout << "Error rendering: "<< errorCode << std::endl;
	}
}
void FillBuffer() 
{
	camera.SetPersp();
	quad.FillBuffer();
	sky.FillBuffer();

	for (auto it = master_wall.begin(); it != master_wall.end(); it++)
	{
		(*it)->FillBuffer();
	}


	sprite.SetDimension(400, 600);
	sprite.SetAmIAnim(true);
	sprite.SetDim(5,1);
	sprite.FillBuffer();

}
void Update() 
{
	camera.Inputs();

	//Testing Purposes
	/*glm::vec3 L_pos = light.GetPosition();
	std::cout << "x: " << L_pos.x << " y: " << L_pos.y << " z: " << L_pos.z << std::endl;*/

	light.Inputs();
	sprite.Inputs();
	glm::vec3 d_position= model.GetPosition();
	glm::vec3 c_position = camera.GetPosition();
	
	// Making the Demon/Minotaur ROTATE towards the camera.
	float angle = atan2(c_position.z - d_position.z,c_position.x - d_position.x);
	float d_angle = (float)angle * 180.0f / 3.14f;
	//I guess that something is wrong with the orientation of the model,hence I worte this weird "-d_angle - 270.0f" is the only way to make it turn correctly
	model.SetRotation(1.0f,-d_angle - 270.0f,1.0f);
	// Making the Demon/Minotaur MOVE towards the camera.
	float x_Distance = c_position.x - d_position.x;
	float z_Distance = c_position.z - d_position.z;
	float hypo = sqrt((x_Distance*x_Distance) + (z_Distance*z_Distance));

	if (hypo>3.0f)
	{
		d_position.x +=  0.04f*(x_Distance/hypo);
		d_position.z += 0.04f*(z_Distance/hypo);
	}
	model.SetPosition(d_position.x, d_position.y, d_position.z);
	model.Update();

}
void Render() 
{
	camera.SetPersp();
	camera.Render();
	quad.Render();
	sky.Render();
	light.Draw();

	model.Draw();
	// Upper half
	master_wall[0]->Render(glm::vec3(0.0f, 2.0f, -15.0f),0);
	master_wall[1]->Render(glm::vec3(-15.0f, 2.0f, -9.0f),45);
	master_wall[2]->Render(glm::vec3( 16.8f, 2.0f, -10.0f),135);
	//bottom half
	master_wall[3]->Render(glm::vec3(0.0f, 2.0f, 12.0f),0);
	master_wall[4]->Render(glm::vec3(-15.0f, 2.0f, 3.0f), 135);
	master_wall[5]->Render(glm::vec3( 16.8f, 2.0f, 5.0f), 45);
	camera.SetOrtho();
	camera.Render();
	sprite.Render();
}
void DestroyBuffer() 
{
	
	quad.DestroyBuffer();
	sky.DestroyBuffer();
	sprite.DestroyBuffer();
	light.Destroy();
	model.Destroy();
	
	for (auto it = master_wall.begin(); it != master_wall.end(); it++)
	{
		(*it)->DestroyBuffer();
	}
}
int main(int argc, char* args[])
{
	TheScreenManager::Instance()->InitScreen("First window",200,30,900,800,true);
	TheScreenManager::Instance()->DisplayProfile();
	TheScreenManager::Instance()->View();
	if (!TheShader::Instance()->CreateProgram()) 
	{
		std::cout << "Something is wrong with the bloody solution!!!"<<std::endl;
	}

	TheShader::Instance()->CreateShader();
	TheShader::Instance()->CompileShader();
	TheShader::Instance()->AttachShader();
	TheShader::Instance()->LinkProgram();
	//====================================== GEN BUFFER!!! =============
	GenBuffers();
	FillBuffer();
	//====================================== MAIN LOOP =================
	while (isGameRunning)
	{
		TheScreenManager::Instance()->ClearScreen();
		TheInputManager::Instance()->Update();
		if(TheInputManager::Instance()->IsXClicked())
		{
			isGameRunning = false;
		}
		if (TheInputManager::Instance()->GetKey()== SDLK_ESCAPE)
		{
			isGameRunning = false;
		}
		//===================== RENDERING & UPDATING !!! ======================
		Update();
		Render();		
		//render the data
		TheScreenManager::Instance()->SwapBuffer();
	}

	
	//destroy the VBO buffer
	DestroyBuffer();
	TheScreenManager::Instance()->ShutDown();

	TheShader::Instance()->DetachShader();
	TheShader::Instance()->DestroyProgram();
	TheShader::Instance()->DestroyShader();
	system("pause");
	return 0;
	
}