#ifndef ANDORA_PHYSICS_H
#define ANDORA_PHYSICS_H

#include "raylib.h"

#define min(a,b) a > b ? b : a
#define max(a,b) a > b ? a : b

typedef struct {
	Vector2 min;
	Vector2 max;
} AABB;

typedef struct {
	Vector2 position;
	Vector2 velocity;
	float restitution;
	float mass;
	float invMass;
	AABB aabb;
} PObject;

typedef struct {
	PObject *A;
	PObject *B;
	float penetration;
	Vector2 normal;
} Manifold;

#endif //ANDORA_PHYSICS_H
