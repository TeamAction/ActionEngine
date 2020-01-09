#include "InputManager.h"
#include "tigr.h"
#include "ActionEngine.h"
#include <windows.h>
#include <algorithm>
#include "EventManager.h"

InputManager* InputManager::s_pInstance = nullptr;

void InputManager::updateInputState()
{
	for (int i = 0; i < 256; i++)
	{
		prevKeyboardState[i] = keyboardState[i];
		keyboardState[i] = GetAsyncKeyState(i);
	}
	tigrMouse2(ActionEngine::Instance()->screen, &mouseX, &mouseY, &mouseB1, &mouseB2, &mouseB3);
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
	return mouseB3;
}

bool InputManager::getMouseLeftButton()
{
	return mouseB1;
}

void InputManager::fireInputEvents() //should be replaced by a system to bind and free events to key and mouse clicks
{
	updateInputState();
	if (InputManager::Instance()->getKeyDown(' '))
	{
		EventManager::Instance()->fireEvent("spaceKey");
	}
	if (InputManager::Instance()->getMouseLeftButton())
	{
		EventManager::Instance()->fireEvent("click to spawn", getMouseX(), getMouseY());
	}

}
