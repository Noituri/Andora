#include "systems.h"

#include <iostream>

#include "components.h"
#include "utils.h"

namespace andora::sys {
void RenderTerrain(entt::registry& registry, Physics& physics) {
  auto view = registry.view<comp::Terrain>();
  for (auto entity : view) {
    comp::Terrain& terrain = view.get<comp::Terrain>(entity);
    raylib::Vector2 camera_pos = main_camera.target;
    float right_offset =
        (camera_pos.x + kScreenWidth / 2.0f) + kChunkWidth * kBlockLen;
    float left_offset = (camera_pos.x - kScreenWidth / 2.0f) - 40.0f;
    float bottom_offset = (camera_pos.y + kScreenHeight / 2.0f) + 40.0f;
    float top_offset = (camera_pos.y - kScreenHeight / 2.0f) - 40.0f;

    for (int i = 0; i < terrain.chunks_created; i++) {
      int pos_x = (i + 1) * kChunkWidth * kBlockLen;
      if (pos_x > right_offset || pos_x < left_offset) continue;
      auto compare = [&](Chunk ch) { return ch.id_ == i; };
      if (std::any_of(terrain.chunks.begin(), terrain.chunks.end(), compare))
        continue;

      std::string tmp_name = "chunk" + std::to_string(i) + ".data";
      Chunk tmp_chunk(tmp_name.c_str(), i);
      for (const auto& block : tmp_chunk.blocks_) {
        if (block.y > bottom_offset || block.y < top_offset) continue;
        CreateBlockCollisions(physics, tmp_chunk, block);
      }

      terrain.chunks.emplace_back(tmp_chunk);
      std::cout << "CHUNK " << i << " LOADED " << std::endl;
    }
    // TODO: Load and remove chunks in async
    // TODO: Create new colliders if y axis changes
    for (auto chunk = terrain.chunks.begin(); chunk != terrain.chunks.end();) {
      if (chunk->pos_x_ > right_offset || chunk->pos_x_ < left_offset) {
        auto it = std::remove_if(physics.bodies_.begin(), physics.bodies_.end(),
                                 [&](const std::unique_ptr<Body>& b) {
                                   return b->owner_ == chunk->id_;
                                 });
        physics.bodies_.erase(it, physics.bodies_.end());
        chunk->Write();
        terrain.chunks.erase(chunk);
        continue;
      }

      for (const auto& block : chunk->blocks_) {
        if (block.y > bottom_offset || block.y < top_offset) continue;

        DrawTextureRec(dirt_txt, {40, 100, 16, 16}, block, WHITE);
      }
      chunk++;
    }
  }
}  // namespace andora::sys
}  // namespace andora::sys