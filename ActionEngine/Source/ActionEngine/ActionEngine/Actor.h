#pragma once
#include <vector>
#include <unordered_map>

struct drawObject;
class ActorComponent;

class Actor
{
public:
	Actor();
	~Actor();
	void addComponent(std::string name, ActorComponent* component);
	void killActor();
	bool actorToBeRemoved();
	void tick(float dt);
	ActorComponent* getComponent(std::string name);
private :
	std::unordered_map<std::string, ActorComponent*> components;
	bool toBeRemoved = false;
};