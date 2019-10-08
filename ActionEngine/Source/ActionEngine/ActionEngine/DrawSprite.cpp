#include "DrawSprite.h"

DrawSprite::DrawSprite(drawObject _obj, int _layer) :DrawInterface(_obj, _layer)
{}

int DrawSprite::getLayer()
{
	return layer;
}

drawObject DrawSprite::getObject()
{
	return object;
}
