#include "DrawSprite.h"
#include "SDL/SDL_rect.h"

DrawSprite::DrawSprite(drawObject _obj, int _layer) :DrawInterface(_layer) , object(_obj), objectOffset(_obj.screenPosition){}

void DrawSprite::onStart(float dt)
{
	nextFunction = static_cast<void(DrawInterface::*)(float dt)>(&DrawSprite::onAddObject);
	onAddObject(dt);
}

void DrawSprite::onAddObject(float dt)
{
	object.screenPosition = v2(owner->getGlobalTransform())+objectOffset;
	Renderer::Instance()->addDrawItem(layer, object);
}