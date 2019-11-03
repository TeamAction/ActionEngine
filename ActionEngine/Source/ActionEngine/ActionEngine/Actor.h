#pragma once
#include <vector>
#include <unordered_map>

struct drawObject;
struct v2;
class ActorComponent;

class Actor
{
public:
	Actor(v2);
	~Actor();
	void addComponent(std::string name, ActorComponent* component);
	void killActor();
	bool actorToBeRemoved();
	void tick(std::vector<std::vector<drawObject>> &bmp, float dt);
	std::unordered_map<std::string, ActorComponent*> components;
private :
	bool toBeRemoved = false;
};