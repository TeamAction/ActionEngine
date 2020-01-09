#pragma once
#include <vector>
#include <unordered_map>

struct drawObject;
class ActorComponent;

class Actor
{
public:
	Actor(std::string _actorName);
	~Actor();
	std::string actorName;
	void addComponent(std::string name, ActorComponent* component);
	void killActor();
	bool actorToBeRemoved();
	void tick(float dt);
	ActorComponent* getComponent(std::string name);
private :
	std::unordered_map<std::string, ActorComponent*> components;
	bool toBeRemoved = false;
};