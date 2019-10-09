#pragma once
#include "DrawInterface.h"

class DrawSprite :public DrawInterface
{
public:
	DrawSprite(drawObject _obj,int _layer);
	virtual int getLayer(Actor *current, float dt);
	virtual drawObject getObject(Actor *current, float dt);
};

