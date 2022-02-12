#include "World.h"
#include "BlockLoader.h"

#include <iostream>

World::World(int seed, int initialChunksXY, BlockRenderer &_blockRenderer)
	: worldGenerator{seed}, blockRenderer{_blockRenderer}
{

	BlockLoader::LoadBlocksFromFile("data/blockdata.txt");

	for (int i = -initialChunksXY; i < initialChunksXY; i++)
	{
		for (int j = -initialChunksXY; j < initialChunksXY; j++)
		{
			Chunk *chunk = new Chunk(i, j);
			auto insertedChunk = worldChunks.insert(std::make_pair(std::make_pair(i, j), chunk));

			// Generate terrain
			worldGenerator.GenerateChunk(chunk);

			// Create GFX buffer
			chunk->GenerateBuffer();
		}
	}
}

World::~World()
{
	for (auto unordered_map_chunk : worldChunks)
	{
		delete unordered_map_chunk.second;
	}
	worldChunks.clear();
}

void World::BufferChunksToBlockRenderer()
{
	for (auto unordered_map_chunk : worldChunks) {
		blockRenderer.BufferChunk(
			unordered_map_chunk.first.first,					// x
			unordered_map_chunk.first.second,					// y
			unordered_map_chunk.second->GetBlockDataVector());	// data
	}
	
}

int World::GetBlockAtWorldPosition(int x, int y, int z)
{
	const int chunkX = x / chunk_size;
	const int chunkZ = z / chunk_size;

	try {
		Chunk *chunk = worldChunks.at(std::make_pair(chunkX, chunkZ));

		// note: it is something wrong with y, should be z?

		const int localBlockX = x % chunk_size;
		const int localBlockY = y % chunk_size;

		return chunk->GetBlock(localBlockX, localBlockY, z);
	}
	catch(const std::out_of_range e){
		return -1; // not found
	}
}

void World::SetBlockAtWorldPosition(int x, int y, int z, uint8_t block_id, bool updateGfxBuffer)
{
	const int chunkX = x / chunk_size;
	const int chunkZ = z / chunk_size;

	try {
		Chunk *chunk = worldChunks.at(std::make_pair(chunkX, chunkZ));

		const int localBlockX = x % chunk_size;
		const int localBlockZ = z % chunk_size;

		chunk->SetChunkBlock(localBlockX, y, localBlockZ, block_id);

		if (updateGfxBuffer)
		{
			chunk->GenerateBuffer();
			blockRenderer.BufferChunk(chunkX, chunkZ, chunk->GetBlockDataVector());
		}
	}
	catch (const std::out_of_range e) {
		std::cerr << "Chunk for position " << x << ", " << y << ", " << z << " not generated\n";
	}
}