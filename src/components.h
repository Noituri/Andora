#pragma once

#include <raylib-cpp.hpp>
#include <vector>

namespace andora {
class Chunk {
 public:
  std::string name_;
  std::vector<raylib::Vector2> blocks_;
  int pos_x_;

  Chunk() = default;
  Chunk(const char* name);
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
};

}  // namespace andora::comp