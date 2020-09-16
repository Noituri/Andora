#pragma once

#include <raylib-cpp.hpp>
#include <vector>

namespace andora {
struct Block {
  raylib::Vector2 pos;
  bool has_collider;
  bool loaded_collider;
};

class Chunk {
 public:
  std::string name_;
  std::vector<Block> blocks_;
  int pos_x_;
  int id_;

  Chunk() = default;
  Chunk(const char* name, int id);
  void Write();
};
}  // namespace andora

namespace andora::comp {

using Transform = raylib::Vector2;

struct Sprite {
  raylib::Texture2D txt;
  int sprites;
  int width;
  int height;
  int frame;
};

struct Terrain {
  std::vector<Chunk> chunks;
  int width;
  int height;
  int seed;
  int chunks_created;
};

}  // namespace andora::comp