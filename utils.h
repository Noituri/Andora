#ifndef ANDORA_UTILS_H
#define ANDORA_UTILS_H

#define MAX_ENTITIES 1000
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#include "systems.h"

void InitGame(Ecs *world);
void FreeGame(Ecs *world);
void RenderCollisions();
void CreateCollisionsForBlock(Chunk chunk, Vector2 block);

#endif //ANDORA_UTILS_H
