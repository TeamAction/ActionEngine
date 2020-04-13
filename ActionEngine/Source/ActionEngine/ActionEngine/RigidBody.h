#pragma once
#include "ActorComponent.h" 
#include "helperStructs.h"
#include "Actor.h"


class RigidBody : public ActorComponent
{
public:
	RigidBody(v2 _size = v2(32,32),float _mass = 1.0f,float _bounceiness = 0.2f, bool _gravity = true, v2 _maxVel = v2(100,100), bool _triggerOnly = false) : ActorComponent(TYPE::RIGIDBODY), 
		size(_size),mass(_mass), bounciness(_bounceiness), obeysGravity(_gravity), maxVelocity(_maxVel), triggerOnly(_triggerOnly){}
	void(RigidBody::* nextFunction)(float dt) = &RigidBody::onStart;
	inline void updatePhysics(float dt) { (this->*nextFunction)(dt); }


	float mass = 1.0f;                            
	float bounciness = 1;                       
	bool obeysGravity = true;                  
	v2 gravity =  v2(0, 160.1f);     
	v2 currentVelocity;                    
	v2 maxVelocity =  v2(10.0f, 10.0f); 
	bool grounded = false;
	AABB aabb;

    void AddForce(v2 force);
    void Stop();
	v2 getCenter();
	void setCenter(v2 cen);
	DataInterface<v2>* actorTransform = nullptr;

	bool triggerOnly = false;
protected:
	virtual void onUpdate(float dt);
	virtual void onStart(float dt);

	v2 totalForces = v2();
	v2 size;
	void SetAABB();
};

