#include <stdlib.h>
#include <stdio.h>
#include "components.h"
#include "third_party/perlin.h"

void freeSprite(void *data)
{
    CSprite *sprite = (CSprite *) data;
    UnloadTexture(sprite->sprite);
}

void registerComponents(Ecs *world)
{
    ecs_register_component(world, COMPONENT_TERRAIN, 1000, sizeof(CTerrain), NULL);
    ecs_register_component(world, COMPONENT_TRANSFORM, 1000, sizeof(CTransform), NULL);
    ecs_register_component(world, COMPONENT_PLAYER_STATE, 1000, sizeof(CPlayerState), NULL);
    ecs_register_component(world, COMPONENT_SPRITE, 1000, sizeof(CSprite), freeSprite);
}

void createTerrain(Ecs *world, int width, int height, int seed)
{
    EcsEnt entity = ecs_ent_make(world);
    Vector2* blocks = malloc(width * height * sizeof(Vector2));

    int i = 0;
    for (int x = 0; x < (width / 16); x++) {
        int maxY = (int)(Perlin_Get2d((double)x / 10, 0, 0.5, 4, seed) * 100);
        for (int y = maxY / 16; y < (height / 16); y++) {
            blocks[i] = (Vector2) { (float) x * 16, (float) y * 16 };
            i++;
        }
    }

    printf("Generated %d blocks\n", i);

    CTerrain terrain = {
            .blocks = blocks,
            .blocksSize = i,
            .width = width,
            .height = height,
            .seed = seed
    };
    CTransform transform = { 720.0f, 100.0f };

    ecs_ent_add_component(world, entity,COMPONENT_TERRAIN, &terrain);
    ecs_ent_add_component(world, entity, COMPONENT_TRANSFORM, &transform);
}

void createPlayer(Ecs *world)
{
    EcsEnt entity = ecs_ent_make(world);
    CPlayerState pState = PLAYER_IDLE;
    CTransform transform = { 720.0f, 100.0f };

    Image img = LoadImage("../res/player.png");
    CSprite sprite = {
            .sprite = LoadTextureFromImage(img),
            .sprites = 9
    };
    UnloadImage(img);

    ecs_ent_add_component(world, entity, COMPONENT_PLAYER_STATE, &pState);
    ecs_ent_add_component(world, entity, COMPONENT_TRANSFORM, &transform);
    ecs_ent_add_component(world, entity, COMPONENT_SPRITE, &sprite);
}