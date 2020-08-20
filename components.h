#ifndef ANDORA_COMPONENTS_H
#define ANDORA_COMPONENTS_H

#include <raylib.h>
#include "third_party/ecs.h"

typedef enum
{
    COMPONENT_TRANSFORM,
    COMPONENT_VELOCITY,
    COMPONENT_SPRITE,
    COMPONENT_TERRAIN,

    COMPONENT_COUNT
} ComponentType;

typedef Vector2 CTransform;

typedef struct {
    Vector2 *blocks;
    int blocksSize;
    int width;
    int height;
    int seed;
} CTerrain;

void registerComponents(Ecs *world);
void createTerrain(Ecs *world, int width, int height, int seed);

#endif //ANDORA_COMPONENTS_H
