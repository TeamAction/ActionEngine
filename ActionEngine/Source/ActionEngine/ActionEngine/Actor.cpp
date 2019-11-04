#include "Actor.h"
#include "ScriptInterface.h"
#include "DrawInterface.h"
#include "DataInterface.h"


#include "tigr.h"

Actor::Actor()
{}

Actor::~Actor()
{
	std::unordered_map<std::string, ActorComponent*>::iterator it = components.begin();
	while (it != components.end())
	{
		delete it->second;
		it->second = nullptr;
		it++;
	}
	int i = 0;
}

void Actor::tick(std::vector<std::vector<drawObject>> &bmp,float dt)
{
	std::unordered_map<std::string, ActorComponent*>::iterator it = components.begin();
	while (it != components.end())
	{
		switch (it->second->objectType)
		{
		case TICK:
			static_cast<ScriptInterface*>(it->second)->tick(this, dt);
			break;
		case DRAW:
			((DrawInterface*)it->second)->addObject(this, dt);
			break;
		default:
			break;
		}
		it++;
	}
}

ActorComponent * Actor::getComponent(std::string name)
{
	ActorComponent* requested = components[name];
	if (!requested)
		tigrError(nullptr,"Requested Component not found");
	return requested;
}

void Actor::addComponent(std::string name,ActorComponent * component)
{
	components.insert({ name, component });
}

void Actor::killActor()
{
	toBeRemoved = true;
}

bool Actor::actorToBeRemoved()
{
	return toBeRemoved;
}