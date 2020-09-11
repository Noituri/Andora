#pragma once

#include <raylib-cpp.hpp>
#include <vector>

namespace andora {
struct Chunk {
  std::vector<raylib::Vector2> blocks;
  int pos_x;
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