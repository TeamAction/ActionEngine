#pragma once
#include "DrawInterface.h"
#include "ScriptInterface.h"
#include "DataInterface.h"


class DrawSprite :public DrawInterface
{
public:
	DrawSprite(drawObject _obj,int _layer);
private:
	virtual void onStart(float dt);
	virtual void onAddObject(float dt);
	drawObject object;
	v2 objectOffset;
};

