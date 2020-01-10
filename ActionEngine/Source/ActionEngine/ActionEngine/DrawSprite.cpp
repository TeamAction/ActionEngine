#include "DrawSprite.h"

DrawSprite::DrawSprite(drawObject _obj, int _layer) :DrawInterface(_layer) , object(_obj), objectOffset(_obj.screenPosition){}

void DrawSprite::onStart(float dt)
{
	actorTransform = static_cast<DataInterface<v2>*>(owner->getComponent("transform"));
	nextFunction = static_cast<void(DrawInterface::*)(float dt)>(&DrawSprite::onAddObject);
	onAddObject(dt);
}

void DrawSprite::onAddObject(float dt)
{
	object.screenPosition = v2(actorTransform->getData())+objectOffset;
	ActionEngine::Instance()->addDrawItem(layer, object);
}