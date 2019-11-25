#include "SampleMouseClickScript.h"
#include "SampleActorScript.h"
#include "DrawSprite.h"
#include "ActionEngine.h"


void SampleActorMouseClick::onStart(Actor * current, float dt)
{
	nextFunction = static_cast<void(ScriptInterface::*)(Actor *current, float dt)>(&SampleActorMouseClick::onTick);
	ActionEngine::Instance()->getInputInterface()->bindEvent(LEFTMOUSEBUTTON, std::bind(&SampleActorMouseClick::mouseClickTest, this));
	onTick(current, dt);
}

void SampleActorMouseClick::mouseClickTest()
{
	v2 spawnCoordinates(ActionEngine::Instance()->getInputInterface()->mouseX, ActionEngine::Instance()->getInputInterface()->mouseY);
	Actor* temp = new Actor();
	temp->addComponent("transform", new DataInterface<v2>(spawnCoordinates));
	temp->addComponent("testImage", new DrawSprite(drawObject(1, v2(0, 0)), 1));
	temp->addComponent("testScrolling", new SampleActorScript());
	ActionEngine::Instance()->addActor(temp);
}


void SampleActorMouseClick::onTick(Actor * current, float dt)
{
}
