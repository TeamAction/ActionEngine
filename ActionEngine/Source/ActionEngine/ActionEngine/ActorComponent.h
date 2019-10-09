#pragma once
#include "ComponentNameEnum.h"

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
	TYPE objectType;
};