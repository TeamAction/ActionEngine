#pragma once
#include "Renderer.h"

enum class TYPE
{
	TICK,
	DRAW,
	DATA,
	RIGIDBODY
};


class Actor;
class ActorComponent
{
public:
	ActorComponent(TYPE _objType) : objectType(_objType) {}
	virtual ~ActorComponent() = default;
	TYPE objectType;
	Actor* owner;
	void SetOwner(Actor* _owner){owner = _owner;}
};