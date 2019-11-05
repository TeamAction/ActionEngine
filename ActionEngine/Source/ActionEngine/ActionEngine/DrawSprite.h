#pragma once
#include "DrawInterface.h"
#include "ScriptInterface.h"
#include "DataInterface.h"


class DrawSprite :public DrawInterface
{
public:
	DrawSprite(drawObject _obj,int _layer);
private:
	virtual void onStart(Actor *current, float dt);
	virtual void onAddObject(Actor *current, float dt);
	drawObject object;
	v2 objectOffset;
	DataInterface<v2>* actorTransform;
};

