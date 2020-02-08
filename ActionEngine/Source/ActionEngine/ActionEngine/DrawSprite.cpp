#include "DrawSprite.h"

DrawSprite::DrawSprite(std::vector<drawObject> _obj, int _layer, float _loopTime) :DrawInterface(_layer) , object(_obj) , loopTime(_loopTime) {}

void DrawSprite::onStart(float dt)
{
	nextFunction = static_cast<void(DrawInterface::*)(float dt)>(&DrawSprite::onAddObject);
	numberOfFrames = object.size();
	timer = loopTime;
	loopTime = loopTime / (numberOfFrames-1);
	onAddObject(dt);
}

void DrawSprite::onAddObject(float dt)
{
	timer += dt;
	currentFrame = int(timer/loopTime) % numberOfFrames;
	convertToScreenSpace(object[currentFrame]);
	Renderer::Instance()->addDrawItem(layer, object[currentFrame]);
}