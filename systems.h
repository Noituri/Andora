#ifndef ANDORA_SYSTEMS_H
#define ANDORA_SYSTEMS_H

#include "components.h"

void RegisterSystems(Ecs *world);
void renderTerrain(Ecs *world);
void movePlayer(Ecs *world);
void renderSprite(Ecs *world);

#endif //ANDORA_SYSTEMS_H
