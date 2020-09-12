#include "utils.h"

#include <raylib-cpp.hpp>

namespace andora {

raylib::Camera2D main_camera({kScreenWidth / 2, kScreenHeight / 2}, {720, 500});
raylib::Texture2D dirt_txt;

void InitGame() { dirt_txt.Load("./res/dirt.png"); }

void RenderCollisions(Physics& p) {
  for (const auto& body : p.bodies_) {
    DrawRectangleLines(body->position_.x, body->position_.y, body->width_,
                       body->height_, RED);
  }
}
}  // namespace andora