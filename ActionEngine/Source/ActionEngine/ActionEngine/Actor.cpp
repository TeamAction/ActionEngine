#include "Actor.h"

Actor::Actor(v2 _transform, std::vector<drawObject> _spriteObjects): transform(_transform), spriteObjects(_spriteObjects)
{
}

Actor::~Actor()
{
	for (int i = 0; i < components.size(); i++)
	{
		delete components[i];
		components[i] = nullptr;
	}
}

void Actor::tick(std::unordered_map<int, std::vector<drawObject>> &bmp,float dt)
{
	drawObjects.clear();
	//drawObjects.push_back(spriteObjects[0]);
	for (int i = 0; i < components.size(); i++)
	{
		components[i]->tick(this,dt);
	}
	for (int i = 0; i < drawObjects.size(); i++)
	{
		bmp[drawlayer].push_back(drawObjects[i]);
	}
}
