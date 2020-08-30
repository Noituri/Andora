#include "utils.h"
#include <raylib.h>

Texture2D dirt_txt;
Texture2D player_txt;

Camera2D camera;

void InitGame(Ecs *world)
{
    // Textures
    Image dirt_img = LoadImage("../res/dirt.png");
    dirt_txt = LoadTextureFromImage(dirt_img);
    UnloadImage(dirt_img);
    
    Image player_img = LoadImage("../res/player.png");
    ImageResize(&player_img, player_img.width * 2, player_img.height * 2);
    player_txt = LoadTextureFromImage(player_img);
    UnloadImage(player_img);
    
    // Camera
    camera = (Camera2D) {
        .offset = (Vector2) { (float) SCREEN_WIDTH / 2, (float) SCREEN_HEIGHT / 2 },
        .rotation = 0.0f,
        .target = (Vector2) { 720.0f, 100.0f },
        .zoom = 1.0f
    };
    
    // ECS
    RegisterComponents(world);
    RegisterSystems(world);
}

void FreeGame(Ecs *world)
{
    ecs_destroy(world);
    UnloadTexture(dirt_txt);
    UnloadTexture(player_txt);
    CloseWindow();
}