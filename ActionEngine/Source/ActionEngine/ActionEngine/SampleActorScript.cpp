#include "SampleActorScript.h"



SampleActorScript::SampleActorScript()
{
}


SampleActorScript::~SampleActorScript()
{
}

void SampleActorScript::tick(Actor * current, float dt)
{
	if(!actorTransform)
		actorTransform = ((DataInterface<v2>*)current->components["transform"]);
	actorTransform->setData(actorTransform->getData()+(v2(20,20)*dt));
}
