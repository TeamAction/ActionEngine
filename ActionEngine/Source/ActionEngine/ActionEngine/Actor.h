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
	void tick(std::vector<std::vector<drawObject>> &bmp,float dt);
	void addComponent(std::string name, ActorComponent* component);
	std::unordered_map<std::string, ActorComponent*> components;
};