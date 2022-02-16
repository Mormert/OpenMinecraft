#include "WorldGenerator.h"
#include "World.h"

#include <cmath>
#include <iostream>

WorldGenerator::WorldGenerator(int seed) : noise{seed} {
    noise.SetNoiseType(FastNoise::Perlin);
}

void WorldGenerator::GenerateChunk(Chunk *chunk) {
    for (int x = 0; x < chunk_size; x += 1) {
        for (int z = 0; z < chunk_size; z += 1) {

            int blockGlobalSpaceX = chunk->GetChunkX() * chunk_size + x;
            int blockGlobalSpaceZ = chunk->GetChunkZ() * chunk_size + z;

            int chunkX = chunk->GetChunkX();
            int chunkZ = chunk->GetChunkZ();

            float terrainConstant{2.5f};
            int height = static_cast<int>(
                    (noise.GetNoise(blockGlobalSpaceX * terrainConstant, blockGlobalSpaceZ * terrainConstant) + 1.0f) *
                    12.0f);
            for (int y = 0; y < height; y += 1) {
                chunk->SetChunkBlock(x, y, z, 1);

                if (y < 6) {
                    chunk->SetChunkBlock(x, y, z, 3);
                }
                if (y < 2) {
                    chunk->SetChunkBlock(x, y, z, 17);
                }
                if (y >= height - 1) {
                    chunk->SetChunkBlock(x, y, z, 2);
                }
            }

            if (height < 15) {
                double val = (double) rand() / RAND_MAX;
                if (val < 0.01) {
                    // generate tree
                    for (int i = 0; i < 5; i++) {
                        chunk->SetChunkBlock(x, height + i, z, 21);
                    }
                    for (int i = -3; i < 3; i++) {
                        for (int j = 0; j < 3; j++) {
                            for (int k = -3; k < 3; k++) {
                                // Use World class here, because we need the fact that we might change a neighbouring chunk.
                                World::g_world->SetBlockAtWorldPosition(i + x + chunkX * chunk_size, height + j + 5,
                                                                        k + z + chunkZ * chunk_size, 52, false);
                            }
                        }
                    }
                    for (int i = -2; i < 2; i++) {
                        for (int j = -2; j < 2; j++) {

                            World::g_world->SetBlockAtWorldPosition(i + x + chunkX * chunk_size, height + 3 + 5,
                                                                    j + z + chunkZ * chunk_size, 52, false);
                        }
                    }
                    for (int i = -1; i < 1; i++) {
                        for (int j = -1; j < 1; j++) {

                            World::g_world->SetBlockAtWorldPosition(i + x + chunkX * chunk_size, height + 3 + 5 + 1,
                                                                    j + z + chunkZ * chunk_size, 52, false);
                        }
                    }

                }
            }
        }
    }
}