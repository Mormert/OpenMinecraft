#pragma once

#include <glm/glm.hpp>

#include <boost/functional/hash.hpp>
#include <unordered_map>

struct BufferBlockData {
	// x, y, z, rotation, face0_id, face1_id, face2_id, face3_id (faces should range 0 - 255)
	float data[8];
};

class BlockRenderer
{
public:

	BlockRenderer();
	~BlockRenderer();

	void RenderAllBufferedChunks();

	void BufferChunk(int x, int z, BufferBlockData *data, unsigned int amount);
	void RemoveChunk(int x, int z);

private:

	struct BufferedChunk
	{
		unsigned int gfxBuffer; // id on the GPU
		unsigned int amount;	// amount of blocks
	};

	// Using boost hash function for <int, int> pair as a key for the map for direct access to chunks
	std::unordered_map<std::pair<int,int>, BufferedChunk, boost::hash<std::pair<int, int>>> chunkInstanceBuffers;

	unsigned int VAO, VBO, texture;

};