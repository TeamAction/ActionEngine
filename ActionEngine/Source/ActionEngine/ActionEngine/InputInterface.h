#define DEBUG

#pragma once
#include <unordered_map>
#include <functional>
#include <Windows.h>

#ifdef DEFINE_GUID
// {D941B7E9-AC8A-4714-A1B9-BDF45D572552}
DEFINE_GUID(test, 0xd941b7e9, 0xac8a, 0x4714, 0xa1, 0xb9, 0xbd, 0xf4, 0x5d, 0x57, 0x25, 0x52);
#endif

struct Tigr;

class InputInterface
{
private:
	std::unordered_map<int,std::vector<std::function<void()>>> events;

	void fireEvent(std::vector<std::function<void()>> functions);
public:
#ifdef DEBUG
	int keyboard[256];
#endif // DEBUG
	int mouseX, mouseY, mouseB1, mouseB2, mouseB3;

	void prossesInput(Tigr* screen);
	void bindEvent(int key, std::function<void()> func);
};

