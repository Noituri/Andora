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

  Chunk tmp_chunk;
  for (int x = 0; x < (w / kBlockLen); x++) {
    if (x % kChunkWidth == 0) {
      tmp_chunk.pos_x_ = x * 16;

      if (x != 0) {
        tmp_chunk.name_ =
            "chunk" + std::to_string(terrain.chunks.size()) + ".data";
        tmp_chunk.Write();
        terrain.chunks.emplace_back(tmp_chunk);
        tmp_chunk.blocks_.clear();
      }
    }
    int maxY = perlin::Get2D(x / 10, 0, 0.5, 4, s) * 100;
    for (int y = maxY / kBlockLen; y < h / kBlockLen; y++) {
      tmp_chunk.blocks_.emplace_back(
          raylib::Vector2{x * static_cast<float>(kBlockLen),
                          y * static_cast<float>(kBlockLen)});
    }
  }

  std::cout << "Generated " << terrain.chunks.size() << " chunks" << std::endl;
  registry_.emplace<comp::Terrain>(entity, terrain);
}

void EntitiesHandler::UpdateNormal() { physics_.NextStep(); }

void EntitiesHandler::UpdateRender() {
  sys::RenderTerrain(registry_, physics_);
  RenderCollisions(physics_);
}
}  // namespace andora