#pragma once
#include <vector>
#include <unordered_map>

struct drawObject;
class ActorComponent;
struct v2;
template < typename T > class DataInterface;

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
	DataInterface<v2>* transform = nullptr; //this is used very often so i am including this to reduce time spent fetching it
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