#pragma once
#include "ComponentInterface.h"
#include <vector>
#include <algorithm>

class Actor
{
public:
	void tick();
private:
		std::vector<ComponentInterface> components;
};