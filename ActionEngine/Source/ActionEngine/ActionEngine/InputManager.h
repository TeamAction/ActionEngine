#pragma once
struct Tigr;

class InputManager
{
private:
	static InputManager* s_pInstance;
	InputManager() {}
	int mouseX, mouseY, mouseB1, mouseB2, mouseB3;
public:
	static InputManager* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new InputManager();
		}
		return s_pInstance;
	}

	bool getKeyDown(char c);
	void updateMouse();
	int getMouseX();
	int getMouseY();
	bool getMouseRightButton();
	bool getMouseLeftButton();
};

