#pragma once
#include "ActorComponent.h" 
#include "helperStructs.h"
#include "Actor.h"

class DrawInterface: public ActorComponent
{
public:
	DrawInterface(int _layer) : ActorComponent(TYPE::DRAW),layer(_layer) {}
	void(DrawInterface::*nextFunction)(float dt) = &DrawInterface::onStart;
	inline void addObject(float dt) { (this->*nextFunction)(dt); }
	inline void convertToScreenSpace(drawObject &obj) 
	{
		obj.screenScale = Renderer::Instance()->getScreenScale(); // should be mutipled by scale when implimented
		obj.screenPosition = owner->getGlobalTransform() * obj.screenScale;
	}

protected:
	virtual void onAddObject(float dt) = 0;
	virtual void onStart(float dt) = 0;
	int layer;
};