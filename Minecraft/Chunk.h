#pragma once

#include "BufferBlockData.h"

#include <cstdint>

constexpr int chunk_size{ 24 };

class Chunk
{
public:

	Chunk(int chunkX, int chunkZ);

	const int GetChunkX();
	const int GetChunkZ();


	void SetChunkBlock(int x, int y, int z, uint8_t block_id);
	uint8_t GetBlock(int x, int y, int z);

	void GenerateBuffer();

	const BlockDataVector &GetBlockDataVector();


private:

	int chunk_x, chunk_z;
	bool IsBlockVisible(int x, int y, int z);

	// Holds an id of the block
	uint8_t blocks[chunk_size][chunk_size][chunk_size] = {0};
	BlockDataVector blockDataVector;
};

