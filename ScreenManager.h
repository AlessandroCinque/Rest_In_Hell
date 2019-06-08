#pragma once
#ifndef ScreenMANAGER_H
#define ScreenMANAGER_H
#include "Singleton.h"
#include <iostream>
#include <SDL.h>
#include "string"
class ScreenManager
{


public:
	friend class Singleton<ScreenManager>;

public:

	void InitScreen(const char* name, int x, int y, int w,int h, bool compatibility);
	void ShutDown();
	void SwapBuffer();
	void ClearScreen();
	void DisplayProfile();
	void View();
private:

	ScreenManager() {}
	ScreenManager(const ScreenManager&);
	ScreenManager& operator=(const ScreenManager&);
	SDL_Window* window = nullptr;
	SDL_GLContext context = nullptr;

};
typedef Singleton<ScreenManager> TheScreenManager;

#endif // !MANAGER_H

