#pragma once
#include "Component.h"

class AbilitiesInterface : public Component
{
public:
	virtual void tick() =0;
};