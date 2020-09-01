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
    Vector2* blocks = malloc(width * height * sizeof(Vector2));
    
    int i = 0;
    for (int x = 0; x < (width / 16); x++) {
        int maxY = (int)(Perlin_Get2d((double)x / 10, 0, 0.5, 4, seed) * 100);
        for (int y = maxY / 16; y < (height / 16); y++) {
            blocks[i++] = (Vector2) { (float) x * 16, (float) y * 16 };
        }
    }
    
    printf("Generated %d blocks\n", i);
    
    CTerrain terrain = {
        .blocks = blocks,
        .blocks_size = i,
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