#pragma once
#include <unordered_map>
#include <functional>


struct Tigr;

class InputInterface
{
private:
	std::unordered_map<int,std::vector<std::function<void()>>> events;
public:
	int keyboard[256];
	int mouseX, mouseY, mouseB1, mouseB2, mouseB3;

	void prossesInput(Tigr* screen);
	void bindEvent(int key, std::function<void()> func);
};

