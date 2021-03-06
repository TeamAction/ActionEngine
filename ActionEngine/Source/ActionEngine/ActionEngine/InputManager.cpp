#pragma once
#include "InputManager.h"
#include "SDL/SDL_mouse.h"
#include <windows.h>
#include "Renderer.h"

InputManager* InputManager::s_pInstance = nullptr;

void InputManager::updateInputState()
{
	for (int i = 0; i < 256; i++)
	{
		prevKeyboardState[i] = keyboardState[i];
		keyboardState[i] = GetAsyncKeyState(i);
	}
	mouseButtons = SDL_GetMouseState(&mouseX, &mouseY);
	mouseX /= Renderer::Instance()->getWidth() / 640.0f;
	mouseY /= Renderer::Instance()->getHeight() / 480.0f;
}

bool InputManager::getKeyHeld(int c)
{
	if (keyboardState[c] != 0 )
		return true;
	return false;
}

bool InputManager::getKeyDown(int c)
{
	if (keyboardState[c] != 0 && prevKeyboardState[c] == 0)
 		return true;
	return false;
}

bool InputManager::getKeyUp(int c)
{
	if (keyboardState[c] == 0 && prevKeyboardState[c] != 0)
 		return true;
	return false;
}

int InputManager::getMouseX()
{
	return mouseX;
}

int InputManager::getMouseY()
{
	return mouseY;
}

bool InputManager::getMouseRightButton()
{
	return 	SDL_BUTTON(mouseButtons)== SDL_BUTTON_RIGHT;
}

bool InputManager::getMouseLeftButton()
{
	return 	SDL_BUTTON(mouseButtons)== SDL_BUTTON_LEFT;
}

void InputManager::debugPrintKeyState()
{
	std::string buffer;
	for (int i = 0; i < 256; i++)
	{
		if (keyboardState[i] != 0)
		{
		buffer += "," + std::to_string(i);

		}
	}
	buffer += "\n";
	Renderer::Instance()->addScreenText(100, 100, buffer, 0.0f);
}