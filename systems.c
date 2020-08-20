#include <stdio.h>
#include "systems.h"
#include "utils.h"

extern Texture2D dirt;

void register_systems(Ecs *world)
{
    ecs_register_system(world, renderTerrain, ECS_SYSTEM_RENDER);
}

#define RENDER_TERRAIN_SYSTEM_MASK \
ECS_MASK(2, COMPONENT_TERRAIN, COMPONENT_TRANSFORM)
void renderTerrain(Ecs *world)
{
    for (uint32_t i = 0; i < ecs_for_count(world); i++) {
        EcsEnt entity = ecs_get_ent(world, i);
        if (ecs_ent_has_mask(world, entity, RENDER_TERRAIN_SYSTEM_MASK)) {
            CTerrain *terrain = ecs_ent_get_component(world, entity, COMPONENT_TERRAIN);
            CTransform *pos = ecs_ent_get_component(world, entity, COMPONENT_TRANSFORM);

            float rightOffset = (pos->x + (float) SCREEN_WIDTH / 2.0f) + 40.0f;
            float leftOffset = (pos->x - (float) SCREEN_WIDTH / 2.0f) - 40.0f;
            float bottomOffset = (pos->y + (float) SCREEN_HEIGHT / 2.0f) + 40.0f;
            float topOffset = (pos->y - (float) SCREEN_HEIGHT / 2.0f) - 40.0f;

            for (int j = 0; j < terrain->blocksSize; j++) {
                Vector2 tmpBlock = terrain->blocks[j];
                if (tmpBlock.x > rightOffset || tmpBlock.x < leftOffset || tmpBlock.y > bottomOffset || tmpBlock.y < topOffset)
                    continue;

                DrawTextureRec(dirt, (struct Rectangle) {40, 100, 16, 16}, tmpBlock, WHITE);
            }
        }
    }
}