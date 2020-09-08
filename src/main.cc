#define RAYMATH_IMPLEMENTATION
#include <iostream>
#include "raylib-cpp.hpp"
#include "entt.hpp"

int main() {
    raylib::Window w(1280, 720, "Andora");
    SetTargetFPS(60);
    entt::registry registry;
    
	while (!w.ShouldClose()) {
		BeginDrawing();
        raylib::Color::White.ClearBackground();
        DrawRectangle(100, 100, 50, 50, BLUE);
		EndDrawing();
    }
    return 0;
}