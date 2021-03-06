#pragma once
#include <vector>
#include <utility>     
#include "helperStructs.h"


class RigidBody;
struct CollisionPair {
    RigidBody* rigidBodyA;
    RigidBody* rigidBodyB;
};

struct CollisionInfo {
    v2 collisionNormal;
    float penetration;
};


class PhysicsSystem
{
public:
	static PhysicsSystem* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new PhysicsSystem();
		}
		return s_pInstance;
	}

    void UpdatePhysics(float dt);

    std::vector<RigidBody*> rigidBodies;
private:
	static PhysicsSystem* s_pInstance;

    std::vector<std::pair<CollisionPair, CollisionInfo>> collisions;
    void PositionalCorrection(CollisionPair c, CollisionInfo i);
    void IsGrounded(RigidBody* r);
    void CheckCollisions();
    void ResolveCollisions(float dt);

	PhysicsSystem() {};
	~PhysicsSystem() {};
};