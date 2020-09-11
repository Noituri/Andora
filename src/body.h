#ifndef ANDORA_BODY_H
#define ANDORA_BODY_H

#include <raylib-cpp.hpp>

namespace andora {
struct AABB {
  raylib::Vector2 min{};
  raylib::Vector2 max{};
};

class Body {
 public:
  int layer_;

  float width_;
  float height_;
  raylib::Vector2 position_;
  raylib::Vector2 velocity_;

  float static_friction_;
  float dynamic_friction_;
  float restitution_;

  float mass_;
  float inv_mass_;

  bool dynamic_;

  AABB aabb_{};

  Body(raylib::Vector2 pos, float width, float height, float mass);
  void CalculateAABB();
};

}  // namespace andora

#endif  // ANDORA_BODY_H