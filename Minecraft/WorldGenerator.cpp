#include "WorldGenerator.h"

#include <cmath>
#include <iostream>

WorldGenerator::WorldGenerator(int seed) : noise{seed}
{
	noise.SetNoiseType(FastNoise::Perlin);
}

void WorldGenerator::GenerateChunk(Chunk *chunk)
{
	for (int x = 0; x < chunk_size; x += 1)
	{
		for (int z = 0; z < chunk_size; z += 1)
		{

			int blockGlobalSpaceX = chunk->GetChunkX() * chunk_size + x;
			int blockGlobalSpaceZ = chunk->GetChunkZ() * chunk_size + z;

			float terrainConstant{ 2.5f };
			int height = static_cast<int>((noise.GetNoise(blockGlobalSpaceX * terrainConstant, blockGlobalSpaceZ * terrainConstant) + 1.0f) * 12.0f);
			for (int y = 0; y < height; y += 1)
			{
				chunk->SetChunkBlock(x, y, z, 1);

				if (y < 6)
				{
					chunk->SetChunkBlock(x, y, z, 3);
				}
				if (y < 2)
				{
					chunk->SetChunkBlock(x, y, z, 17);
				}
				if (y >= height - 1)
				{
					chunk->SetChunkBlock(x, y, z, 2);
				}
			}
		}
	}
}