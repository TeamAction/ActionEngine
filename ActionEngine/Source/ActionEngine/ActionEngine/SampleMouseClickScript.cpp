#include "SampleMouseClickScript.h"
#include "SampleActorScript.h"
#include "DrawSprite.h"
#include "ActionEngine.h"

#include "InputManager.h"


void SampleActorMouseClick::onStart(Actor * current, float dt)
{
	nextFunction = static_cast<void(ScriptInterface::*)(Actor *current, float dt)>(&SampleActorMouseClick::onTick);
	EventManager::Instance()->bindEvent("click to spawn", std::bind(&SampleActorMouseClick::mouseClickTest, this));
	onTick(current, dt);
}

void SampleActorMouseClick::mouseClickTest()
{
	v2 spawnCoordinates(InputManager::Instance()->getMouseX(), InputManager::Instance()->getMouseY());
	Actor* temp = new Actor();
	temp->addComponent("transform", new DataInterface<v2>(spawnCoordinates));
	temp->addComponent("testImage", new DrawSprite(drawObject(1, v2(0, 0)), 1));
	temp->addComponent("testScrolling", new SampleActorScript());
	ActionEngine::Instance()->addActor(temp);
}


void SampleActorMouseClick::onTick(Actor * current, float dt)
{
}
