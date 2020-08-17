#include "worldgen.h"
#include "perlin.h"

int WorldGen_Generate(Vector2 *blocks, int width, int height, int seed)
{
	int i = 0;
	for (int x = 0; x < (width / 16); x++) {
		int maxY = (int)(Perlin_Get2d((double)x / 10, 0, 0.5, 4, seed) * 100);
		for (int y = maxY / 16; y < (height / 16); y++) {
			blocks[i] = (struct Vector2) { (float) x * 16, (float) y * 16 };
			i++;
		}
	}

	return i;
}

void WorldGen_RenderVisibleBlocks(Texture2D dirt, Vector2 *blocks, int blocksAmount, Vector2 pos, int width, int height)
{
	float rightOffset = (pos.x + (float) width / 2.0f) + 40.0f;
	float leftOffset = (pos.x - (float) width / 2.0f) - 40.0f;
	float bottomOffset = (pos.y + (float) height / 2.0f) + 40.0f;
	float topOffset = (pos.y - (float) height / 2.0f) - 40.0f;

	for (int i = 0; i < blocksAmount; i++) {
		Vector2 tmpBlock = blocks[i];
		if (tmpBlock.x > rightOffset || tmpBlock.x < leftOffset || tmpBlock.y > bottomOffset || tmpBlock.y < topOffset)
			continue;

		DrawTextureRec(dirt, (struct Rectangle) {40, 100, 16, 16}, tmpBlock, WHITE);
	}
}