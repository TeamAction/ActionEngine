#pragma once
#include "ComponentInterface.h" 


class Action : public ComponentInterface
{
	void tick(Actor *current, float dt);
};