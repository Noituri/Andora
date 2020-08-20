#define ECS_IMPLEMENTATION

#include <stdio.h>
#include <raylib.h>
#include "utils.h"

int main()
{
	printf("Game init\n");
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Andora");
	SetTargetFPS(60);

	const int WORLD_WIDTH = 8000;
	const int WORLD_HEIGHT = 2000;

	Ecs *world = ecs_make(MAX_ENTITIES, COMPONENT_COUNT, 1);

//	Vector2* blocks = (Vector2 *) malloc(WORLD_WEIGHT * WORLD_HEIGHT * sizeof(Vector2));
//	int blocksAmount = WorldGen_Generate(blocks, WORLD_WEIGHT, WORLD_HEIGHT, 1010);

//	printf("Generated coordinates for %d blocks\n", blocksAmount);

    initGame(world);

	Camera2D camera = {
			.offset = (struct Vector2) { (float) SCREEN_WIDTH / 2, (float) SCREEN_HEIGHT / 2 },
			.rotation = 0.0f,
			.target = (struct Vector2) { 720.0f, 100.0f },
			.zoom = 1.0f
	};

	createTerrain(world, WORLD_WIDTH, WORLD_HEIGHT, 1101);

	while (!WindowShouldClose()) {
        ecs_run_systems(world, ECS_SYSTEM_UPDATE);
//	    FIXME: Port this to the ecs system
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

        ecs_run_systems(world, ECS_SYSTEM_RENDER);

        EndMode2D();

		DrawFPS(15, 15);
		EndDrawing();
	}

	freeGame(world);

	return 0;
}