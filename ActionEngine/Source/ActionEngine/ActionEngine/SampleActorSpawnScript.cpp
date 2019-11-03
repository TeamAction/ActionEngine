#include "SampleActorSpawnScript.h"
#include "SampleActorScript.h"
#include "DrawSprite.h"
#include "ActionEngine.h"



void SampleActorSpawnScript::onStart(Actor * current, float dt)
{
	actorTransform = ((DataInterface<v2>*)current->components["transform"]);
	nextFunction = reinterpret_cast<void(ScriptInterface::*)(Actor *current, float dt)>(&SampleActorSpawnScript::onTick);
	onTick(current, dt);
}



void SampleActorSpawnScript::onTick(Actor * current, float dt)
{
	timer += dt;
	if (timer >= 1.0f)
	{
		Actor* temp = new Actor(actorTransform->getData());
		temp->addComponent("testImage", new DrawSprite(drawObject(0, v2(0, 0), true), 0));
		temp->addComponent("testScrolling", new SampleActorScript());
		ActionEngine::Instance()->addActor(temp);
		timer = 0;
	}
}
