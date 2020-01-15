#pragma once
#include "ActorComponent.h" 
#include "drawHelper.h"
#include "Actor.h"

class DrawInterface: public ActorComponent
{
public:
	DrawInterface(int _layer) : ActorComponent(TYPE::DRAW),layer(_layer) {}
	void(DrawInterface::*nextFunction)(float dt) = &DrawInterface::onStart;
	inline void addObject(float dt) { (this->*nextFunction)(dt); }
	inline void convertToScreenSpace(drawObject &obj,v2 offset) 
	{
		obj.screenScale = Renderer::Instance()->getScreenScale();
		obj.screenPosition = (v2(owner->getGlobalTransform()) + offset) * obj.screenScale;
	}

protected:
	virtual void onAddObject(float dt) = 0;
	virtual void onStart(float dt) = 0;
	int layer;
};