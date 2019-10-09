#include "Actor.h"
#include "Transform.h"
#include "ActiveInterface.h"
#include "DrawInterface.h"
#include "DataInterface.h"


Actor::Actor(v2 _transform)
{
	addComponent("transform",new Transform(_transform));
}

Actor::~Actor()
{
	std::unordered_map<std::string, ActorComponent*>::iterator it = components.begin();
	while (it != components.end())
	{
		delete it->second;
		it->second = nullptr;
		it++;
	}
}

void Actor::tick(std::vector<std::vector<drawObject>> &bmp,float dt)
{
	std::unordered_map<std::string, ActorComponent*>::iterator it = components.begin();
	while (it != components.end())
	{
		switch (it->second->objectType)
		{
		case TICK:
			((ActiveInterface*)it->second)->tick(this, dt);
			break;
		case DRAW:
			bmp[((DrawInterface*)it->second)->getLayer(this, dt)].push_back(((DrawInterface*)it->second)->getObject(this, dt));
			break;
		default:
			break;
		}
		it++;
	}
}

void Actor::addComponent(std::string name,ActorComponent * component)
{
	components.insert({ name, component });
}
