#pragma once

class Actor;

enum TYPE
{
	TICK
};

class ComponentInterface
{
public:
	virtual void tick(Actor* current,float dt) =0;
};