#include "utils.h"

#include <filesystem>
#include <iostream>
#include <raylib-cpp.hpp>

namespace andora {
raylib::Camera2D main_camera({kScreenWidth / 2, kScreenHeight / 2}, {720, 100});
raylib::Texture2D dirt_txt;

void RenderCollisions(Physics& p) {
  for (const auto& body : p.bodies_) {
    DrawRectangleLines(body->position_.x, body->position_.y, body->width_,
                       body->height_, RED);
  }
}

// void CreateBlockCollisions(Physics& p, const Chunk& chunk,
//                            const raylib::Vector2& block) {
//   int t = 0, r = 0, b = 0, l = 0;
//   for (const auto& tmp_block : chunk.blocks) {
//     // BOTTOM
//     if ((int)block.y + 16 == (int)tmp_block.y &&
//         (int)block.x == (int)tmp_block.x) {
//       b = 1;
//       continue;
//     }

//     // TOP
//     if ((int)block.y - 16 == (int)tmp_block.y &&
//         (int)block.x == (int)tmp_block.x) {
//       t = 1;
//       continue;
//     }

//     // RIGHT
//     if ((int)block.x + 16 == (int)tmp_block.x &&
//         (int)block.y == (int)tmp_block.y) {
//       r = 1;
//       continue;
//     }

//     // LEFT
//     if ((int)block.x - 16 == (int)tmp_block.x &&
//         (int)block.y == (int)tmp_block.y) {
//       l = 1;
//       continue;
//     }
//     if (t && r && b && l) {
//       break;
//     }
//   }

//   if (!(t && r && b && l)) p.CreateBody({block, kBlockLen, kBlockLen, 0.0f});
// }

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