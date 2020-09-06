#include <stdlib.h>
#include <stdio.h>
#include "components.h"
#include "third_party/perlin.h"

extern Texture2D player_txt;

void RegisterComponents(Ecs *world)
{
    ecs_register_component(world, COMPONENT_TERRAIN, 1000, sizeof(CTerrain), NULL);
    ecs_register_component(world, COMPONENT_TRANSFORM, 1000, sizeof(CTransform), NULL);
    ecs_register_component(world, COMPONENT_PLAYER_STATE, 1000, sizeof(CPlayerState), NULL);
    ecs_register_component(world, COMPONENT_SPRITE, 1000, sizeof(CSprite), NULL);
    //    ecs_register_component(world, COMPONENT_PHYSICS, 1000, sizeof(CPhysics), NULL);
}

void CreateTerrain(Ecs *world, int width, int height, int seed)
{
    EcsEnt entity = ecs_ent_make(world);
    Chunk *chunks = (Chunk *) malloc(1000 * sizeof(Chunk));
    
    int chunks_size = 0;
	Chunk *chunk = &chunks[chunks_size];
	for (int x = 0; x < (width / 16); x++) {
		if (x % 16 == 0) {
			chunk = &chunks[chunks_size];
			chunks_size++;
			chunk->blocks_size = 0;
			chunk->blocks = malloc(CHUNK_WIDTH * CHUNK_HEIGHT * sizeof(Vector2));
			chunk->pos_x = x;
		}
		int maxY = (int)(Perlin_Get2d((double)x / 10, 0, 0.5, 4, seed) * 100);
		for (int y = maxY / 16; y < (height / 16); y++) {
			chunk->blocks[chunk->blocks_size++] = (Vector2) { (float) x * 16, (float) y * 16 };
		}
    }
	for (int i = 0; i < chunks_size; i++) {
		Chunk tmp_c = chunks[i];
		Chunk c = tmp_c;
	}
    printf("Generated %d chunks\n", chunks_size);

    // TODO(noituri): Load only visible chunks to memory, the other chunks should be saved on the disk and freed from memory
    CTerrain terrain = {
        .chunks = chunks,
        .chunks_size = chunks_size,
        .width = width,
        .height = height,
        .seed = seed
    };
    CTransform transform = { 720.0f, 100.0f };
    
    ecs_ent_add_component(world, entity,COMPONENT_TERRAIN, &terrain);
    ecs_ent_add_component(world, entity, COMPONENT_TRANSFORM, &transform);
}

void CreatePlayer(Ecs *world)
{
    EcsEnt entity = ecs_ent_make(world);
    CPlayerState p_state = PLAYER_IDLE;
    CTransform transform = { 720.0f, -150.0f };
    
    CSprite sprite = {
        .txt = player_txt,
        .sprites = 9,
        .width = player_txt.width / 9,
        .height = 64 * 2,
        .frame = 0
    };
    
    //    CPhysics body = CreatePhysicsBodyRectangle(transform, (float) playerTxt.width / 9, 64 * 2, 1);
    //    body->freezeOrient = true;
    
    ecs_ent_add_component(world, entity, COMPONENT_PLAYER_STATE, &p_state);
    ecs_ent_add_component(world, entity, COMPONENT_TRANSFORM, &transform);
    ecs_ent_add_component(world, entity, COMPONENT_SPRITE, &sprite);
    //    ecs_ent_add_component(world, entity, COMPONENT_PHYSICS, &body);
}