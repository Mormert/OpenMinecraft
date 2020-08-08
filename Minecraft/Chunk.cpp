#include "Chunk.h"

#include <cassert>

void Chunk::SetBlockLocal(int x, int y, int z, uint8_t block_id)
{
	assert(x >= 0, x <= chunk_size, y >= 0, y <= chunk_size, z >= 0, z <= chunk_size);

	blocks[x][y][z] = block_id;
}

void Chunk::SetBlockGlobal(int chunkX, int chunkZ, int globalX, int globalY, int globalZ, unsigned int block_id)
{
	const int localX = globalX - chunkX * chunk_size;
	const int localZ = globalZ - chunkZ * chunk_size;

	assert(localX >= 0, localX <= chunk_size, globalY >= 0, globalY <= chunk_size, localZ >= 0, localZ <= chunk_size);

	blocks[localX][globalY][localZ] = block_id;
}