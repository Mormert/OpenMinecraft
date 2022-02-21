#pragma once

#include "Camera.h"
#include "BufferBlockData.h"

#include <unordered_map>
#include "PairHash.h"

class BlockRenderer
{
public:

	BlockRenderer(const Camera &camera);
	~BlockRenderer();

	void RenderAllBufferedChunks();

	void BufferChunk(int x, int z, const BlockDataVector &blockDataVector);
	void RemoveChunk(int x, int z);

    void SetProjectionMatrix(glm::mat4 p);

private:

	struct BufferedChunk
	{
		unsigned int gfxBuffer; // id on the GPU
		unsigned int amount;	// amount of blocks
	};

    glm::mat4 projectionMatrix;

	const Camera &mainCamera;

	// Using boost hash function for <int, int> pair as a key for the map for direct access to chunks
	std::unordered_map<std::pair<int,int>, BufferedChunk, pair_hash> chunkInstanceBuffers;

	unsigned int VAO, VBO, texture;

};