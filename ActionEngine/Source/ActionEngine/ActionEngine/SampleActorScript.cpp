#include "SampleActorScript.h"



void SampleActorScript::onStart(Actor * current, float dt)
{
	actorTransform = static_cast<DataInterface<v2>*>(current->getComponent("transform"));
	nextFunction = static_cast<void(ScriptInterface::*)(Actor *current, float dt)>(&SampleActorScript::onTick);
	onTick(current, dt);
}



void SampleActorScript::onTick(Actor * current, float dt)
{
	actorTransform->setData(actorTransform->getData()+(v2(100,0)*dt));
	if (actorTransform->getData().x > 640)
		current->killActor();
}
