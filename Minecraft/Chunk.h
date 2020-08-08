#pragma once

#include <cstdint>

constexpr unsigned int chunk_size{ 10 };

class Chunk
{
public:

	void SetBlockLocal(int x, int y, int z, uint8_t block_id);
	void SetBlockGlobal(int chunkX, int chunkZ, int x, int y, int z, unsigned int block_id);

private:
	// Holds an id of the block
	uint8_t blocks[chunk_size][chunk_size][chunk_size];
};

