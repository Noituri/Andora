//
// Created by mikol on 8/17/2020.
//

#include <raylib.h>

#ifndef ANDORA_WORLDGEN_H
#define ANDORA_WORLDGEN_H

int WorldGen_Generate(Vector2 *blocks, int width, int height, int seed);
void WorldGen_RenderVisibleBlocks(Texture2D dirt, Vector2 *blocks, int blocksAmount, Vector2 pos, int width, int height);

#endif //ANDORA_WORLDGEN_H
