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

	const int TERRAIN_WIDTH = SCREEN_WIDTH;
	const int TERRAIN_HEIGHT = 200;

	Color *terrainPixels = (Color *)malloc(TERRAIN_WIDTH * TERRAIN_HEIGHT * sizeof(Color));
	for (int x = 0; x < TERRAIN_WIDTH; x++) {
		int maxY = (int)(PerlinGet2d((double)x/80, 0, 0.5, 4, 11111) * 100);
		for (int y = maxY; y < TERRAIN_HEIGHT; y++) {
			terrainPixels[TERRAIN_WIDTH * y + x] = WHITE;
		}
	}

	Image terrainImg = {
			.data = terrainPixels,
			.width = TERRAIN_WIDTH,
			.height = TERRAIN_HEIGHT,
			.format = UNCOMPRESSED_R8G8B8A8,
			.mipmaps = 1
	};

	Texture2D terrain = LoadTextureFromImage(terrainImg);
	UnloadImage(terrainImg);

	while (!WindowShouldClose()) {
		BeginDrawing();

		ClearBackground(BLACK);
		DrawText("I C nothing wrong with this code", 50, 360, 45, WHITE);

		DrawTexture(terrain, SCREEN_WIDTH / 2 - terrain.width / 2, SCREEN_HEIGHT - terrain.height, WHITE);

		EndDrawing();
	}

	UnloadTexture(terrain);
	CloseWindow();

	return 0;
}