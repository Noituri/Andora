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
        .position = (Vector2) { 0.0f, SCREEN_HEIGHT - 32 },
        .width = 32.0f,
        .height = 32.0f,
        .layer = 1,
        .restitution = 0.2f,
        .dynamic_friction = 0.2f,
        .static_friction = 0.4f,
    };
    
    Body B = {
        .position = (Vector2) { 0.0f, 200.0f },
        .width = 32.0f,
        .height = 32.0f,
        .dynamic = true,
        .mass = 5.0f,
        .layer = 1,
        .restitution = 0.0f,
        .dynamic_friction = 0.2f,
        .static_friction = 0.4f,
    };

	Body C = {
			.position = (Vector2) { 32.0f, SCREEN_HEIGHT - 32 },
			.width = 32.0f,
			.height = 32.0f,
			.layer = 1,
			.restitution = 0.2f,
			.dynamic_friction = 0.2f,
			.static_friction = 0.4f,
	};

	Body D = {
			.position = (Vector2) { 64.0f, SCREEN_HEIGHT - 32 },
			.width = 32.0f,
			.height = 32.0f,
			.layer = 1,
			.restitution = 0.2f,
			.dynamic_friction = 0.2f,
			.static_friction = 0.4f,
	};

	Body E = {
			.position = (Vector2) { 96.0f, SCREEN_HEIGHT },
			.width = 32.0f,
			.height = 32.0f,
			.layer = 1,
			.restitution = 0.2f,
			.dynamic_friction = 0.2f,
			.static_friction = 0.4f,
	};

	Body F = {
			.position = (Vector2) { 128.0f, SCREEN_HEIGHT },
			.width = 32.0f,
			.height = 32.0f,
			.layer = 1,
			.restitution = 0.2f,
			.dynamic_friction = 0.2f,
			.static_friction = 0.4f,
	};

	Body G = {
			.position = (Vector2) { 160.0f, SCREEN_HEIGHT - 32 },
			.width = 32.0f,
			.height = 32.0f,
			.layer = 1,
			.restitution = 0.2f,
			.dynamic_friction = 0.2f,
			.static_friction = 0.4f,
	};
    
    AddBody(&A);
	AddBody(&B);
	AddBody(&C);
	AddBody(&D);
	AddBody(&E);
	AddBody(&F);
	AddBody(&G);

    InitGame(world);
    
	CreateTerrain(world, WORLD_WIDTH, WORLD_HEIGHT, 1101);
	CreatePlayer(world);
    
	while (!WindowShouldClose()) {
        PhysicsStep();
        //printf("POS Y: %f\n", B.position.y);
        //ecs_run_systems(world, ECS_SYSTEM_UPDATE);
        
        if (IsKeyDown(KEY_R)) {
			B.position.x = 0;
			B.position.y = 200;
		}
		if (IsKeyDown(KEY_A))
			B.velocity.x -= 1;
		if (IsKeyDown(KEY_D))
			B.velocity.x += 1;
		if (IsKeyDown(KEY_W))
			B.velocity.y -= 2;
        
		BeginDrawing();
        
        //BeginMode2D(camera);
        
        ClearBackground(GetColor(0xB4D5F4));
        //ecs_run_systems(world, ECS_SYSTEM_RENDER);

		DrawRectangle(A.position.x, A.position.y, 32, 32, RED);
		DrawRectangle(E.position.x, E.position.y, 32, 32, RED);
		DrawRectangle(C.position.x, C.position.y, 32, 32, RED);
		DrawRectangle(D.position.x, D.position.y, 32, 32, RED);
		DrawRectangle(F.position.x, F.position.y, 32, 32, RED);
		DrawRectangle(G.position.x, G.position.y, 32, 32, RED);

		DrawRectangle(B.position.x, B.position.y, 32, 32, BLUE);
		//EndMode2D();
        
        DrawFPS(15, 15);
        
		EndDrawing();
	}
    
	FreeGame(world);
    
	return 0;
}