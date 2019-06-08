#include "InputManager.h"
#include "Singleton.h"
#include <Windows.h>
#include <gl/GL.h>
#include <SDL.h>


// =================== USE SDLWIKI!!!!!! ======================

KeyState InputManager::GetKeyStates()
{
	return KeyState();
}

void InputManager::Update()
{
	//m_keyStates = SDL_GetKeyboard
	SDL_Event events;
	m_mouseMotion = glm::vec2( 0.0f,0.0f);
	events.wheel.y = 0;
	while (SDL_PollEvent(&events)) 
	{
		switch (events.type) 
		{
			case SDL_QUIT:
				{
					m_isXClicked = true;
					
					break;
				}
			case SDL_KEYDOWN:
				{
					m_isKeyPressed = true;
					m_Key = events.key.keysym.sym;
					break;
				}
			case SDL_KEYUP: 
			{
				m_isKeyPressed = false;
				m_Key = ' ';
				break;
			}
			case SDL_MOUSEMOTION: 
			{
				//m_mouseMotion = glm::vec2(events.motion.x, events.motion.y);

				m_mouseMotion = glm::vec2(events.motion.xrel, events.motion.yrel);
				break;
			}
			case SDL_MOUSEBUTTONUP: 
			{
				if (events.button.button != SDL_BUTTON_RIGHT) 
				{
					m_isRightButtonClicked = false;
				}
				if (events.button.button != SDL_BUTTON_LEFT) 
				{
					m_isLeftButtonClicked = false;
				}
				break;
			}
			case SDL_MOUSEBUTTONDOWN:
			{
				if (events.button.button == SDL_BUTTON_RIGHT) 
				{
					m_isRightButtonClicked = true;
				}
				if (events.button.button == SDL_BUTTON_LEFT) 
				{
					m_isLeftButtonClicked = true;
				}
					break;
			}
			case SDL_MOUSEWHEEL:
			{
				
				if (events.wheel.y > 0)
				{
					m_ScrollUp = true;
					//events.wheel.y = 0;
				}
				else
				{
					m_ScrollUp = false;
				}
				if (events.wheel.y <0)
				{
					m_ScrollDown = true;
				}
				else 
				{
					m_ScrollDown = false;
				}
				
				break;
			}
		}
		
	}
}


