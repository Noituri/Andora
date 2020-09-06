#define ECS_IMPLEMENTATION

#include <raymath.h>
#include "utils.h"

extern Camera2D camera;

int main()
{
	printf("Game init\n");
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Andora");
    
    SetTargetFPS(60);
    
    const int WORLD_WIDTH = 2000;
	const int WORLD_HEIGHT = 1000;
    
	Ecs *world = ecs_make(MAX_ENTITIES, COMPONENT_COUNT, 3);
    
    InitPhysics();

    InitGame(world);
    
	CreateTerrain(world, WORLD_WIDTH, WORLD_HEIGHT, 1101);
	CreatePlayer(world);

	Body *TestBody = CreateBody((Vector2) { 0.0f, -200.0f }, 16, 16, 5.0f);
	TestBody->dynamic = 1;
	TestBody->restitution = 0.0f;

	while (!WindowShouldClose()) {
        PhysicsStep();
        //printf("POS Y: %f\n", TestBody.position.y);
//        ecs_run_systems(world, ECS_SYSTEM_UPDATE);

//        if (IsKeyDown(KEY_R)) {
//			TestBody->position.x = 0;
//			TestBody->position.y = -200;
//			TestBody->velocity = (Vector2) {0.0f, 0.0f};
//		}
//		if (IsKeyDown(KEY_A))
//			TestBody->velocity.x -= 1;
//		if (IsKeyDown(KEY_D))
//			TestBody->velocity.x += 1;
//		if (IsKeyDown(KEY_W))
//			TestBody->velocity.y -= 2;

		if (IsKeyDown(KEY_A))
			camera.target.x -= 20;
		if (IsKeyDown(KEY_D))
			camera.target.x += 20;
		if (IsKeyDown(KEY_W))
			camera.target.y -= 20;
		if (IsKeyDown(KEY_S))
			camera.target.y += 20;

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