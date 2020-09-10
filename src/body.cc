#include "body.h"

namespace andora {
Body::Body(raylib::Vector2 pos, float width, float height, float mass) {
  position_ = pos;
  width_ = width;
  height_ = height_;
  mass_ = mass;
  inv_mass_ = mass ? (1 / mass) : 0;
  dynamic_ = mass != 0;
  layer_ = 1;
  restitution_ = 0.2f;
  dynamic_friction_ = 0.2f;
  static_friction_ = 0.4f;
  velocity_ = raylib::Vector2::Zero();
}
}  // namespace andora