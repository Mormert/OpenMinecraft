#pragma once

#include "BufferBlockData.h"

#include <cstdint>

constexpr unsigned int chunk_size{ 10 };

class Chunk
{
public:

	Chunk(int chunkX, int chunkZ);

	void SetBlockLocal(int x, int y, int z, uint8_t block_id);
	void SetBlockGlobal(int chunkX, int chunkZ, int x, int y, int z, unsigned int block_id);

	void GenerateBuffer();

	const BlockDataVector &GetBlockDataVector();


private:

	int chunk_x, chunk_z;
	bool IsBlockVisible(int x, int y, int z);

	// Holds an id of the block
	uint8_t blocks[chunk_size][chunk_size][chunk_size];
	BlockDataVector blockDataVector;
};

