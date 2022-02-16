#include "World.h"
#include "BlockLoader.h"

#include <iostream>

World::World(int seed, int initialChunksXY, BlockRenderer &_blockRenderer)
	: worldGenerator{seed}, blockRenderer{_blockRenderer}
{

    g_world = this;

	BlockLoader::LoadBlocksFromFile("data/blockdata.txt");

    // Generate all chunks first, because a chunk generation may edit a neighbouring chunk
	for (int i = -initialChunksXY; i < initialChunksXY; i++)
	{
		for (int j = -initialChunksXY; j < initialChunksXY; j++)
		{
			Chunk *chunk = new Chunk(i, j);
			auto insertedChunk = worldChunks.insert(std::make_pair(std::make_pair(i, j), chunk));
		}
	}

    for(auto&& chunk : worldChunks)
    {
        // Generate terrain
        worldGenerator.GenerateChunk(chunk.second);

        // Create GFX buffer
        chunk.second->GenerateBuffer();
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

    if(y < 0 || y > 24)
    {
        return -1;
    }

    glm::ivec3 chunkSpaceCoords;
    std::pair<int,int> chunkCoords;

    std::tie(chunkSpaceCoords, chunkCoords) = GetLocalChunkCoordinates(x,y,z);

    if(chunkSpaceCoords.y >= chunk_size)
    {
        return 0;
    }

    Chunk* chunk;

    auto iter = worldChunks.find(chunkCoords);

    if(iter != worldChunks.end())
    {
        chunk = iter->second;
    }else{
        return -1;
    }

    return chunk->GetBlock(chunkSpaceCoords.x, chunkSpaceCoords.y, chunkSpaceCoords.z);
}

Chunk* World::SetBlockAtWorldPosition(int x, int y, int z, uint8_t block_id, bool updateGfxBuffer)
{
    if(y >= 24)
    {
        return nullptr;
    }

    glm::ivec3 chunkSpaceCoords;
    std::pair<int,int> chunkCoords;

    std::tie(chunkSpaceCoords, chunkCoords) = GetLocalChunkCoordinates(x,y,z);

    Chunk* chunk = nullptr;

    auto iter = worldChunks.find(chunkCoords);

    if(iter != worldChunks.end())
    {
        chunk = worldChunks.at(chunkCoords);
    }else
    {
        return nullptr;
    }

    chunk->SetChunkBlock(chunkSpaceCoords.x, chunkSpaceCoords.y, chunkSpaceCoords.z, block_id);

    if (updateGfxBuffer)
    {
        chunk->GenerateBuffer();
        blockRenderer.BufferChunk(chunkX, chunkZ, chunk->GetBlockDataVector());
    }

    return chunk;
}

std::tuple<glm::ivec3, std::pair<int,int>> World::GetLocalChunkCoordinates(int x, int y, int z) {

    chunkX = x / chunk_size;
    chunkZ = z / chunk_size;

    if(x < 0)
    {
        chunkX = (x+1) / chunk_size;
        chunkX--;
    }

    if(z < 0)
    {
        chunkZ = (z+1) / chunk_size;
        chunkZ--;
    }

    localBlockX = x % chunk_size;

    if(x < 0)
    {
        localBlockX = (x+1) % chunk_size;
        localBlockX = chunk_size + localBlockX-1;
    }

    localBlockZ = z % chunk_size;

    if(z < 0)
    {
        localBlockZ = (z+1) % chunk_size;
        localBlockZ = chunk_size + localBlockZ-1;
    }

    return {glm::ivec3{localBlockX, y, localBlockZ}, std::make_pair(chunkX, chunkZ)};
}


/*
int World::GetBlockAtWorldPosition(int x, int y, int z)
{
    if(y >= chunk_size)
    {
        return 0;
    }

	chunkX = x / chunk_size;
	chunkZ = z / chunk_size;

    if(x < 0)
    {
        chunkX = (x+1) / chunk_size;
        chunkX--;
    }

    if(z < 0)
    {
        chunkZ = (z+1) / chunk_size;
        chunkZ--;
    }

	try {
		Chunk *chunk = worldChunks.at(std::make_pair(chunkX, chunkZ));

		localBlockX = x % chunk_size;

        if(x < 0)
        {
            localBlockX = (x+1) % chunk_size;
            localBlockX = chunk_size + localBlockX-1;
        }

        localBlockZ = z % chunk_size;

        if(z < 0)
        {
            localBlockZ = (z+1) % chunk_size;
            localBlockZ = chunk_size + localBlockZ-1;
        }

		return chunk->GetBlock(localBlockX, y, localBlockZ);
	}
	catch(const std::out_of_range e){
		return -1; // not found
	}
}
 */