#pragma once
#include "Singleton.h"
#include <Windows.h>
#include <gl/GL.h>
#include <SDL.h>
#include <glm.hpp>
typedef const Uint8* KeyState;
class InputManager
{
public:
	friend class Singleton<InputManager>;
public:
	char GetKey() { return m_Key; }
	bool IsXClicked() { return m_isXClicked; }
	bool isKeyPressed() { return m_isKeyPressed; }

	glm::vec2 GetMousePos() { return m_mousePos; }
	glm::vec2 GetMouseMotion() { return m_mouseMotion; }
	
	bool IsRightButtonClicked() { return m_isRightButtonClicked; }
	bool IsLeftButtonClicked() { return m_isLeftButtonClicked; }

	bool IsScrollUP() { return m_ScrollUp; }
	bool IsScrollDOWN() { return m_ScrollDown; }
	KeyState GetKeyStates();
public:
	void Update();
private:
	InputManager() {}
	InputManager(const InputManager&);
	InputManager& operator=(const InputManager&);
private:
	int last= 0;
	char m_Key;
	int m_Wheel;
	bool m_isKeyPressed= false;
	bool m_isXClicked = false;

	bool m_isLeftButtonClicked = false;
	bool m_isRightButtonClicked = false;

	bool m_ScrollUp = false;
	bool m_ScrollDown = false;

	glm::vec2 m_mousePos = glm::vec2(0.0f,0.0f);
	glm::vec2 m_mouseMotion= glm::vec2(0.0f, 0.0f);
	
};
typedef Singleton<InputManager> TheInputManager;

//InputManager();
//~InputManager();