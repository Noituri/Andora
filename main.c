#define ECS_IMPLEMENTATION

#include "utils.h"
#include "physics.h"

extern Camera2D camera;

int main()
{
	printf("Game init\n");
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Andora");
    
    SetTargetFPS(60);
    
    const int WORLD_WIDTH = 8000;
	const int WORLD_HEIGHT = 2000;
    
	Ecs *world = ecs_make(MAX_ENTITIES, COMPONENT_COUNT, 3);
    
    InitPhysics();
    
    Body A = {
        .position = (Vector2) { 0.0f, 0.0f },
        .width = 32.0f,
        .height = 32.0f,
        .layer = 1,
    };
    
    
    Body B = {
        .position = (Vector2) { 0.0f, 31.0f },
        .width = 32.0f,
        .height = 32.0f,
        .dynamic = true,
        .layer = 1,
    };
    
    extern Body bodies[];
    extern int bodiesCount;
    extern int pairsCount;
    bodies[0] = A;
    bodies[1] = B;
    bodiesCount = 2;
    printf("contacts: %d\n", pairsCount);
    GenerateContactPairs();
    printf("contacts: %d\n", pairsCount);
    
    
    return 0;
    initGame(world);
    
	createTerrain(world, WORLD_WIDTH, WORLD_HEIGHT, 1101);
	createPlayer(world);
    
	while (!WindowShouldClose()) {
        ecs_run_systems(world, ECS_SYSTEM_UPDATE);
        
		BeginDrawing();
        
        BeginMode2D(camera);
        
        ClearBackground(GetColor(0xB4D5F4));
        ecs_run_systems(world, ECS_SYSTEM_RENDER);
        renderCollisions();
        
        EndMode2D();
        
        DrawFPS(15, 15);
        
		EndDrawing();
	}
    
	freeGame(world);
    
	return 0;
}