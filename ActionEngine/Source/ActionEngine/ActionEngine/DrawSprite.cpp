#include "DrawSprite.h"

DrawSprite::DrawSprite(drawObject _obj, int _layer) :DrawInterface(_obj, _layer)
{}

int DrawSprite::getLayer(Actor *current, float dt)
{
	return layer;
}

drawObject DrawSprite::getObject(Actor *current, float dt)
{
	if (!actorTransform)
		actorTransform = ((DataInterface<v2>*)current->components["transform"]);
	return drawObject(object.spriteIndex,object.screenPosition + actorTransform->getData());
}
