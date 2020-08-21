#define ECS_IMPLEMENTATION

#include <stdio.h>
#include <raylib.h>
#include "utils.h"

extern Camera2D camera;

int main()
{
	printf("Game init\n");
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Andora");
	SetTargetFPS(60);

	const int WORLD_WIDTH = 8000;
	const int WORLD_HEIGHT = 2000;

	Ecs *world = ecs_make(MAX_ENTITIES, COMPONENT_COUNT, 2);

    initGame(world);

	createTerrain(world, WORLD_WIDTH, WORLD_HEIGHT, 1101);
	createPlayer(world);

	while (!WindowShouldClose()) {
        ecs_run_systems(world, ECS_SYSTEM_UPDATE);

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