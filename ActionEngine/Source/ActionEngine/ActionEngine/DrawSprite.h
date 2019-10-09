#pragma once
#include "DrawInterface.h"
#include "ActiveInterface.h"
#include "DataInterface.h"


class DrawSprite :public DrawInterface
{
public:
	DrawSprite(drawObject _obj,int _layer);
	virtual int getLayer(Actor *current, float dt);
	virtual drawObject getObject(Actor *current, float dt);
private:
	DataInterface<v2>* actorTransform;
};

