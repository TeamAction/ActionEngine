#include "SampleActorScript.h"



SampleActorScript::SampleActorScript()
{
}


SampleActorScript::~SampleActorScript()
{
}

void SampleActorScript::tick(Actor * current, float dt)
{
	((DataInterface<v2>*)current->components[TRANSFORM])->setData(((DataInterface<v2>*)current->components[TRANSFORM])->getData()+(v2(20,20)*dt));
}
