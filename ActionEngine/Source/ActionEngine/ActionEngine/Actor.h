#pragma once
#include "ComponentInterface.h"
#include "helper.h"
#include <vector>
#include <unordered_map>

class Actor
{
public:
	Actor(v2, std::vector<drawObject>);
	~Actor();
	void tick(std::unordered_map<int, std::vector<drawObject>> &bmp,float dt);
private:
		std::vector<ComponentInterface*> components;
		std::vector<drawObject> spriteObjects; // all sprites drawable by this actor
		std::vector<drawObject> drawObjects; // what should be drawn this frame by this actor
		int drawlayer;
		v2 transform;
};