#ifndef ANDORA_UTILS_H
#define ANDORA_UTILS_H

#define MAX_ENTITIES 1000
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#include "systems.h"

void initGame(Ecs *world);
void freeGame(Ecs *world);
void renderCollisions();

#endif //ANDORA_UTILS_H
