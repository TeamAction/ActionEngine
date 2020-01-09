#pragma once
struct Tigr;

class InputManager
{
private:
	static InputManager* s_pInstance;
	InputManager() {}
	int mouseX = 0, mouseY = 0, mouseB1 = 0, mouseB2 = 0, mouseB3 =0;
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

