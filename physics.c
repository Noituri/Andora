#include "physics.h"
#include "raymath.h"
#include <time.h>
#include <stdio.h>
#include <math.h>

const float fps = 60;
const float dt = 1 / 60;
float accumulator = 0.0f;
time_t timeStart;

Manifold collisionPairs[1000];
Body bodies[1000];
int bodiesCount, pairsCount = 0;

void InitPhysics()
{
    timeStart = time(NULL);
}

int AddBody(Body newBody)
{
    int currentBodiesCount = bodiesCount;
    bodies[bodiesCount++] = newBody;
    return currentBodiesCount;
}

void RemoveBody(int bodyIndex)
{
    bodies[bodyIndex] = bodies[bodiesCount-1];
    bodiesCount--;
}

void positionalCorrection(Manifold *m)
{
    Body *A = m->A;
    Body *B = m->B;
    
    const float percent = 0.2f;
    const float slop = 0.01f;
    float tmp = (max(m->penetration - slop, 0.0f) / (A->invMass + B->invMass)) * percent;
    Vector2 correction = Vector2Scale(m->normal, tmp);
    A->position = Vector2Subtract(A->position, Vector2Scale(correction, A->invMass));
    B->position = Vector2Add(B->position, Vector2Scale(correction, B->invMass));
}

void ResolveCollision(Manifold *m)
{
    Body *A = m->A;
    Body *B = m->B;
    
    Vector2 relativeV = Vector2Subtract(B->velocity, A->velocity);
    float velAlongNormal = Vector2DotProduct(relativeV, m->normal);
    if (velAlongNormal > 0)
        return;
    
    if(A->mass == 0)
        A->invMass = 0;
    else
        A->invMass = 1 / A->mass;
    
    if(B->mass == 0)
        B->invMass = 0;
    else
        B->invMass = 1 / B->mass;
    
    float e = min(A->restitution, B->restitution);
    float j = -(e + 1) * velAlongNormal;
    
    j /= 1 / A->mass + 1 / B->mass;
    
    Vector2 impulse = Vector2Scale(m->normal, j);
    float massSum = A->mass + B->mass;
    
    float ratio = A->mass / massSum;
    A->velocity = Vector2Subtract(A->velocity, Vector2Scale(impulse, ratio));
    
    ratio = B->mass / massSum;
    B->velocity = Vector2Add(B->velocity, Vector2Scale(impulse, ratio));
    
    relativeV = Vector2Subtract(B->velocity, A->velocity);
    Vector2 tmpDot = Vector2Scale(m->normal, Vector2DotProduct(relativeV, m->normal));
    Vector2 tangent = Vector2Subtract(relativeV, tmpDot);
    tangent = Vector2Normalize(tangent);
    
    float jt = -Vector2DotProduct(relativeV, tangent);
    jt /= A->invMass + B->invMass;
    
    float mu = pythagoreanSolve(A->staticFriction, B->staticFriction);
    
    Vector2 frictionImpulse = {};
    if (fabsf(jt) < j * mu) {
        frictionImpulse = Vector2Scale(tangent, jt);
    } else {
        float dynamicFriction = pythagoreanSolve(A->dynamicFriction, B->dynamicFriction);
        frictionImpulse = Vector2Scale(tangent, -j * dynamicFriction);
    }
    
    A->velocity = Vector2Subtract(A->velocity, Vector2Scale(frictionImpulse, A->invMass));
    B->velocity = Vector2Add(B->velocity, Vector2Scale(frictionImpulse, B->invMass));
}

int AABBvsAABB(Manifold *m)
{
    Vector2 normal = Vector2Subtract(m->B->position, m->A->position);
    float aExtent = (m->A->aabb.max.x - m->A->aabb.min.x) / 2;
    float bExtent = (m->B->aabb.max.x - m->B->aabb.min.x) / 2;
    
    float xOverlap = aExtent + bExtent - fabsf(normal.x);
    if (xOverlap > 0) {
        float aExtent = (m->A->aabb.max.y - m->A->aabb.min.y) / 2;
        float bExtent = (m->B->aabb.max.y - m->B->aabb.min.y) / 2;
        
        float yOverlap = aExtent + bExtent - fabsf(normal.y);
        if (yOverlap > 0) {
            if (xOverlap > yOverlap) {
                if (normal.x < 0)
                    m->normal = (Vector2) {-1, 0};
                else
                    m->normal = Vector2Zero();
                m->penetration = xOverlap;
            } else {
                if (normal.y < 0)
                    m->normal = (Vector2) {0, -1};
                else
                    m->normal = (Vector2) {0, 1};
                m->penetration = yOverlap;
            }
            
            return 1;
        }
    }
    
    return 0;
}

void PhysicsStep()
{
    time_t currentTime = time(NULL);
    accumulator += currentTime - timeStart;
    timeStart = currentTime;
    
    if (accumulator > 0.2f)
        accumulator = 0.2f;
    
    while (accumulator > dt) {
        accumulator -= dt;
    }
    
    const float alpha = accumulator / dt;
}

AABB CalculateAABB(Body *b)
{
    // TODO: Check this implementation
    AABB tmp = {
        .min = b->position,
        .max = (Vector2) { b->position.x + b->width, b->position.y + b->height }
    };
    
    return tmp;
}

void GenerateContactPairs()
{
    AABB A_aabb;
    AABB B_aabb;
    printf("BODIES COUNT: %d\n", bodiesCount);
    
    for (int i = 0; i < bodiesCount; i++) {
        Body *A = &bodies[i];
        
        for (int j = i + 1; j < bodiesCount; j++) {
            Body *B = &bodies[j];
            if (!A->dynamic && !B->dynamic)
                continue;
            
            if (!(A->layer & B->layer))
                continue;
            
            A->aabb = CalculateAABB(A);
            B->aabb = CalculateAABB(B);
            
            Manifold manifold = {
                .A = A,
                .B = B
            };
            printf("TESTING AABBtoAABB\n");
            if (AABBvsAABB(&manifold)) {
                collisionPairs[pairsCount++] = manifold;
            }
        }
    }
}