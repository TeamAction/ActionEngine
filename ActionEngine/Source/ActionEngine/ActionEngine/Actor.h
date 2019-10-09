#pragma once
#include <vector>
#include <unordered_map>
#include "ActiveInterface.h"
#include "DrawInterface.h"
#include "DataInterface.h"

struct drawObject;
struct v2;
class ActorComponent;
enum COMPONENTNAMES;

class Actor
{
public:
	Actor(v2);
	~Actor();
	void tick(std::unordered_map<int, std::vector<drawObject>> &bmp,float dt);
	void addComponent(COMPONENTNAMES name, ActorComponent* component);
	std::unordered_map<COMPONENTNAMES, ActorComponent*> components;
};