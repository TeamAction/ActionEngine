#pragma once
#include "ActorComponent.h" 
#include "drawHelper.h"

class DrawInterface: public ActorComponent
{
public:
	DrawInterface(drawObject _obj, int _layer) : ActorComponent(DRAW), object(_obj), layer(_layer) {}
	virtual int getLayer() =0;
	virtual drawObject getObject()= 0;
protected:
	drawObject object;
	int layer;
};