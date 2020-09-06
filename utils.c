#include "utils.h"
#include "physics.h"

#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>

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
        .target = (Vector2) { 1000.0f, 200.0f },
        .zoom = 1.0f
    };
    
    // ECS
    RegisterComponents(world);
    RegisterSystems(world);
}

void FreeGame(Ecs *world)
{
    FreePhysics();
    UnloadTexture(dirt_txt);
    UnloadTexture(player_txt);
    ecs_destroy(world);
    CloseWindow();
    printf("Game has been freed\n");
}


void RenderCollisions()
{
	int bodies_amount = 0;
	Body **bodies = GetBodies(&bodies_amount);
	for (int i = 0; i < bodies_amount; i++) {
		Body *body = bodies[i];
		DrawRectangleLines(body->position.x, body->position.y, body->width, body->height, RED);
	}
}

void CreateCollisionsForBlock(Chunk chunk, Vector2 block)
{
	int l = 0, r = 0, t = 0, b = 0;
	for (int current_block = 0; current_block < chunk.blocks_size; current_block++) {
		Vector2 tmp = chunk.blocks[current_block];
		// BOTTOM
		if ((int)block.y + 16 == (int)tmp.y && (int)block.x == (int)tmp.x) {
			b = 1;
			continue;
		}

		// TOP
		if ((int)block.y - 16 == (int)tmp.y && (int)block.x == (int)tmp.x) {
			t = 1;
			continue;
		}

		// RIGHT
		if ((int)block.x + 16 == (int)tmp.x && (int)block.y == (int)tmp.y) {
			r = 1;
			continue;
		}

		// LEFT
		if ((int)block.x - 16 == (int)tmp.x && (int)block.y == (int)tmp.y) {
			l = 1;
			continue;
		}
		if (t && r && b && l) {
			break;
		}
	}

	if (!(t && r && b && l))
		CreateBody(block, 16, 16, 0.0f);
}