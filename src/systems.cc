#include "systems.h"

#include <iostream>

#include "components.h"
#include "utils.h"

namespace andora::sys {
bool colliders_generated = false;  // TODO: Remove this
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
        int id = CreateBlockCollisions(physics, tmp_chunk, block);
        if (id != -1) {
          tmp_chunk.colliders_.emplace_back(id);
        }
      }
      terrain.chunks.emplace_back(tmp_chunk);
      std::cout << "CHUNK " << i << " LOADED " << std::endl;
    }
    for (auto chunk = terrain.chunks.begin(); chunk != terrain.chunks.end();) {
      if (chunk->pos_x_ > right_offset || chunk->pos_x_ < left_offset) {
        chunk->Write();
        for (const auto& c : chunk->colliders_) {
          physics.RemoveBody(c);
        }
        terrain.chunks.erase(chunk);
        std::cout << "CHUNK " << chunk->id_ << " UNLOADED " << std::endl;
        continue;
      }

      for (const auto& block : chunk->blocks_) {
        if (block.y > bottom_offset || block.y < top_offset) continue;

        DrawTextureRec(dirt_txt, {40, 100, 16, 16}, block, WHITE);
        // if (!colliders_generated) CreateBlockCollisions(physics, chunk,
        // block);
      }
      chunk++;
    }
    colliders_generated = true;
  }
}  // namespace andora::sys
}  // namespace andora::sys