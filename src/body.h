#pragma once

#include <optional>
#include <raylib-cpp.hpp>

namespace andora {
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

  std::optional<int> owner_;

  Body(raylib::Vector2 pos, float width, float height, float mass);
};

}  // namespace andoradd