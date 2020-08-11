#include "Chunk.h"

#include "BlockLoader.h"

#include <cassert>
#include <iostream>


Chunk::Chunk(int chunkX, int chunkZ)
{
	chunk_x = chunkX;
	chunk_z = chunkZ;
}

const int Chunk::GetChunkX()
{
	return chunk_x;
}

const int Chunk::GetChunkZ()
{
	return chunk_z;
}

void Chunk::SetChunkBlock(int x, int y, int z, uint8_t block_id)
{
	assert(x >= 0 && x < chunk_size);
	assert(y >= 0 && y < chunk_size);
	assert(z >= 0 && z < chunk_size);

	blocks[x][y][z] = block_id;
}

bool Chunk::IsBlockVisible(int x, int y, int z)
{
	if (x == (chunk_size-1) || x == 0
		|| y == (chunk_size-1) || y == 0
		|| z == (chunk_size-1) || z == 0) {
		return true;
	}

	if (blocks[x + 1][y][z] == 0
		|| blocks[x - 1][y][z] == 0
		|| blocks[x][y + 1][z] == 0
		|| blocks[x][y - 1][z] == 0
		|| blocks[x][y][z + 1] == 0
		|| blocks[x][y][z - 1] == 0)
	{
		return true;
	}

	return false;
}

void Chunk::GenerateBuffer()
{
	blockDataVector.clear();
	for (int x = 0; x < chunk_size; x++)
	{
		for (int y = 0; y < chunk_size; y++)
		{
			for (int z = 0; z < chunk_size; z++)
			{
				if (IsBlockVisible(x, y, z) && blocks[x][y][z] != 0) {

					BlockFaceData blockFaceData = BlockLoader::GetBlockFaceData(blocks[x][y][z]);
					blockDataVector.push_back(BlockData{
					float(x + chunk_size * chunk_x),
					float(y),
					float(z + chunk_size * chunk_z),
					0.0f, // rot
					blockFaceData[0],
					blockFaceData[1],
					blockFaceData[2],
					blockFaceData[3]
						});
				}
			}
		}
	}
}

const BlockDataVector &Chunk::GetBlockDataVector()
{
	return blockDataVector;
}
