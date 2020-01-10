#include "Actor.h"
#include "ScriptInterface.h"
#include "DrawInterface.h"
#include "DataInterface.h"
#include "tigr.h"

Actor::Actor(std::string _actorName, Actor* _parent) : actorName(_actorName)
{
	parent = _parent;
	if(_parent != nullptr)
		parent->addChild(this);
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
	int i = 0;
}

void Actor::tick(float dt)
{
	tickComponents(dt);
	for(int i = 0; i < children.size(); i++)
	{
		children[i]->tick(dt);
	}
}

ActorComponent * Actor::getComponent(std::string name)
{
	if(components.count(name))
		return components[name];
	char output[256];
	sprintf_s(output, "Requested Component \"%s\" not found on actor \"%s\"",name.c_str() , actorName.c_str());
	tigrError(nullptr,output);
}

int Actor::numberOfChildren()
{
	int count = 0;
	for (int i = 0; i < children.size(); i++)
	{
		count++;
		count += children[i]->numberOfChildren();
	}
	return count;
}

v2 Actor::getGlobalTransform()
{
	if (parent == nullptr)
		return static_cast<DataInterface<v2>*>(getComponent("transform"))->getData();
	return static_cast<DataInterface<v2>*>(getComponent("transform"))->getData()+parent->getGlobalTransform();
}

void Actor::updateComponents(float dt)
{
	std::unordered_map<std::string, ActorComponent*>::iterator it = components.begin();
	actorName;
	while (it != components.end())
	{
		switch (it->second->objectType)
		{
		case TYPE::TICK:
			static_cast<ScriptInterface*>(it->second)->tick(dt);
			break;
		case TYPE::DRAW:
			static_cast<DrawInterface*>(it->second)->addObject(dt);
			break;
		default:
			break;
		}
		it++;
	}
}

void Actor::createTransform(float dt)
{
	if (!components.count("transform"))
	{
		addComponent("transform", new DataInterface<v2>(v2(0,0)));
	}
	nextFunction = &Actor::updateComponents;
	tickComponents(dt);
}

void Actor::addComponent(std::string name,ActorComponent * component)
{
	if (components.count(name))
	{
		char output[256];
		sprintf_s(output, "Error compent of name \"%s\" already exists", name.c_str());
		tigrError(nullptr, output);
	}
	component->SetOwner(this);
	components.insert({ name, component });
}

void Actor::addChild(Actor* child)
{
	children.push_back(child);
}

void Actor::flagActorForRemoval()
{
	toBeRemoved = true;
	for(int i =0;i<children.size();i++)
	{
		children[i]->flagActorForRemoval();
	}
}

void Actor::removeFlaggedActors()
{
	for (int i = 0; i < children.size(); i++)
	{
		children[i]->removeFlaggedActors();
		if (children[i]->flagStatus() == true)
		{
			delete children[i];
			children.erase(children.begin() + i);
		}
	}
}

bool Actor::flagStatus()
{
	return toBeRemoved;
}
