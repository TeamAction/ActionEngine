#include "Actor.h"
#include "ActiveInterface.h"
#include "DrawInterface.h"


Actor::~Actor()
{
	for (int i = 0; i < components.size(); i++)
	{
		delete components[i];
		components[i] = nullptr;
	}
}

void Actor::tick(std::unordered_map<int, std::vector<drawObject>> &bmp,float dt)
{
	for (int i = 0; i < components.size(); i++)
	{
		switch (components[i]->objectType)
		{
		case TICK:
			((ActiveInterface*)components[i])->tick(this, dt);
			break;
		case DRAW:
			bmp[((DrawInterface*)components[i])->getLayer()].push_back(((DrawInterface*)components[i])->getObject());
			break;
		default:
			break;
		}
	}
}

void Actor::addComponent(ActorComponent * component)
{
	components.push_back(component);
}
