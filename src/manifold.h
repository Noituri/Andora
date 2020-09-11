#ifndef ANDORA_MANIFOLD_H
#define ANDORA_MANIFOLD_H

#include "body.h"

namespace andora {
class Manifold {
 public:
  Manifold(Body& A, Body& B);
  void PositionalCorrection();
  void SolveCollision();
  bool AABBvsAABB();

 private:
  Body& A_;
  Body& B_;
  float penetration_;
  raylib::Vector2 normal_;
};
}  // namespace andora

#endif