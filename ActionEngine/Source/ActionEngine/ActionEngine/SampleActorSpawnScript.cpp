#include "SampleActorSpawnScript.h"
#include "SampleActorScript.h"
#include "DrawSprite.h"
#include "ActionEngine.h"


void SampleActorSpawnScript::onStart(Actor * current, float dt)
{
	actorTransform = static_cast<DataInterface<v2>*>(current->getComponent("transform"));
	nextFunction = static_cast<void(ScriptInterface::*)(Actor *current, float dt)>(&SampleActorSpawnScript::onTick);
	ActionEngine::Instance()->getInputInterface()->bindEvent(' ', std::bind(&SampleActorSpawnScript::spaceBarTest, this));
	onTick(current, dt);
}

void SampleActorSpawnScript::spaceBarTest()
{
	Actor* temp = new Actor();
	temp->addComponent("transform", new DataInterface<v2>(actorTransform->getData()));
	temp->addComponent("testImage", new DrawSprite(drawObject(1, v2(0, 0)), 1));
	temp->addComponent("testScrolling", new SampleActorScript());
	ActionEngine::Instance()->addActor(temp);
}



void SampleActorSpawnScript::onTick(Actor * current, float dt)
{
	/*timer += dt;
	if (timer >= 1.0f)
	{
		Actor* temp = new Actor();
		temp->addComponent("transform", new DataInterface<v2>(actorTransform->getData()));
		temp->addComponent("testImage", new DrawSprite(drawObject(1, v2(0, 0)), 0));
		temp->addComponent("testScrolling", new SampleActorScript());
		ActionEngine::Instance()->addActor(temp);
		timer = 0;
	}*/
}




