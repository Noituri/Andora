#include <entt.hpp>
#include <iostream>
#include <raylib-cpp.hpp>

#include "entities_handler.h"
#include "physics.h"
#include "timer.h"
#include "utils.h"

int main() {
  raylib::Window w(andora::kScreenWidth, andora::kScreenHeight, "Andora");
  SetTargetFPS(andora::kTargetFPS);

  andora::InitGame();

  andora::EntitiesHandler entities_handler;
  entities_handler.CreateTerrain(2000 * andora::kBlockLen, 1000 * andora::kBlockLen, 12321);

  while (!w.ShouldClose()) {
    if (IsKeyDown(KEY_A))
      andora::main_camera.target.x -= 20;
    if (IsKeyDown(KEY_D))
      andora::main_camera.target.x += 20;
    if (IsKeyDown(KEY_W))
      andora::main_camera.target.y -= 20;
    if (IsKeyDown(KEY_S))
      andora::main_camera.target.y += 20;
    
    entities_handler.UpdateNormal();

    BeginDrawing();
    andora::main_camera.BeginMode2D();
    {
      raylib::Color::SkyBlue.ClearBackground();
      entities_handler.UpdateRender();
    }
    andora::main_camera.EndMode2D();

    DrawFPS(10, 10);
    EndDrawing();
  }

  return 0;
}