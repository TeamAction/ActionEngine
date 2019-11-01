#include "SampleActorScript.h"



SampleActorScript::SampleActorScript(Actor * current)
{
	actorTransform = ((DataInterface<v2>*)current->components["transform"]);
}


SampleActorScript::~SampleActorScript()
{
}

void SampleActorScript::tick(Actor * current, float dt)
{
	actorTransform->setData(actorTransform->getData()+(v2(100,100)*dt));
	if (actorTransform->getData().y > 720)
		current->killActor();
 }
