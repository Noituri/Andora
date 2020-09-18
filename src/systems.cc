#include "systems.h"

#include <iostream>
#include <thread>

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
      terrain.chunks.emplace_back(tmp_chunk);

      std::cout << "CHUNK " << i << " LOADED " << std::endl;
    }

    for (auto chunk = terrain.chunks.begin(); chunk != terrain.chunks.end();) {
      if (chunk->pos_x_ > right_offset || chunk->pos_x_ < left_offset) {
        chunk->Write();
        std::thread thread_obj(
            [](Physics& p, int chunk_id) {
              std::lock_guard<std::mutex> guard(p.bodies_mutex_);
              auto it = std::remove_if(p.bodies_.begin(), p.bodies_.end(),
                                       [&](const std::unique_ptr<Body>& b) {
                                         return b->owner_ == chunk_id;
                                       });
              p.bodies_.erase(it, p.bodies_.end());
            },
            std::ref(physics), chunk->id_);

        thread_obj.detach();
        terrain.chunks.erase(chunk);
        std::cout << "CHUNK " << chunk->id_ << " UNLOADED " << std::endl;
        continue;
      }

      for (auto& block : chunk->blocks_) {
        if (block.pos.y > bottom_offset || block.pos.y < top_offset) {
          if (block.has_collider && block.loaded_collider) {
            std::lock_guard<std::mutex> guard(physics.bodies_mutex_);
            auto it =
                std::remove_if(physics.bodies_.begin(), physics.bodies_.end(),
                               [&](const std::unique_ptr<Body>& b) {
                                 return b->position_ == block.pos;
                               });
            physics.bodies_.erase(it, physics.bodies_.end());
            block.loaded_collider = false;
          }
          continue;
        }

        if (block.has_collider && !block.loaded_collider) {
          physics.CreateBody({block.pos, kBlockLen, kBlockLen, 0.0f})->owner_ =
              chunk->id_;
          block.loaded_collider = true;
        }

        DrawTextureRec(dirt_txt, {40, 100, 16, 16}, block.pos, WHITE);
      }
      chunk++;
    }
  }
}  // namespace andora::sys
}  // namespace andora::sys