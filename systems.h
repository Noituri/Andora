#ifndef ANDORA_SYSTEMS_H
#define ANDORA_SYSTEMS_H

#include "components.h"

void registerSystems(Ecs *world);
void renderTerrain(Ecs *world);
void moveCamera(Ecs *world);
void renderSprite(Ecs *world);

#endif //ANDORA_SYSTEMS_H
