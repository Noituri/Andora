#include <stdio.h>
#include "systems.h"
#include "utils.h"

extern Texture2D dirt;
extern Camera2D camera;

void registerSystems(Ecs *world)
{
    ecs_register_system(world, moveCamera, ECS_SYSTEM_UPDATE);
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

                DrawTextureRec(dirt, (Rectangle) {40, 100, 16, 16}, tmpBlock, WHITE);
            }
        }
    }
}

#define RENDER_TERRAIN_SYSTEM_MASK \
ECS_MASK(2, COMPONENT_TERRAIN, COMPONENT_TRANSFORM)
void moveCamera(Ecs *world)
{
    for (uint32_t i = 0; i < ecs_for_count(world); i++) {
        EcsEnt entity = ecs_get_ent(world, i);
        if (ecs_ent_has_mask(world, entity, RENDER_TERRAIN_SYSTEM_MASK)) {
            CTransform *pos = ecs_ent_get_component(world, entity, COMPONENT_TRANSFORM);

            if (IsKeyDown(KEY_A)) {
                camera.target.x -= 10;
            }

            if (IsKeyDown(KEY_D)) {
                camera.target.x += 10;
            }

            if (IsKeyDown(KEY_W)) {
                camera.target.y -= 10;
            }

            if (IsKeyDown(KEY_S)) {
                camera.target.y += 10;
            }

            *pos = camera.target;
        }
    }
}