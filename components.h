#ifndef ANDORA_COMPONENTS_H
#define ANDORA_COMPONENTS_H

#include <raylib.h>
#include <physac.h>
#include "third_party/ecs.h"

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
    Texture2D sprite;
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
    int blocksSize;
    int width;
    int height;
    int seed;
} CTerrain;

typedef PhysicsBody CPhysics;

void registerComponents(Ecs *world);
void createTerrain(Ecs *world, int width, int height, int seed);
void createPlayer(Ecs *world);

#endif //ANDORA_COMPONENTS_H
