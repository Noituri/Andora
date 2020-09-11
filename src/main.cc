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
  andora::Body& a = physics.CreateBody({{0.0f, 500.0f}, 16, 16, 5.0});
  andora::Body& b = physics.CreateBody({{0.0f, 600.0f}, 16, 16, 0.0});

  while (!w.ShouldClose()) {
    physics.NextStep();
    BeginDrawing();
    raylib::Color::Black.ClearBackground();
    DrawRectangleV(a.position_, {16.0f, 16.0f}, BLUE);
    DrawRectangleV(b.position_, {16.0f, 16.0f}, RED);
    EndDrawing();
  }

  return 0;
}