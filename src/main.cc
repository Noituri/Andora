#include <iostream>

#include "entt.hpp"
#include "raylib-cpp.hpp"
#include "timer.h"
#include "physics.h"

constexpr int kTargetFPS = 60;

int main() {
  raylib::Window w(1280, 720, "Andora");
  SetTargetFPS(kTargetFPS);
  entt::registry registry;

  andora::Physics physics(kTargetFPS);

  while (!w.ShouldClose()) {
    BeginDrawing();
    raylib::Color::Black.ClearBackground();
    DrawRectangle(100, 100, 50, 50, BLUE);
    EndDrawing();
  }
  return 0;
}