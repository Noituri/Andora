#include "utils.h"

#include <filesystem>
#include <iostream>
#include <raylib-cpp.hpp>

namespace andora {
raylib::Camera2D main_camera({kScreenWidth / 2, kScreenHeight / 2}, {720, 100});
raylib::Texture2D dirt_txt;

void RenderCollisions(Physics& p) {
  std::lock_guard<std::mutex> guard(p.bodies_mutex_);
  for (const auto& body : p.bodies_) {
    DrawRectangleLines(body->position_.x, body->position_.y, body->width_,
                       body->height_, RED);
  }
}

bool IsBlockSurrounded(const Chunk& chunk, const Block& block) {
  int block_x = static_cast<int>(block.pos.x);
  int block_y = static_cast<int>(block.pos.y);
  int chunk_x = static_cast<int>(chunk.pos_x_);

  bool t = false;
  bool r = chunk_x - kBlockLen == block_x;
  bool b = false;
  bool l = chunk_x - kBlockLen * kChunkWidth == block_x;

  for (const auto& tmp_block : chunk.blocks_) {
    int tmp_block_x = static_cast<int>(tmp_block.pos.x);
    int tmp_block_y = static_cast<int>(tmp_block.pos.y);

    // BOTTOM
    if (block_y + 16 == tmp_block_y && block_x == tmp_block_x) {
      b = true;
      continue;
    }

    // TOP
    if (block_y - 16 == tmp_block_y && block_x == tmp_block_x) {
      t = true;
      continue;
    }

    // RIGHT
    if (block_x + 16 == tmp_block_x && block_y == tmp_block_y) {
      r = true;
      continue;
    }

    // LEFT
    if (block_x - 16 == tmp_block_x && block_y == tmp_block_y) {
      l = true;
      continue;
    }

    if (t && r && b && l) {
      return true;
    }
  }

  return false;
}

fs::path GetBaseDir() {
#ifdef WIN32
  fs::path base_dir = getenv("APPDATA");
  base_dir /= kGameName;
#elif __linux
  fs::path base_dir = getenv("HOME");
  base_dir /= std::string(".") + kGameName;
#endif

  return base_dir;
}

fs::path GetSaveDir() { return GetBaseDir() / "saves" / "testingWorld"; }

void CreateGameDir() {
  std::cout << "Creating game directories" << std::endl;
  fs::create_directories(GetSaveDir() / "chunks");
}

void InitGame() {
  dirt_txt.Load("./res/dirt.png");
  CreateGameDir();
}
}  // namespace andora