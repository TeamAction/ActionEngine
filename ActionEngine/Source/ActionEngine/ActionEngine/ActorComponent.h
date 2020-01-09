#pragma once
#include "ActionEngine.h"

enum class TYPE
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