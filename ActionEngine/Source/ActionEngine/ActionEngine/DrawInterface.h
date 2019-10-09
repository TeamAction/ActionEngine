#pragma once
#include "ActorComponent.h" 
#include "drawHelper.h"
#include "Actor.h"

class DrawInterface: public ActorComponent
{
public:
	DrawInterface(drawObject _obj, int _layer) : ActorComponent(DRAW), object(_obj), layer(_layer) {}
	virtual int getLayer(Actor *current, float dt) =0;
	virtual drawObject getObject(Actor *current, float dt)= 0;
protected:
	drawObject object;
	int layer;
};