#ifndef ANDORA_PHYSICS_H
#define ANDORA_PHYSICS_H

#include <raymath.h>

#include <memory>
#include <vector>

#include "manifold.h"
#include "timer.h"

namespace andora {
class Physics {
 public:
  Physics(float fps);
  Body& CreateBody(Body&& body);

 private:
  Timer timer_;
  float dt_;
  Vector2 gravity_;
  std::vector<std::unique_ptr<Body>> bodies_;
  std::vector<Manifold> contacts_;
};
}  // namespace andora

#endif  // ANDORA_TIMER_H