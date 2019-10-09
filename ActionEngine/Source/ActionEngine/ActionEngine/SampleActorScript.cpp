#include "SampleActorScript.h"



SampleActorScript::SampleActorScript()
{
}


SampleActorScript::~SampleActorScript()
{
}

void SampleActorScript::tick(Actor * current, float dt)
{
	DataInterface<v2> * transform = ((DataInterface<v2>*)current->components[TRANSFORM]);
	transform->setData(transform->getData()+(v2(20,20)*dt));
}
