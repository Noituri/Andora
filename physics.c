#include "physics.h"
#include "raymath.h"
#include <time.h>
#include <stdio.h>
#include <math.h>

const float fps = 60;
const float dt = 1 / 60;
float accumulator = 0.0f;
time_t time_start;

Manifold collision_pairs[1000];
Body bodies[1000];
int bodies_count, pairs_count = 0;

void InitPhysics()
{
    time_start = time(NULL);
}

int AddBody(Body new_body)
{
    int current_count = bodies_count;
    bodies[bodies_count++] = new_body;
    return current_count;
}

void RemoveBody(int body_index)
{
    bodies[body_index] = bodies[bodies_count-1];
    bodies_count--;
}

void positionalCorrection(Manifold *m)
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
    
    if(A->mass == 0)
        A->inv_mass = 0;
    else
        A->inv_mass = 1 / A->mass;
    
    if(B->mass == 0)
        B->inv_mass = 0;
    else
        B->inv_mass = 1 / B->mass;
    
    float e = min(A->restitution, B->restitution);
    float j = -(e + 1) * vel_along_normal;
    
    j /= 1 / A->mass + 1 / B->mass;
    
    Vector2 impulse = Vector2Scale(m->normal, j);
    float mass_sum = A->mass + B->mass;
    
    float ratio = A->mass / mass_sum;
    A->velocity = Vector2Subtract(A->velocity, Vector2Scale(impulse, ratio));
    
    ratio = B->mass / mass_sum;
    B->velocity = Vector2Add(B->velocity, Vector2Scale(impulse, ratio));
    
    relative_v = Vector2Subtract(B->velocity, A->velocity);
    Vector2 tmp_dot = Vector2Scale(m->normal, Vector2DotProduct(relative_v, m->normal));
    Vector2 tangent = Vector2Subtract(relative_v, tmp_dot);
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
    Vector2 normal = Vector2Subtract(m->B->position, m->A->position);
    float a_extent = (m->A->aabb.max.x - m->A->aabb.min.x) / 2;
    float b_extent = (m->B->aabb.max.x - m->B->aabb.min.x) / 2;
    
    float x_overlap = a_extent + b_extent - fabsf(normal.x);
    if (x_overlap > 0) {
        float a_extent = (m->A->aabb.max.y - m->A->aabb.min.y) / 2;
        float b_extent = (m->B->aabb.max.y - m->B->aabb.min.y) / 2;
        
        float y_overlap = a_extent + b_extent - fabsf(normal.y);
        if (y_overlap > 0) {
            if (x_overlap > y_overlap) {
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

void PhysicsStep()
{
    time_t current_time = time(NULL);
    accumulator += current_time - time_start;
    time_start = current_time;
    
    if (accumulator > 0.2f)
        accumulator = 0.2f;
    
    while (accumulator > dt) {
        accumulator -= dt;
    }
    
    const float alpha = accumulator / dt;
}

AABB calculateAABB(Body *b)
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
    printf("BODIES COUNT: %d\n", bodies_count);
    
    for (int i = 0; i < bodies_count; i++) {
        Body *A = &bodies[i];
        
        for (int j = i + 1; j < bodies_count; j++) {
            Body *B = &bodies[j];
            if (!A->dynamic && !B->dynamic)
                continue;
            
            if (!(A->layer & B->layer))
                continue;
            
            A->aabb = calculateAABB(A);
            B->aabb = calculateAABB(B);
            
            Manifold manifold = {
                .A = A,
                .B = B
            };
            printf("TESTING AABBtoAABB\n");
            if (AABBvsAABB(&manifold)) {
                collision_pairs[pairs_count++] = manifold;
            }
        }
    }
}