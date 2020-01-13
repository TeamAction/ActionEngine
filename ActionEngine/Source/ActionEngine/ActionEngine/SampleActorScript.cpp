#include "SampleActorScript.h"
#include <iostream>

void SampleActorScript::onStart(float dt)
{
	actorTransform = static_cast<DataInterface<v2>*>(owner->getComponent("transform"));
	nextFunction = static_cast<void(ScriptInterface::*)(float dt)>(&SampleActorScript::onTick);
	onTick(dt);
}



void SampleActorScript::onTick(float dt)
{
	actorTransform->setData(actorTransform->getData()+(v2(100,0)*dt));
	if (actorTransform->getData().x > 640)
		owner->flagActorForRemoval();
}
