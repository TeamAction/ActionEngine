#include "SampleMouseClickScript.h"
#include "SampleActorScript.h"
#include "DrawSprite.h"
#include "ActionEngine.h"


void SampleActorMouseClick::onStart(Actor * current, float dt)
{
	nextFunction = static_cast<void(ScriptInterface::*)(Actor *current, float dt)>(&SampleActorMouseClick::onTick);
	ActionEngine::Instance()->getInputInterface()->bindEvent(LEFTMOUSEBUTTON, std::bind(&SampleActorMouseClick::mouseClickTest, this, std::ref(ActionEngine::Instance()->getInputInterface()->mouseX), std::ref(ActionEngine::Instance()->getInputInterface()->mouseY)));
	onTick(current, dt);
}

void SampleActorMouseClick::mouseClickTest(int mouseX,int mouseY)
{
	v2 spawnCoordinates(mouseX,mouseY);
	Actor* temp = new Actor();
	temp->addComponent("transform", new DataInterface<v2>(spawnCoordinates));
	temp->addComponent("testImage", new DrawSprite(drawObject(1, v2(0, 0)), 1));
	temp->addComponent("testScrolling", new SampleActorScript());
	ActionEngine::Instance()->addActor(temp);
}


void SampleActorMouseClick::onTick(Actor * current, float dt)
{
}
