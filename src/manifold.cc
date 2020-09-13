#include "manifold.h"

#include <cmath>
#include <iostream>

namespace andora {
Manifold::Manifold(Body& A, Body& B) : A_(A), B_(B) {}

void Manifold::PositionalCorrection() {
  constexpr float kPercent = 0.2f;
  constexpr float kSlop = 0.01f;

  raylib::Vector2 correction =
      normal_ *
      (std::max(penetration_ - kSlop, 0.0f) / (A_.inv_mass_ + B_.inv_mass_)) *
      kPercent;
  
  A_.position_ -= correction * A_.inv_mass_;
  B_.position_ += correction * B_.inv_mass_;
}

void Manifold::SolveCollision() {
  raylib::Vector2 relative_v = B_.velocity_ - A_.velocity_;
  float vel_along_normal = relative_v.DotProduct(normal_);
  if (vel_along_normal > 0) return;

  float e = std::min(A_.restitution_, B_.restitution_);
  float j = -(e + 1) * vel_along_normal;
  j /= A_.inv_mass_ + B_.inv_mass_;

  raylib::Vector2 impulse = normal_ * j;
  A_.velocity_ -= impulse * A_.inv_mass_;
  B_.velocity_ += impulse * B_.inv_mass_;

  relative_v = B_.velocity_ - A_.velocity_;
  raylib::Vector2 tangent =
      relative_v - normal_ * relative_v.DotProduct(normal_);
  if (tangent.Length() == 0) return;
  tangent.Normalize();

  float jt = -relative_v.DotProduct(tangent);
  jt /= A_.inv_mass_ + B_.inv_mass_;
  float mu = std::sqrt(std::pow(2.0, A_.static_friction_) +
                        std::pow(2.0, B_.static_friction_));

  raylib::Vector2 friction_impulse;
  if (std::abs(jt) < j * mu) {
    friction_impulse = tangent * jt;
  } else {
    float dynamic_friction = std::sqrt(std::pow(2.0, A_.dynamic_friction_) +
                                        std::pow(2.0, B_.dynamic_friction_));
    friction_impulse = tangent * -j * dynamic_friction;
  }

  A_.velocity_ -= friction_impulse * A_.inv_mass_;
  B_.velocity_ += friction_impulse * B_.inv_mass_;
}

bool Manifold::AABBvsAABB() {
  AABB A_aabb = A_.aabb_;
  AABB B_aabb = B_.aabb_;

  raylib::Vector2 n = B_.position_ - A_.position_;
  float a_extent = (A_aabb.max.x - A_aabb.min.x) / 2;
  float b_extent = (B_aabb.max.x - B_aabb.min.x) / 2;

  float x_overlap = a_extent + b_extent - fabsf(n.x);
  if (x_overlap > 0) {
    a_extent = (A_aabb.max.y - A_aabb.min.y) / 2;
    b_extent = (B_aabb.max.y - B_aabb.min.y) / 2;

    float y_overlap = a_extent + b_extent - fabsf(n.y);
    if (y_overlap > 0) {
      if (x_overlap < y_overlap) {
        if (n.x < 0)
          normal_ = raylib::Vector2{-1, 0};
        else
          normal_ = raylib::Vector2{1, 0};
        penetration_ = x_overlap;
      } else {
        if (n.y < 0)
          normal_ = raylib::Vector2{0, -1};
        else
          normal_ = raylib::Vector2{0, 1};
        penetration_ = y_overlap;
      }

      return true;
    }
  }

  return false;
}
}  // namespace andora