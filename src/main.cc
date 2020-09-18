#include <entt.hpp>
#include <fstream>
#include <iostream>
#include <raylib-cpp.hpp>

#include "chunk_generated.h"
#include "entities_handler.h"
#include "physics.h"
#include "schema_handler.h"
#include "timer.h"
#include "utils.h"

int main() {
  raylib::Window w(andora::kScreenWidth, andora::kScreenHeight, "Andora");
  SetTargetFPS(andora::kTargetFPS);

  andora::InitGame();

  andora::EntitiesHandler entities_handler;
  entities_handler.CreateTerrain(2000 * andora::kBlockLen,
                                 500 * andora::kBlockLen, 12321);
  entities_handler.CreatePlayer(720.0f, -50.0f);

  while (!w.ShouldClose()) {
    if (IsKeyDown(KEY_A)) andora::main_camera.target.x -= 20;
    if (IsKeyDown(KEY_D)) andora::main_camera.target.x += 20;
    if (IsKeyDown(KEY_W)) andora::main_camera.target.y -= 20;
    if (IsKeyDown(KEY_S)) andora::main_camera.target.y += 20;
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