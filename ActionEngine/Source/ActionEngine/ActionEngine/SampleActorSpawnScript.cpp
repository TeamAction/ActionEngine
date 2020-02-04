#include "SampleActorSpawnScript.h"
#include "SampleActorScript.h"
#include "DrawSprite.h"
#include "ActionEngine.h"
#include "EventManager.h"


void SampleActorSpawnScript::onStart(float dt)
{
	actorTransform = static_cast<DataInterface<v2>*>(owner->getComponent("transform"));
	nextFunction = static_cast<void(ScriptInterface::*)(float dt)>(&SampleActorSpawnScript::onTick);
	test = EventManager<>::Instance()->bindEvent("spaceKey",std::bind(&SampleActorSpawnScript::spaceBarTest, this));
	startPosition = actorTransform->getData();
	onTick(dt);
}

void SampleActorSpawnScript::spaceBarTest()
{
	Actor* temp = new Actor("scrolling rock",owner);
	temp->addComponent("testImage", new DrawSprite(drawObject(1, v2(0, 0),v2(0,0)), 1));
	//temp->addComponent("testScrolling", new SampleActorScript());
}



void SampleActorSpawnScript::onTick(float dt)
{
	timer += dt;
	actorTransform->setData(startPosition+v2(0,100*sin(timer)));
}




