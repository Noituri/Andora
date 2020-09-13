#include "physics.h"

#include <iostream>

namespace andora {
Physics::Physics(float fps, raylib::Vector2 gravity)
    : dt_(1 / fps), gravity_(gravity) {}

Body& Physics::CreateBody(Body&& body) {
  std::unique_ptr<Body> new_body = std::make_unique<Body>(body);
  bodies_.emplace_back(std::move(new_body));

  return *bodies_.back().get();
}

void Physics::RemoveBody(int i) { bodies_.erase(bodies_.begin() + i); }

void Physics::GenerateContactPairs() {
  contacts_.clear();
  AABB A_aabb;
  AABB B_aabb;

  for (size_t i = 0; i < bodies_.size(); i++) {
    Body& A = *bodies_[i].get();

    for (size_t j = i + 1; j < bodies_.size(); j++) {
      Body& B = *bodies_[j].get();
      if (!(A.dynamic_ || B.dynamic_)) continue;

      if (!(A.layer_ & B.layer_)) continue;

      A.CalculateAABB();
      B.CalculateAABB();

      Manifold m(A, B);
      if (m.AABBvsAABB()) contacts_.emplace_back(m);
    }
  }
}

void Physics::IntegrateForces(Body& b) {
  b.velocity_ += (gravity_ + raylib::Vector2{0.0f, b.inv_mass_}) * (dt_ / 2);
}

void Physics::IntegrateVelocity(Body& b) {
  if (!b.dynamic_) return;

  b.position_ += b.velocity_ * dt_;
  IntegrateForces(b);
}

void Physics::NextStep() {
  float acc = timer_.GetElapsed();
  if (acc > 0.2f) acc = 0.2f;

  while (acc > dt_) {
    GenerateContactPairs();

    for (auto& b : bodies_) IntegrateVelocity(*b.get());
    for (auto& c : contacts_) c.SolveCollision();
    for (auto& b : bodies_) IntegrateVelocity(*b.get());
    for (auto& c : contacts_) c.PositionalCorrection();

    acc -= dt_ * 2;
  }
}
}  // namespace andora