#include "DrawSprite.h"

DrawSprite::DrawSprite(drawObject _obj, int _layer) :DrawInterface(_layer) , object(_obj), objectOffset(_obj.screenPosition){}

void DrawSprite::onStart(Actor * current, float dt)
{
	actorTransform = static_cast<DataInterface<v2>*>(current->getComponent("transform"));
	nextFunction = static_cast<void(DrawInterface::*)(Actor *current, float dt)>(&DrawSprite::onAddObject);
	onAddObject(current, dt);
}

void DrawSprite::onAddObject(Actor *current, float dt)
{
	object.screenPosition = v2(actorTransform->getData())+objectOffset;
	ActionEngine::Instance()->addDrawItem(layer, object);
}