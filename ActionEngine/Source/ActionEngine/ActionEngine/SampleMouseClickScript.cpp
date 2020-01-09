#include "SampleMouseClickScript.h"
#include "SampleActorScript.h"
#include "DrawSprite.h"
#include "ActionEngine.h"

#include "InputManager.h"


void SampleActorMouseClick::onStart(Actor * current, float dt)
{
	nextFunction = static_cast<void(ScriptInterface::*)(Actor *current, float dt)>(&SampleActorMouseClick::onTick);
	EventManager::Instance()->bindEvent("click to spawn", eventParameterTypes::INT2,std::bind(&SampleActorMouseClick::mouseClickTest,this, std::placeholders::_1));
	onTick(current, dt);
}

void SampleActorMouseClick::mouseClickTest(eventData data)
{
	v2 spawnCoordinates(data.int2.i1, data.int2.i2);
	Actor* temp = new Actor("scrolling rock");
	temp->addComponent("transform", new DataInterface<v2>(spawnCoordinates));
	temp->addComponent("testImage", new DrawSprite(drawObject(1, v2(0, 0)), 1));
	temp->addComponent("testScrolling", new SampleActorScript());
	ActionEngine::Instance()->addActor(temp);
}


void SampleActorMouseClick::onTick(Actor * current, float dt)
{
}
