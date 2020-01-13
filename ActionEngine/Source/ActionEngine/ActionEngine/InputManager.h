#pragma once
#include <stdint.h>
struct Tigr;

class InputManager
{
private:
	static InputManager* s_pInstance;
	InputManager() {updateInputState();}
	~InputManager(){delete s_pInstance;s_pInstance = nullptr;}
	int mouseX, mouseY;
	uint32_t mouseButtons;
	int keyboardState[256] = {0};
	int prevKeyboardState[256] = {0};
public:
	static InputManager* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new InputManager();
		}
		return s_pInstance;
	}
	void updateInputState();
	bool getKeyHeld(int c);
	bool getKeyDown(int c);
	bool getKeyUp(int c);
	int getMouseX();
	int getMouseY();
	bool getMouseRightButton();
	bool getMouseLeftButton();
	void fireInputEvents();
};

