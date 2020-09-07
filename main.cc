#include <iostream>
#include <raylib.h>
#include <entt.hpp>

int main() {
	InitWindow(1280, 720, "Andora");
    SetTargetFPS(60);

	while (!WindowShouldClose()) {
		BeginDrawing();
        ClearBackground(BLACK);
        DrawRectangle(100, 100, 50, 50, RED);
		EndDrawing();
    }
    return 0;
}