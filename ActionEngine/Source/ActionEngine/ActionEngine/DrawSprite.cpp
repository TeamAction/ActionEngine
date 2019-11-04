#include "DrawSprite.h"

DrawSprite::DrawSprite(drawObject _obj, int _layer) :DrawInterface(_obj, _layer)
{}

void DrawSprite::addObject(Actor *current, float dt)
{
	if (!actorTransform)
		actorTransform = ((DataInterface<v2>*)current->getComponent("transform"));
	object.screenPosition = v2(actorTransform->getData());
	ActionEngine::Instance()->addDrawItem(object.spriteIndex, object);
}
