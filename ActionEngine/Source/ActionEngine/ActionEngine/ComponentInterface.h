#pragma once

enum TYPE
{
	TRANSFORM,
	ACTION
};

class ComponentInterface
{
public:
	TYPE type;
	virtual void tick() = 0;
};