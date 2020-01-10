#include "SampleMouseClickScript.h"
#include "SampleActorScript.h"
#include "DrawSprite.h"
#include "ActionEngine.h"

#include "InputManager.h"


void SampleActorMouseClick::onStart(float dt)
{
	nextFunction = static_cast<void(ScriptInterface::*)(float dt)>(&SampleActorMouseClick::onTick);
	EventManager<int,int>::Instance()->bindEvent("click to spawn", std::bind(&SampleActorMouseClick::mouseClickTest,this, std::placeholders::_1, std::placeholders::_2));
	onTick(dt);
}

void SampleActorMouseClick::mouseClickTest(int x, int y)
{
	v2 spawnCoordinates(x, y);
	Actor* temp = new Actor("scrolling rock",owner);
	temp->addComponent("transform", new DataInterface<v2>(spawnCoordinates));
	temp->addComponent("testImage", new DrawSprite(drawObject(1, v2(0, 0)), 1));
	temp->addComponent("testScrolling", new SampleActorScript());
	//ActionEngine::Instance()->addActor(temp);
}


void SampleActorMouseClick::onTick(float dt)
{
}
