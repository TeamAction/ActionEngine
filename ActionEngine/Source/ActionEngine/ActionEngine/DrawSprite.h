#pragma once
#include "DrawInterface.h"
#include "ScriptInterface.h"
#include "DataInterface.h"


class DrawSprite :public DrawInterface
{
public:
	DrawSprite(drawObject _obj,int _layer);
	virtual void addObject(Actor *current, float dt);
private:
	DataInterface<v2>* actorTransform;
};

