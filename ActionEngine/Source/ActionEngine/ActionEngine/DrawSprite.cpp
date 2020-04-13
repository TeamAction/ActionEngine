#include "DrawSprite.h"

DrawSprite::DrawSprite(animation _anim, int _layer) :DrawInterface(_layer) , anim(_anim){}

void DrawSprite::setAnimation(animation _anim)
{
	anim = _anim;
	timer = 0;
	loopTime = 0;
	if (anim.spriteIndex.size() > 1 && anim.loopTime > 0)
	{
		timer = anim.loopTime;
		loopTime = anim.loopTime / (anim.spriteIndex.size() - 1);
	}
}

void DrawSprite::onStart(float dt)
{
	nextFunction = static_cast<void(DrawInterface::*)(float dt)>(&DrawSprite::onAddObject);
	if (anim.spriteIndex.size() > 1 && anim.loopTime >0)
	{
		timer = anim.loopTime;
		loopTime = anim.loopTime / (anim.spriteIndex.size() - 1);
	}
	onAddObject(dt);
}

void DrawSprite::onAddObject(float dt)
{
	timer += dt;
	if (loopTime != 0)
	{
		currentFrame = int(timer / loopTime) % anim.spriteIndex.size();
	}
	else 
	{
		currentFrame = 0;
	}
	Renderer::Instance()->addDrawItem(layer, drawObject(anim.spriteIndex[currentFrame], owner->getGlobalTransform() * Renderer::Instance()->getScreenScale(), Renderer::Instance()->getScreenScale()));
}