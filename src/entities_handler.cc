#include "entities_handler.h"

#include <iostream>

#include "components.h"
#include "perlin.h"
#include "utils.h"

namespace andora {
void EntitiesHandler::CreateTerrain(int w, int h, int s) {
  auto entity = registry_.create();
  comp::Terrain terrain;
  terrain.width = w;
  terrain.height = h;
  terrain.seed = s;

  Chunk tmp_chunk;
  for (int x = 0; x < (w / kBlockLen); x++) {
    if (x % kChunkWidth == 0) {
      tmp_chunk.pos_x = x * 16;

      if (x != 0) {
        terrain.chunks.emplace_back(tmp_chunk);
        tmp_chunk.blocks.clear();
      }
    }
    int maxY = perlin::Get2D(x / 10, 0, 0.5, 4, s);
    for (int y = maxY / kBlockLen; y < h / kBlockLen; y++) {
      tmp_chunk.blocks.emplace_back(
          raylib::Vector2{x * static_cast<float>(kBlockLen),
                          y * static_cast<float>(kBlockLen)});
    }
  }

  std::cout << "Generated " << terrain.chunks.size() << " chunks" << std::endl;
  registry_.emplace<comp::Terrain>(entity, terrain);
}
}  // namespace andora