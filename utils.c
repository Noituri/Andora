#include "utils.h"
#include <raylib.h>

Texture2D dirt;

void initGame(Ecs *world)
{
    Image dirtImg = LoadImage("../res/dirt.png");
    dirt = LoadTextureFromImage(dirtImg);
    UnloadImage(dirtImg);
    register_components(world);
    register_systems(world);
}

void freeGame(Ecs *world)
{
    ecs_destroy(world);
    UnloadTexture(dirt);
    CloseWindow();
}