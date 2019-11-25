#define DEBUG
#pragma once
#include <unordered_map>
#include <functional>
#include <Windows.h>


#define LEFTMOUSEBUTTON  -1
#define RIGHTMOUSEBUTTON  -2

struct Tigr;

class InputInterface
{
private:
	std::unordered_map<int,std::vector<std::function<void()>>> events;
	void fireEvent(std::vector<std::function<void()>> functions);
	bool getEventTrigger(int key);

public:
#ifdef DEBUG
	int keyboard[256];
#endif // DEBUG
	int mouseX, mouseY, mouseB1, mouseB2, mouseB3;

	void prossesInput(Tigr* screen);
	void bindEvent(int key, std::function<void()> func);
	//void unBindEvent(int key, std::function<void()> func);
};

