#include "physics.h"

#include <iostream>

namespace andora {
Physics::Physics(float fps) : dt_(1 / fps) { timer_ = Timer(); }

Body& Physics::CreateBody(Body&& body) {
  std::unique_ptr<Body> new_body = std::make_unique<Body>(body);
  bodies_.emplace_back(std::move(new_body));

  return *bodies_.front().get();
}

void Physics::RemoveBody(int i) { bodies_.erase(bodies_.begin() + i); }
}  // namespace andora