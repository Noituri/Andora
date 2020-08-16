#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>
#include "perlin.h"

int main()
{
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;

	printf("Game init\n");
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Andora");
	SetTargetFPS(60);

	const int TERRAIN_HEIGHT = 1000;

	Vector2 *visibleBlocks = (Vector2 *) malloc(SCREEN_WIDTH*SCREEN_HEIGHT*sizeof(Vector2));

	int blocksAmount = 0;
	for (int x = 0; x < (SCREEN_WIDTH / 16 + 10); x++) { // TODO: Use chunks
		int maxY = (int)(PerlinGet2d((double) x/80, 0, 0.5, 4, 11111) * 100);
		for (int y = maxY / 16; y < (TERRAIN_HEIGHT / 16 + 10); y++) {
			visibleBlocks[blocksAmount] = (struct Vector2) { (float) x * 16, (float) y * 16 };
			blocksAmount++;
		}
	}

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
		for (int i = 0; i < blocksAmount; i++) {
			DrawTextureRec(dirt, (struct Rectangle) {40, 100, 16, 16}, visibleBlocks[i], WHITE);
		}

		EndMode2D();

		DrawFPS(15, 15);
		EndDrawing();
	}

	UnloadTexture(dirt);
	CloseWindow();

	return 0;
}