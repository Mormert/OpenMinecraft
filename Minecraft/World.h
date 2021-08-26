#pragma once


#include "BlockRenderer.h"
#include "WorldGenerator.h"
#include "Chunk.h"

#include <boost/functional/hash.hpp>
#include <unordered_map>

class World
{
public:
	World(int seed, int initialChunksXY, BlockRenderer &_blockRenderer);
	~World();

	void BufferChunksToBlockRenderer();
	int GetBlockAtWorldPosition(int x, int y, int z); 	// 0 is air, -1 is not found

	// Sets a block at a world position if the chunk for that position exists
	void SetBlockAtWorldPosition(int x, int y, int z, uint8_t block_id, bool updateGfxBuffer = true);

private:
	std::unordered_map<std::pair<int, int>, Chunk*, boost::hash<std::pair<int, int>>> worldChunks;
	WorldGenerator worldGenerator;

	BlockRenderer &blockRenderer;
};