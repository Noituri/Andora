#include <iostream>

#include "entt.hpp"
#include "physics.h"
#include "raylib-cpp.hpp"
#include "timer.h"

constexpr int kTargetFPS = 60;

int main() {
  raylib::Window w(1280, 720, "Andora");
  SetTargetFPS(kTargetFPS);
  entt::registry registry;

  andora::Physics physics(kTargetFPS);
  physics.CreateBody(andora::Body({ 0.0f, 0.0f }, 16, 16, 0.0));

  while (!w.ShouldClose()) {
    BeginDrawing();
    raylib::Color::Black.ClearBackground();
    DrawRectangle(100, 100, 50, 50, BLUE);
    EndDrawing();
  }

  return 0;
}