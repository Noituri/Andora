#include "entities_handler.h"

#include <iostream>

#include "chunk_generated.h"
#include "components.h"
#include "perlin.h"
#include "schema_handler.h"
#include "systems.h"
#include "utils.h"

namespace andora {
EntitiesHandler::EntitiesHandler() : physics_(kTargetFPS, {0.0f, 9.0f}) {
  physics_.CreateBody({{720, -100}, 16, 16, 5});
}

void EntitiesHandler::CreateTerrain(int w, int h, int s) {
  entt::entity entity = registry_.create();
  comp::Terrain terrain;
  terrain.width = w;
  terrain.height = h;
  terrain.seed = s;
  terrain.chunks_created = 0;

  Chunk tmp_chunk;
  for (int x = 0; x < (w / kBlockLen); x++) {
    if (x % kChunkWidth == 0 && x != 0) {
      tmp_chunk.pos_x_ = x * kBlockLen;
      tmp_chunk.name_ =
          "chunk" + std::to_string(terrain.chunks_created) + ".data";
      tmp_chunk.Write();
      tmp_chunk.blocks_.clear();
      terrain.chunks_created++;
    }
    int maxY = perlin::Get2D(x / 10, 0, 0.5, 4, s) * 100;
    for (int y = maxY / kBlockLen; y < h / kBlockLen; y++) {
      tmp_chunk.blocks_.emplace_back(
          raylib::Vector2{x * static_cast<float>(kBlockLen),
                          y * static_cast<float>(kBlockLen)});
    }
  }

  std::cout << "Generated " << terrain.chunks_created << " chunks" << std::endl;
  registry_.emplace<comp::Terrain>(entity, terrain);
}

void EntitiesHandler::UpdateNormal() { physics_.NextStep(); }

void EntitiesHandler::UpdateRender() {
  sys::RenderTerrain(registry_, physics_);
  RenderCollisions(physics_);
}
}  // namespace andora