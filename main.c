#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>
#include "perlin.h"
#include "worldgen.h"

int main()
{
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;

	printf("Game init\n");
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Andora");
	SetTargetFPS(60);

	const int WORLD_WEIGHT = 8000;
	const int WORLD_HEIGHT = 2000;

	Vector2* visibleBlocks = (Vector2 *) malloc(WORLD_WEIGHT*WORLD_HEIGHT*sizeof(Vector2));
	int blocksAmount = WorldGen_Generate(visibleBlocks, WORLD_WEIGHT, WORLD_HEIGHT, 1010);

	printf("Generated coordinates for %d blocks\n", blocksAmount);

	Image dirtImg = LoadImage("../res/dirt.png");
	Texture2D dirt = LoadTextureFromImage(dirtImg);
	UnloadImage(dirtImg);

	Camera2D camera = {
			.offset = (struct Vector2) { (float) SCREEN_WIDTH / 2, (float) SCREEN_HEIGHT / 2 },
			.rotation = 0.0f,
			.target = (struct Vector2) { 720.0f, 100.0f },
			.zoom = 1.0f
	};

	while (!WindowShouldClose()) {
		if (IsKeyDown(KEY_A)) {
			camera.target.x -= 10;
		}

		if (IsKeyDown(KEY_D)) {
			camera.target.x += 10;
		}

		if (IsKeyDown(KEY_W)) {
			camera.target.y -= 10;
		}

		if (IsKeyDown(KEY_S)) {
			camera.target.y += 10;
		}

		BeginDrawing();

		BeginMode2D(camera);

		ClearBackground(GetColor(0xB4D5F4));
		WorldGen_RenderVisibleBlocks(dirt, visibleBlocks, blocksAmount, camera.target, SCREEN_WIDTH, SCREEN_HEIGHT);
//		for (int i = 0; i < blocksAmount; i++) {
//			DrawTextureRec(dirt, (struct Rectangle) {40, 100, 16, 16}, visibleBlocks[i], WHITE);
//		}

		EndMode2D();

		DrawFPS(15, 15);
		EndDrawing();
	}

	UnloadTexture(dirt);
	CloseWindow();

	return 0;
}