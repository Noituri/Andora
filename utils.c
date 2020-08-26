#include "utils.h"
#include <raylib.h>

Texture2D dirtTxt;
Texture2D playerTxt;

Camera2D camera;

void initGame(Ecs *world)
{
    // Textures
    Image dirtImg = LoadImage("../res/dirt.png");
    dirtTxt = LoadTextureFromImage(dirtImg);
    UnloadImage(dirtImg);

    Image playerImg = LoadImage("../res/player.png");
    ImageResize(&playerImg, playerImg.width * 2, playerImg.height * 2);
    playerTxt = LoadTextureFromImage(playerImg);
    UnloadImage(playerImg);

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
    UnloadTexture(dirtTxt);
    UnloadTexture(playerTxt);
    ClosePhysics();
    CloseWindow();
}