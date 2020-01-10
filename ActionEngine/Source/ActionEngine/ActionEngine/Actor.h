#pragma once
#include <vector>
#include <unordered_map>

struct drawObject;
class ActorComponent;
struct v2;

class Actor
{
public:
	Actor(std::string _actorName, Actor* _parent);
	~Actor();
	std::string actorName;
	void addComponent(std::string name, ActorComponent* component);
	void flagActorForRemoval();
	void removeFlaggedActors();
	bool flagStatus();
	void tick(float dt);
	ActorComponent* getComponent(std::string name);
	int numberOfChildren();
	v2 getGlobalTransform();
private :
	inline void tickComponents(float dt) { (this->*nextFunction)(dt); }
	void(Actor::* nextFunction)(float dt) = &Actor::createTransform;
	void updateComponents(float dt);
	void createTransform(float dt);
	bool toBeRemoved = false;
	void addChild(Actor* child);
	Actor* parent;
	std::unordered_map<std::string, ActorComponent*> components;
	std::vector<Actor*> children;
};