#include "systems.h"

#include "components.h"
#include "utils.h"

namespace andora::sys {
bool colliders_generated = false;  // TODO: Remove this
void RenderTerrain(entt::registry& registry, Physics& physics) {
  // auto view = registry.view<comp::Terrain>();
  // for (auto entity : view) {
  // comp::Terrain& terrain = view.get<comp::Terrain>(entity);
  // raylib::Vector2 camera_pos = main_camera.target;

  // float right_offset =
  //     (camera_pos.x + kScreenWidth / 2.0f) + kChunkWidth * kBlockLen;
  // float left_offset = (camera_pos.x - kScreenWidth / 2.0f) - 40.0f;
  // float bottom_offset = (camera_pos.y + kScreenHeight / 2.0f) + 40.0f;
  // float top_offset = (camera_pos.y - kScreenHeight / 2.0f) - 40.0f;

  // for (const auto& chunk : terrain.chunks) {
  //   if (chunk.pos_x > right_offset || chunk.pos_x < left_offset) continue;

  //   for (const auto& block : chunk.blocks) {
  //     if (block.y > bottom_offset || block.y < top_offset) continue;

  //     DrawTextureRec(dirt_txt, {40, 100, 16, 16}, block, WHITE);
  //     if (!colliders_generated) CreateBlockCollisions(physics, chunk,
  //     block);
  //   }
  // }
  // colliders_generated = true;
  // }
}
}  // namespace andora::sys