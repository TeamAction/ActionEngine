#pragma once
#include "DrawInterface.h"
#include "DataInterface.h"


class DrawSprite :public DrawInterface
{
public:
	DrawSprite(animation _anim, int _layer);
	void setAnimation(animation _anim);
	void setMirror(bool _mirror);
private:
	virtual void onStart(float dt);
	virtual void onAddObject(float dt);
	int flip = 0x00000000;
	int currentFrame = 0;
	float loopTime = 0.0f;
	float timer = 0.0f;
	animation anim;
};

