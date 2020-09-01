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
        .position = (Vector2) { 0.0f, 64.0f },
        .width = 32.0f,
        .height = 32.0f,
        .dynamic = true,
        .mass = 5.0,
        .layer = 1,
    };
    
    printf("POS Y: %f\n", B.position.y);
    AddBody(&A);
    AddBody(&B);
    
    InitGame(world);
    
	CreateTerrain(world, WORLD_WIDTH, WORLD_HEIGHT, 1101);
	CreatePlayer(world);
    
	while (!WindowShouldClose()) {
        PhysicsStep();
        printf("POS Y: %f\n", B.position.y);
        ecs_run_systems(world, ECS_SYSTEM_UPDATE);
        
		BeginDrawing();
        
        BeginMode2D(camera);
        
        ClearBackground(GetColor(0xB4D5F4));
        ecs_run_systems(world, ECS_SYSTEM_RENDER);
        RenderCollisions();
        
        EndMode2D();
        
        DrawFPS(15, 15);
        
		EndDrawing();
	}
    
	FreeGame(world);
    
	return 0;
}