#include <iostream>
#include "raylib-cpp.hpp"
#include "entt.hpp"
#include "timer.h"

int main() {
    raylib::Window w(1280, 720, "Andora");
    SetTargetFPS(60);
    entt::registry registry;
    
    andora::Timer timer;

	while (!w.ShouldClose()) {
		BeginDrawing();
        raylib::Color::Black.ClearBackground();
        DrawRectangle(100, 100, 50, 50, BLUE);
		EndDrawing();
    }
    return 0;
}