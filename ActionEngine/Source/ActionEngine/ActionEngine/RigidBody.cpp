#pragma once
#include "RigidBody.h"
#include "DataInterface.h"
#include "PhysicsSystem.h"

void RigidBody::AddForce(v2 force)
{
    totalForces =  totalForces + force;
}

void RigidBody::Stop()
{
    currentVelocity = v2();
    totalForces = v2();
}

v2 RigidBody::getCenter()
{
    v2 transform = actorTransform->getData();
    return v2(transform.x + (size.x / 2), transform.y + (size.y / 2));
}

void RigidBody::setCenter(v2 cen)
{
    actorTransform->setData(v2(cen.x - (size.x / 2), cen.y - (size.y / 2)));
}

void RigidBody::onUpdate(float dt)
{
    dt = 0.016;
    if (mass == 0)
    {
        PhysicsSystem::Instance()->rigidBodies.push_back(this);
        return;
    }
    v2 acceleration =  v2();
    if (obeysGravity && !grounded) {
        acceleration = gravity;
    }
    else {
        if (abs(currentVelocity.y) < 25.0f) currentVelocity.y = 0;
    }

    acceleration = acceleration + totalForces * (1/mass);

    currentVelocity = currentVelocity + acceleration * dt;
    currentVelocity.x = currentVelocity.x * 0.9;
    if (abs(currentVelocity.x) < 1.0f)
        currentVelocity.x = 0;

    v2 temp = actorTransform->getData();
    temp = temp + currentVelocity * dt;
    actorTransform->setData(temp);
    SetAABB();

    totalForces = v2();
    PhysicsSystem::Instance()->rigidBodies.push_back(this);
}

void RigidBody::onStart(float dt)
{
    nextFunction = static_cast<void(RigidBody::*)(float dt)>(&RigidBody::onUpdate);
    actorTransform = static_cast<DataInterface<v2>*>(owner->getComponent("transform"));
    SetAABB();
    onUpdate(dt);
}

void RigidBody::SetAABB()
{
    v2 transform = actorTransform->getData();
    aabb.bLeft = v2(transform.x, transform.y + size.y);
    aabb.tRight = v2(transform.x + size.x, transform.y );
}