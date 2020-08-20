#include "utils.h"
#include <raylib.h>

Texture2D dirt;
Camera2D camera;

void initGame(Ecs *world)
{
    // Textures
    Image dirtImg = LoadImage("../res/dirt.png");
    dirt = LoadTextureFromImage(dirtImg);
    UnloadImage(dirtImg);

    // Camera
    camera = (Camera2D) {
            .offset = (Vector2) { (float) SCREEN_WIDTH / 2, (float) SCREEN_HEIGHT / 2 },
            .rotation = 0.0f,
            .target = (Vector2) { 720.0f, 100.0f },
            .zoom = 1.0f
    };

    // ECS
    registerComponents(world);
    registerSystems(world);
}

void freeGame(Ecs *world)
{
    ecs_destroy(world);
    UnloadTexture(dirt);
    CloseWindow();
}