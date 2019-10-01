#include "Actor.h"

void Actor::tick()
{
	for (int i = 0; i < components.size();i++)
	{
		components[i].tick();
	}
}
