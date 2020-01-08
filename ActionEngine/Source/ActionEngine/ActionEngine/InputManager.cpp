#include "InputManager.h"
#include "tigr.h"
#include "ActionEngine.h"
#include <windows.h>
#include <algorithm>

InputManager* InputManager::s_pInstance = nullptr;

bool InputManager::getKeyDown(char c)
{
	if (GetAsyncKeyState(c)!=0)
		return true;
	return false;
}

void InputManager::updateMouse()
{
	tigrMouse2(ActionEngine::Instance()->screen, &mouseX, &mouseY, &mouseB1, &mouseB2, &mouseB3);
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
