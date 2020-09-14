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
  //  Flatbuffer experiment
  // {
  //   // andora::SchemaHandler<andora::schema::Chunk *> chunk(
  //   //     "chunk.data", andora::schema::GetChunk);

  //   // std::cout << "CHUNK POS_X" << chunk.scheme_->pos_x() << std::endl;
  // flatbuffers::FlatBufferBuilder builder(1024);
  // andora::schema::Vec2 blocks[] = {{1.0, 1.0}, {2.0, 1.0}, {0.0, 0.0}};
  // auto blocks_vec = builder.CreateVectorOfStructs(blocks, 3);
  // auto chunk = andora::schema::CreateChunk(builder, 16.0, blocks_vec);
  // builder.Finish(chunk);

  // auto chunk_file =
  //     std::fstream("chunk.data", std::ios::out | std::ios::binary);
  // chunk_file.write(reinterpret_cast<char *>(builder.GetBufferPointer()),
  //                  builder.GetSize());

  //   // chunk_file.close();
  //   // auto loaded_chunk = andora::schema::GetChunk(data);

  //   // std::cout << "CHUNK POS_X " << loaded_chunk->pos_x() << ", BLOCK0 "
  //   //           << loaded_chunk->blocks()->Get(0)->x() << std::endl;
  // }

  // return 0;

  raylib::Window w(andora::kScreenWidth, andora::kScreenHeight, "Andora");
  SetTargetFPS(andora::kTargetFPS);

  andora::InitGame();

  andora::EntitiesHandler entities_handler;
  entities_handler.CreateTerrain(2000 * andora::kBlockLen,
                                 1000 * andora::kBlockLen, 12321);

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