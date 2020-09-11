#pragma once

#include <entt.hpp>

namespace andora {
class EntitiesHandler {
 public:
  EntitiesHandler() = default;
  void CreateTerrain(int w, int h, int s);

 private:
  entt::registry registry_;
};
}  // namespace andora