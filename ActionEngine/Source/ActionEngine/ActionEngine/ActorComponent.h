#pragma once

enum TYPE
{
	TICK,
	DRAW,
	DATA
};

class ActorComponent
{
public:
	ActorComponent(TYPE _objType) : objectType(_objType) {}
	TYPE objectType;
};