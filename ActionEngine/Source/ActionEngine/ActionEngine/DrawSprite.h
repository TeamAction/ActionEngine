#pragma once
#include "DrawInterface.h"

class DrawSprite :public DrawInterface
{
public:
	DrawSprite(drawObject _obj,int _layer);
	virtual int getLayer();
	virtual drawObject getObject();
};

