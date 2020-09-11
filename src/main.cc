#include <entt.hpp>
#include <iostream>
#include <raylib-cpp.hpp>

#include "entities_handler.h"
#include "physics.h"
#include "timer.h"
#include "utils.h"

int main() {
  raylib::Window w(1280, 720, "Andora");
  SetTargetFPS(andora::kTargetFPS);

  andora::EntitiesHandler entities_handler;
  entities_handler.CreateTerrain(2000, 1000, 420);

  return 0;  // Ignore code below for now
  andora::Physics physics(andora::kTargetFPS);
  andora::Body& a = physics.CreateBody({{0.0f, 500.0f}, 16, 16, 5.0});
  andora::Body& b = physics.CreateBody({{0.0f, 600.0f}, 16, 16, 0.0});

  while (!w.ShouldClose()) {
    physics.NextStep();
    if (IsKeyDown(KEY_R)) a.position_.y = 500.0f;
    BeginDrawing();
    raylib::Color::Black.ClearBackground();
    DrawRectangleV(a.position_, {16.0f, 16.0f}, BLUE);
    DrawRectangleV(b.position_, {16.0f, 16.0f}, RED);
    EndDrawing();
  }

  return 0;
}