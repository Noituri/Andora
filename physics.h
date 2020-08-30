#ifndef ANDORA_PHYSICS_H
#define ANDORA_PHYSICS_H

#include "raylib.h"

#define min(a,b) a > b ? b : a
#define max(a,b) a > b ? a : b

void InitPhysics();
void GenerateContactPairs();

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
    Vector2 force;
    
	float restitution;
    float density;
    
	float mass;
	float invMass;
	
    int dynamic;
    
    AABB aabb;
} Body;

typedef struct {
    Body *A;
    Body *B;
	float penetration;
	Vector2 normal;
} Manifold;

#endif //ANDORA_PHYSICS_H
