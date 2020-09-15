#pragma once

#include <memory>
#include <vector>

#include "manifold.h"
#include "timer.h"

namespace andora {
class Physics {
 public:
  std::vector<std::unique_ptr<Body>> bodies_;

  Physics(float fps, raylib::Vector2 gravity);
  int CreateBody(Body&& body);
  void RemoveBody(int i);
  void NextStep();

 private:
  Timer timer_;
  float dt_;
  raylib::Vector2 gravity_;
  std::vector<Manifold> contacts_;

  void GenerateContactPairs();
  void IntegrateForces(Body& b);
  void IntegrateVelocity(Body& b);
};
}  // namespace andora