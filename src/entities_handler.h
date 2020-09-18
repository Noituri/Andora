#pragma once

#include <entt.hpp>

#include "physics.h"
#include "utils.h"

namespace andora {
class EntitiesHandler {
 public:
  EntitiesHandler();
  void CreateTerrain(int w, int h, int s);
  void CreatePlayer(float x, float y);
  void UpdateNormal();
  void UpdateRender();

 private:
  entt::registry registry_;
  Physics physics_;
};
}  // namespace andora