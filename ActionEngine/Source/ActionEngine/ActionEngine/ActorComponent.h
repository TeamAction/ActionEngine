#pragma once

enum TYPE
{
	TICK,
	DRAW,
	DATA
};

class Actor;
class ActorComponent
{
public:
	ActorComponent(TYPE _objType) : objectType(_objType) {}
	virtual ~ActorComponent() = default;
	TYPE objectType;
};