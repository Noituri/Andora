#include <stdio.h>
#include "systems.h"
#include "utils.h"

extern Texture2D dirtTxt;
extern Texture2D playerTxt;
extern Camera2D camera;

int frameCounter = 0;

void registerSystems(Ecs *world)
{
    ecs_register_system(world, movePlayer, ECS_SYSTEM_UPDATE);
    ecs_register_system(world, renderTerrain, ECS_SYSTEM_RENDER);
    ecs_register_system(world, renderSprite, ECS_SYSTEM_RENDER);
}

#define RENDER_TERRAIN_SYSTEM_MASK \
ECS_MASK(2, COMPONENT_TERRAIN, COMPONENT_TRANSFORM)
void renderTerrain(Ecs *world)
{
    for (uint32_t i = 0; i < ecs_for_count(world); i++) {
        EcsEnt entity = ecs_get_ent(world, i);
        if (ecs_ent_has_mask(world, entity, RENDER_TERRAIN_SYSTEM_MASK)) {
            CTerrain *terrain = ecs_ent_get_component(world, entity, COMPONENT_TERRAIN);
            Vector2 pos = camera.target;

            float rightOffset = (pos.x + (float) SCREEN_WIDTH / 2.0f) + 40.0f;
            float leftOffset = (pos.x - (float) SCREEN_WIDTH / 2.0f) - 40.0f;
            float bottomOffset = (pos.y + (float) SCREEN_HEIGHT / 2.0f) + 40.0f;
            float topOffset = (pos.y - (float) SCREEN_HEIGHT / 2.0f) - 40.0f;

            for (int j = 0; j < terrain->blocksSize; j++) {
                Vector2 tmpBlock = terrain->blocks[j];
                if (tmpBlock.x > rightOffset || tmpBlock.x < leftOffset || tmpBlock.y > bottomOffset || tmpBlock.y < topOffset)
                    continue;

                DrawTextureRec(dirtTxt, (Rectangle) {40, 100, 16, 16}, tmpBlock, WHITE);
            }
        }
    }
}

#define MOVE_PLAYER_SYSTEM_MASK \
ECS_MASK(3, COMPONENT_PLAYER_STATE, COMPONENT_PHYSICS, COMPONENT_TRANSFORM)
void movePlayer(Ecs *world)
{
    for (uint32_t i = 0; i < ecs_for_count(world); i++) {
        EcsEnt entity = ecs_get_ent(world, i);
        if (ecs_ent_has_mask(world, entity, MOVE_PLAYER_SYSTEM_MASK)) {
            CPhysics *body = ecs_ent_get_component(world, entity, COMPONENT_PHYSICS);
            CTransform *pos = ecs_ent_get_component(world, entity, COMPONENT_TRANSFORM);
            *pos = (*body)->position;
//            if (IsKeyDown(KEY_A)) {
//                camera.target.x -= 10;
//            }
//
//            if (IsKeyDown(KEY_D)) {
//                camera.target.x += 10;
//            }
//
//            if (IsKeyDown(KEY_W)) {
//                camera.target.y -= 10;
//            }
//
//            if (IsKeyDown(KEY_S)) {
//                camera.target.y += 10;
//            }

//            *pos = camera.target;
        }
    }
}

#define RENDER_SPRITE_SYSTEM_MASK \
ECS_MASK(2, COMPONENT_SPRITE, COMPONENT_TRANSFORM)
void renderSprite(Ecs *world)
{
    for (uint32_t i = 0; i < ecs_for_count(world); i++) {
        EcsEnt entity = ecs_get_ent(world, i);
        if (ecs_ent_has_mask(world, entity, RENDER_SPRITE_SYSTEM_MASK)) {
            CTransform *pos = ecs_ent_get_component(world, entity, COMPONENT_TRANSFORM);
            CSprite *sprite = ecs_ent_get_component(world, entity, COMPONENT_SPRITE);

            Rectangle rec = {
                    .width = (float) sprite->width,
                    .height = (float) sprite->height,
                    .x = (float) sprite->frame * (float) sprite->width,
                    .y = 0
            };
            frameCounter++;
            if (frameCounter % 10 == 0)
                sprite->frame++;

            if (frameCounter == 60)
                frameCounter = 0;

            if (sprite-> frame > sprite->sprites)
                sprite->frame = 0;
            DrawTextureRec(sprite->sprite, rec, *pos, WHITE);
        }
    }
}