#include <stdio.h>
#include <stdlib.h>
#include <raymath.h>
#include "systems.h"
#include "utils.h"

extern Texture2D dirt_txt;
extern Texture2D player_txt;
extern Camera2D camera;

int frame_counter = 0;

void RegisterSystems(Ecs *world)
{
    ecs_register_system(world, movePlayer, ECS_SYSTEM_UPDATE);
    ecs_register_system(world, renderTerrain, ECS_SYSTEM_RENDER);
    ecs_register_system(world, renderSprite, ECS_SYSTEM_RENDER);
}

// FIXME remove this test/experiment

int did_once = 0;

#define RENDER_TERRAIN_SYSTEM_MASK \
ECS_MASK(2, COMPONENT_TERRAIN, COMPONENT_TRANSFORM)
void renderTerrain(Ecs *world)
{
	for (uint32_t i = 0; i < ecs_for_count(world); i++) {
        EcsEnt entity = ecs_get_ent(world, i);
        if (ecs_ent_has_mask(world, entity, RENDER_TERRAIN_SYSTEM_MASK)) {
            CTerrain *terrain = ecs_ent_get_component(world, entity, COMPONENT_TERRAIN);
            Vector2 pos = camera.target;
            
            float right_offset = (pos.x + (float) SCREEN_WIDTH / 2.0f) + 40.0f;
            float left_offset = (pos.x - (float) SCREEN_WIDTH / 2.0f) - 16.0f * 16;
            float bottom_offset = (pos.y + (float) SCREEN_HEIGHT / 2.0f) + 40.0f;
            float top_offset = (pos.y - (float) SCREEN_HEIGHT / 2.0f) - 40.0f;
            for (int j = 0; j < terrain->chunks_size; j++) {
                Chunk tmp_chunk = terrain->chunks[j];
                if (tmp_chunk.pos_x > right_offset || tmp_chunk.pos_x < left_offset)
					continue;
                for (int k = 0; k < tmp_chunk.blocks_size; k++) {
					Vector2 tmp_block = tmp_chunk.blocks[k];

					if (tmp_block.y > bottom_offset || tmp_block.y < top_offset)
						continue;
					DrawTextureRec(dirt_txt, (Rectangle) {40, 100, 16, 16}, tmp_block, WHITE);

					if (!did_once)
						CreateCollisionsForBlock(tmp_chunk, tmp_block);
				}
			}
			did_once = 1;
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
            //            CPhysics *body = ecs_ent_get_component(world, entity, COMPONENT_PHYSICS);
            //            CTransform *pos = ecs_ent_get_component(world, entity, COMPONENT_TRANSFORM);
            //            Vector2 newPos = (*body)->position;
            
            //            if (pos->x != newPos.x || pos->y != newPos.y)
            //            	posChanged = true;
            //            *pos = (*body)->position;
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
            frame_counter++;
            if (frame_counter % 10 == 0)
                sprite->frame++;
            
            if (frame_counter == 60)
                frame_counter = 0;
            
            if (sprite-> frame > sprite->sprites)
                sprite->frame = 0;
            DrawTextureRec(sprite->txt, rec, *pos, WHITE);
        }
    }
}