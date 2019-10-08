#pragma once
#include "ActorComponent.h"
#include <vector>
#include <unordered_map>

struct drawObject;
class Actor
{
public:
	~Actor();
	void tick(std::unordered_map<int, std::vector<drawObject>> &bmp,float dt);
	void addComponent(ActorComponent* component);
private:
		std::vector<ActorComponent*> components;
};