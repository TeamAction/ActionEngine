#pragma once
#include "PhysicsSystem.h"
#include "RigidBody.h"
#include "DataInterface.h"



PhysicsSystem* PhysicsSystem::s_pInstance = 0;
void PhysicsSystem::UpdatePhysics(float dt)
{
    if (rigidBodies.size() == 0)
        return;
    CheckCollisions();
    ResolveCollisions(dt);
    IsGrounded();
    rigidBodies.clear();
    collisions.clear();
}

void PhysicsSystem::PositionalCorrection(CollisionPair c, CollisionInfo i)
{
    float invMassA, invMassB;
    if (c.rigidBodyA->mass == 0)
        invMassA = 0;
    else
        invMassA = 1 / c.rigidBodyA->mass;

    if (c.rigidBodyB->mass == 0)
        invMassB = 0;
    else
        invMassB = 1 / c.rigidBodyB->mass;
    v2 correction = ((i.penetration / (invMassA + invMassB)) * 1.0f) * i.collisionNormal;

    v2 temp = c.rigidBodyA->getCenter();
    temp = temp + (invMassA * correction);
    c.rigidBodyA->setCenter(temp);

    temp = c.rigidBodyB->getCenter();
    temp = temp - (invMassB * correction);
    c.rigidBodyB->setCenter(temp);

}

void PhysicsSystem::IsGrounded()
{
    for (int i = 0; i < rigidBodies.size();i++) {
        rigidBodies[i]->grounded = false;
        for (int q = 0; q < rigidBodies.size(); q++) {
            if (i != q) {
                if (rigidBodies[i]->aabb.bLeft.x < rigidBodies[q]->aabb.tRight.x
                    && rigidBodies[i]->aabb.tRight.x > rigidBodies[q]->aabb.bLeft.x
                    && abs(rigidBodies[q]->aabb.tRight.y - rigidBodies[i]->aabb.bLeft.y) <= 1.0f) {
                    if (abs(rigidBodies[i]->currentVelocity.y) < 10.0f)
                        rigidBodies[i]->grounded = true;
                }
            }
        }
    }
}



void PhysicsSystem::CheckCollisions()
{
    for (int i = 0; i < rigidBodies.size()-1;i++) {
        for (int q = i+1; q < rigidBodies.size(); q++) {
            if (q != i) {
                CollisionPair pair;
                CollisionInfo colInfo;
                pair.rigidBodyA = rigidBodies[i]; pair.rigidBodyB = rigidBodies[q];

                v2 distance = rigidBodies[q]->getCenter() - rigidBodies[i]->getCenter();

                v2 halfSizeA = abs(rigidBodies[i]->aabb.tRight - rigidBodies[i]->aabb.bLeft) / 2;
                v2 halfSizeB = abs(rigidBodies[q]->aabb.tRight - rigidBodies[q]->aabb.bLeft) / 2;
                abs(halfSizeB);

                v2 gap =  v2(abs(distance.x), abs(distance.y)) - (halfSizeA + halfSizeB);

                if (gap.x < 0 && gap.y < 0) {

                    if (gap.x > gap.y) {
                        if (distance.x > 0) {
                            colInfo.collisionNormal = v2(1, 0);
                        }
                        else {
                            colInfo.collisionNormal = v2(-1, 0);
                        }
                        colInfo.penetration = gap.x;
                    }
                    else {
                        if (distance.y > 0) {
                            colInfo.collisionNormal = v2(0, 1);
                        }
                        else
                        {
                            colInfo.collisionNormal = v2(0, -1);
                        }
                        colInfo.penetration = gap.y;
                    }
                    collisions.push_back({pair, colInfo});
                }

            }
        }
    }
}

void PhysicsSystem::ResolveCollisions(float dt)
{
    for (int i = 0; i < collisions.size();i++) {
        float minBounce = std::fmin(collisions[i].first.rigidBodyA->bounciness, collisions[i].first.rigidBodyB->bounciness);
        float velAlongNormal = dot(collisions[i].first.rigidBodyB->currentVelocity - collisions[i].first.rigidBodyA->currentVelocity, collisions[i].second.collisionNormal);
        if (velAlongNormal > 0) continue;

        float j = -(1 + minBounce) * velAlongNormal;
        float invMassA, invMassB;
        if (collisions[i].first.rigidBodyA->mass == 0)
            invMassA = 0;
        else
            invMassA = 1 / collisions[i].first.rigidBodyA->mass;

        if (collisions[i].first.rigidBodyB->mass == 0)
            invMassB = 0;
        else
            invMassB = 1 / collisions[i].first.rigidBodyB->mass;

        j /= invMassA + invMassB;

        v2 impulse = collisions[i].second.collisionNormal*j;

        collisions[i].first.rigidBodyA->AddForce((impulse * -1) / dt);
        collisions[i].first.rigidBodyB->AddForce(impulse/ dt);

        if (abs(collisions[i].second.penetration) > 0.01) {
            PositionalCorrection(collisions[i].first, collisions[i].second);
        }
    }
}
