#include <iostream>
#include "ScreenManager.h"
#include "Singleton.h"
#include <glew.h>
#include <SDL.h>


void ScreenManager::InitScreen(const char* name, int x, int y, int w,int h,bool compatibility)
{
	//================== Initialization ======================

	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		//In case you didn`t setted up properly OPENGL this massage will be show
		std::cout << "Error!You didn`t setted up properly" << std::endl;
	}
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);


	//Switch on double buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	if(compatibility == false)
	{
		// set a CORE OpenGL context
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		std::cout << "Core Mode : ON" << std::endl;
	}
	else 
	{
		//set COMPATIBILITY
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
		std::cout << "Core Mode : OFF (COMPATIBILITY ACTIVATED)" << std::endl;
	}

	//============= Setting the right Version for the Potato Laptop =============

	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	if(!SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4))
	{
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	}
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

	window = SDL_CreateWindow(name, x, y, w, h, SDL_WINDOW_OPENGL);
	if (window == nullptr)
	{
		//The pointer is not working
		std::cout << "Error creating game window" << std::endl;
	}
	//context
	context = SDL_GL_CreateContext(window);

	if (context == nullptr)
	{
		std::cout << "Error creating OpenGL context" << std::endl;
	}

	//============== init glew ================
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Could not init GLEW" << std::endl;
	}
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void ScreenManager::SwapBuffer()
{
	//swap the frame buffers
	SDL_GL_SwapWindow(window);
}
void ScreenManager::ClearScreen()
{
	glEnable(GL_DEPTH_TEST);
	//clear the screen
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}
void ScreenManager::DisplayProfile()
{
	std::cout << "vendor:" << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Model:" << glGetString(GL_RENDERER) << std::endl;
	std::cout << "Version:" << glGetString(GL_VERSION) << std::endl;
}
void ScreenManager::View()
{
	glViewport(0, 0, 900, 800);
}
void ScreenManager::ShutDown()
{
	//====================================== SHUT DOWN =================
	//free OpenGL context
	SDL_GL_DeleteContext(context);
	//free game window
	SDL_DestroyWindow(window);
	//shut down SDL
	SDL_Quit();

}