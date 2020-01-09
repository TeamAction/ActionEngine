#include "Actor.h"
#include "ScriptInterface.h"
#include "DrawInterface.h"
#include "DataInterface.h"
#include "tigr.h"

Actor::Actor(std::string _actorName = "UNNAMED") : actorName(_actorName)
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

void Actor::tick(float dt)
{
	std::unordered_map<std::string, ActorComponent*>::iterator it = components.begin();
	while (it != components.end())
	{
		switch (it->second->objectType)
		{
		case TYPE::TICK:
			static_cast<ScriptInterface*>(it->second)->tick(this, dt);
			break;
		case TYPE::DRAW:
			static_cast<DrawInterface*>(it->second)->addObject(this, dt);
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
	{
		char output[256];
		sprintf_s(output, "Requested Component \"%s\" not found on actor \"%s\"",name.c_str() , actorName.c_str());
		tigrError(nullptr,output);
	}
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