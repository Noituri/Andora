#ifndef ANDORA_PHYSICS_H
#define ANDORA_PHYSICS_H

#include "raylib.h"

#define MIN(a,b) a > b ? b : a
#define MAX(a,b) a > b ? a : b
#define P_SOLVE(a,b) sqrtf(a*a + b*b)

typedef struct {
	Vector2 min;
	Vector2 max;
} AABB;

typedef struct {
    int layer;
    
    float width;
    float height;
	Vector2 position;
	Vector2 velocity;

    float static_friction;
    float dynamic_friction;
	float restitution;

	float mass;
	float inv_mass;
	
    int dynamic;
    
    AABB aabb;
} Body;

typedef struct {
    Body *A;
    Body *B;
	float penetration;
	Vector2 normal;
} Manifold;

void InitPhysics();
int AddBody(Body *newBody);
void RemoveBody(int i);
Body **GetBodies(int* amount);
void FreePhysics();
Body *CreateBody(Vector2 p, float w, float h, float m);
void GenerateContactPairs();
void PhysicsStep();

#endif //ANDORA_PHYSICS_H
