#include "Actor.h"
#include "ScriptInterface.h"
#include "DrawInterface.h"
#include "DataInterface.h"
#include "Renderer.h"
#include "RigidBody.h"

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
}

void Actor::tick(float dt)
{
	tickComponents(dt);
	for(int i = 0; i < children.size(); i++)
	{
		children[i]->tick(dt);
	}
}

ActorComponent* Actor::getComponent(std::string name)
{
	if(components.count(name))
		return components[name];
	char output[256];
	sprintf_s(output, "Requested Component \"%s\" not found on actor \"%s\"",name.c_str() , actorName.c_str());
	Renderer::Instance()->ErrorPopup(output);
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
	if (!parent)
		return transform->getData();
	return transform->getData()+parent->getGlobalTransform();
}

void Actor::setGlobalTransform(v2 newTransform)
{
	v2 currentTransform = transform->getData();
	if (!parent)
	{
		transform->setData(newTransform);
		return;
	}
	transform->setData(newTransform - parent->getGlobalTransform());
}

v2 Actor::getLocalTransform()
{
	return transform->getData();
}

void Actor::setLocalTransform(v2 newTransform)
{
	transform->setData(newTransform);
}

void Actor::addForce(v2 force)
{
	if (!rigidBody)
	{
		char output[256];
		sprintf_s(output, "%s does not have a rigid body add one to use forces", actorName.c_str());
		Renderer::Instance()->ErrorPopup(output);
		return;
	}
	rigidBody->AddForce(force);
}

v2 Actor::getVelocity()
{
	return rigidBody->currentVelocity;
}

bool Actor::isGrounded()
{
	if (!rigidBody)
	{
		char output[256];
		sprintf_s(output, "%s does not have a rigid body add one to check if grounded", actorName.c_str());
		Renderer::Instance()->ErrorPopup(output);
		return false;
	}
	return rigidBody->grounded;
}

ActorComponent* Actor::getSprite(std::string name)
{
	ActorComponent* comp = getComponent(name);
	if (static_cast<DrawInterface*>(comp) != nullptr)
		return comp;
	char output[256];
	sprintf_s(output, "Error compent of name \"%s\" is not a sprite", name.c_str());
	Renderer::Instance()->ErrorPopup(output);
	return nullptr;
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
		case TYPE::RIGIDBODY:
			static_cast<RigidBody*>(it->second)->updatePhysics(dt);
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
	transform = static_cast<DataInterface<v2>*>(getComponent("transform"));
	nextFunction = &Actor::updateComponents;
}

void Actor::addComponent(std::string name,ActorComponent * component)
{
	if (components.count(name))
	{
		char output[256];
		sprintf_s(output, "Error compent of name \"%s\" already exists", name.c_str());
		Renderer::Instance()->ErrorPopup(output);
	}
	component->SetOwner(this);
	components.insert({ name, component });
	if (component->objectType == TYPE::RIGIDBODY)
	{
		if (rigidBody)
		{
			char output[256];
			sprintf_s(output, "%s already has a rigid body only one per actor", actorName.c_str());
			Renderer::Instance()->ErrorPopup(output);
		}
		rigidBody = static_cast<RigidBody*>(component);
	}if (component->objectType == TYPE::DATA && name == "transform")
	{
		if (transform)
		{
			char output[256];
			sprintf_s(output, "%s already has a transform only one per actor", actorName.c_str());
			Renderer::Instance()->ErrorPopup(output);
		}
		transform = static_cast<DataInterface<v2>*>(component);
	}
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
	if (preserveInTransition)
		return;
	for (int i = 0; i < children.size(); i++)
	{
		children[i]->removeFlaggedActors();
	}
	if (flagStatus())
	{
		if (parent != nullptr)
		{
			ActionEngine::Instance()->actorMap.erase(actorName);
			parent->children.erase(std::remove(parent->children.begin(), parent->children.end(), this), parent->children.end());
		}
		delete this;
	}
}

void Actor::recoverPreservedActors(std::vector<Actor*>& actorList)
{
	for (int i = 0; i < children.size(); i++)
	{
		children[i]->recoverPreservedActors(actorList);
	}
	if (preserveInTransition)
		actorList.push_back(this);
}

bool Actor::flagStatus()
{
	return toBeRemoved;
}
