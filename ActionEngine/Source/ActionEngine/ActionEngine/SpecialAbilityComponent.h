#pragma once
#include "ComponentInterface.h" 


class SpecialAbilityComponent : public ComponentInterface
{
	SpecialAbilityComponent();
	~SpecialAbilityComponent();
	void tick();
};