#ifndef ANDORA_COMPONENTS_H
#define ANDORA_COMPONENTS_H

#include "raylib.h"
#include "third_party/ecs.h"
#include "physics.h"

typedef enum {
    COMPONENT_TRANSFORM,
    COMPONENT_SPRITE,
    COMPONENT_TERRAIN,
    COMPONENT_PLAYER_STATE,
    COMPONENT_PHYSICS,
    
    COMPONENT_COUNT
} ComponentType;

typedef Vector2 CTransform;

typedef struct {
    Texture2D txt;
    int sprites;
    int width;
    int height;
    int frame;
} CSprite;

typedef enum {
    PLAYER_IDLE,
    PLAYER_WALK
} CPlayerState;

typedef struct {
    Vector2 *blocks;
    int blocks_size;
    int width;
    int height;
    int seed;
} CTerrain;

//typedef PhysicsBody CPhysics;

void RegisterComponents(Ecs *world);
void CreateTerrain(Ecs *world, int width, int height, int seed);
void CreatePlayer(Ecs *world);

#endif //ANDORA_COMPONENTS_H
