// TODO(noituri): CLEAN UP

#include "physics.h"
#include "raymath.h"
#include <stdio.h>
#include <math.h>

#ifdef WIN32
#include <Windows.h>
LARGE_INTEGER cpu_freq;
#else
#include <time.h>
#endif

const float fps = 60;
const float dt = 1 / fps;
const Vector2 gravity = { 0.0f, -5.0f };
Clock time_start;

Manifold collision_pairs[1000];
Body *bodies[1000];
int bodies_count, pairs_count = 0;

void GetPhysicsTime(Clock *t)
{
#ifdef WIN32
    QueryPerformanceCounter(t);
#else
    clock_gettime(CLOCK_MONOTONIC, t);
#endif
}

void InitPhysics()
{
    GetPhysicsTime(&time_start);
#ifdef WIN32
    QueryPerformanceFrequency(&cpu_freq);
#endif
}

int AddBody(Body *b)
{
    if (b->mass == 0)
        b->inv_mass = 0;
    else
        b->inv_mass = 1 / b->mass;
    
    int current_count = bodies_count;
    bodies[bodies_count++] = b;
    return current_count;
}

void RemoveBody(int body_index)
{
    bodies[body_index] = bodies[--bodies_count];
}

void PositionalCorrection(Manifold *m)
{
    Body *A = m->A;
    Body *B = m->B;
    
    const float percent = 0.2f;
    const float slop = 0.01f;
    float tmp = (max(m->penetration - slop, 0.0f) / (A->inv_mass + B->inv_mass)) * percent;
    Vector2 correction = Vector2Scale(m->normal, tmp);
    A->position = Vector2Subtract(A->position, Vector2Scale(correction, A->inv_mass));
    B->position = Vector2Add(B->position, Vector2Scale(correction, B->inv_mass));
}

void ResolveCollision(Manifold *m)
{
    Body *A = m->A;
    Body *B = m->B;
    
    Vector2 relative_v = Vector2Subtract(B->velocity, A->velocity);
    float vel_along_normal = Vector2DotProduct(relative_v, m->normal);
    if (vel_along_normal > 0)
        return;
    
    float e = min(A->restitution, B->restitution);
    float j = -(e + 1) * vel_along_normal;
    j /= A->inv_mass + B->inv_mass;
    
    Vector2 impulse = Vector2Scale(m->normal, j);
    A->velocity = Vector2Subtract(A->velocity, Vector2Scale(impulse, A->inv_mass));
    B->velocity = Vector2Add(B->velocity, Vector2Scale(impulse, B->inv_mass));
    
    relative_v = Vector2Subtract(B->velocity, A->velocity);
    Vector2 tmp_dot = Vector2Scale(m->normal, Vector2DotProduct(relative_v, m->normal));
    
    
    Vector2 tangent = Vector2Subtract(relative_v, tmp_dot);
    if (!Vector2Length(tangent))
        return;
    tangent = Vector2Normalize(tangent);
    
    float jt = -Vector2DotProduct(relative_v, tangent);
    jt /= A->inv_mass + B->inv_mass;
    
    float mu = pythagoreanSolve(A->static_friction, B->static_friction);
    
    Vector2 friction_impulse = {};
    if (fabsf(jt) < j * mu) {
        friction_impulse = Vector2Scale(tangent, jt);
    } else {
        float dynamic_friction = pythagoreanSolve(A->dynamic_friction, B->dynamic_friction);
        
        friction_impulse = Vector2Scale(tangent, -j * dynamic_friction);
    }
    
    A->velocity = Vector2Subtract(A->velocity, Vector2Scale(friction_impulse, A->inv_mass));
    B->velocity = Vector2Add(B->velocity, Vector2Scale(friction_impulse, B->inv_mass));
}

int AABBvsAABB(Manifold *m)
{
    Body *A = m->A;
    Body *B = m->B;
    AABB A_aabb = A->aabb;
    AABB B_aabb = B->aabb;
    
    Vector2 normal = Vector2Subtract(B->position, A->position);
    float a_extent = (A_aabb.max.x - A_aabb.min.x) / 2;
    float b_extent = (B_aabb.max.x - B_aabb.min.x) / 2;
    
    float x_overlap = a_extent + b_extent - fabsf(normal.x);
    if (x_overlap > 0) {
        float a_extent = (A_aabb.max.y - A_aabb.min.y) / 2;
        float b_extent = (B_aabb.max.y - B_aabb.min.y) / 2;
        
        float y_overlap = a_extent + b_extent - fabsf(normal.y);
        if (y_overlap > 0) {
            if (x_overlap < y_overlap) {
                if (normal.x < 0)
                    m->normal = (Vector2) {-1, 0};
                else
                    m->normal = Vector2Zero();
                m->penetration = x_overlap;
            } else {
                if (normal.y < 0)
                    m->normal = (Vector2) {0, -1};
                else
                    m->normal = (Vector2) {0, 1};
                m->penetration = y_overlap;
            }
            
            return 1;
        }
    }
    
    return 0;
}

void IntegrateForces(Body *b)
{
    Vector2 tmp = gravity;
    tmp.y += b->inv_mass;
    b->velocity = Vector2Add(b->velocity, Vector2Scale(tmp, dt / 2));
}

void IntegrateVelocity(Body *b)
{
    if (!b->dynamic)
        return;
    
    b->position = Vector2Add(b->position, Vector2Scale(b->velocity, dt));
    IntegrateForces(b);
}

float TimeElapsed()
{
    Clock current;
    GetPhysicsTime(&current);
#ifdef WIN32
    return (current.QuadPart - time_start.QuadPart) / (float) cpu_freq.QuadPart;
#else
    return (current.tv_sec - time_start.tv_sec) * 1e6 + (current.tv_nsec - time_start.tv_nsec) / 1e3;
#endif
}

void PhysicsStep()
{
    float accumulator = TimeElapsed();
    if (accumulator > 0.2f)
        accumulator = 0.2f;
    
    while (accumulator > dt) {
        GenerateContactPairs();
        for (int i = 0; i < bodies_count; i++)
            IntegrateVelocity(bodies[i]);
        
        for (int i = 0; i < pairs_count; i++)
            ResolveCollision(&collision_pairs[i]);
        
        for (int i = 0; i < bodies_count; i++)
            IntegrateVelocity(bodies[i]);
        
        for (int i = 0; i < pairs_count; i++)
            PositionalCorrection(&collision_pairs[i]);
        
        accumulator -= dt * 2;
    }
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
    pairs_count = 0;
    
    AABB A_aabb;
    AABB B_aabb;
    
    for (int i = 0; i < bodies_count; i++) {
        Body *A = bodies[i];
        
        for (int j = i + 1; j < bodies_count; j++) {
            Body *B = bodies[j];
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
            
            if (AABBvsAABB(&manifold)) {
                collision_pairs[pairs_count++] = manifold;
            }
        }
    }
}