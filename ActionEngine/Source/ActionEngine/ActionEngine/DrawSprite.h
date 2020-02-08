#pragma once
#include "DrawInterface.h"
#include "DataInterface.h"


class DrawSprite :public DrawInterface
{
public:
	DrawSprite(std::vector<drawObject> _obj,int _layer, float _loopTime);
private:
	virtual void onStart(float dt);
	virtual void onAddObject(float dt);
	int currentFrame = 0;
	int numberOfFrames = 0;
	float loopTime = 5.0f;
	float timer = 0.0f;
	std::vector<drawObject> object;
};

