#include "BlockRenderer.h"

#include <glad/glad.h>

#include "stb_image.h"

#include <cmath>
#include <iostream>

BlockRenderer::BlockRenderer(const Camera &camera) : mainCamera{ camera }
{

	// Setup texture
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// Clear pixels using GL_NEAREST
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Load and generate the texture
	int width, height, nrChannels;
	unsigned char *data = stbi_load("terrain.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture terrain.png" << std::endl;
	}
	stbi_image_free(data);


	constexpr float textureBias = 0.0005f; // Used to prevent sampling from the tiles next to current tile
	constexpr float one = (1.0f / 16.0f) - textureBias;
	constexpr float zero = 0.0f + textureBias;

	constexpr float vertices[] = {
		// Vertex position,		 Texture coordinates		// Face id
		-0.5f, -0.5f, -0.5f,	 one,		one,			1.0f, // Front
		 0.5f, -0.5f, -0.5f,	 zero,		one,			1.0f,
		 0.5f,  0.5f, -0.5f,	 zero,		zero,			1.0f,
		 0.5f,  0.5f, -0.5f,	 zero,		zero,			1.0f,
		-0.5f,  0.5f, -0.5f,	 one,		zero,			1.0f,
		-0.5f, -0.5f, -0.5f,	 one,		one,			1.0f,

		-0.5f, -0.5f,  0.5f,	 one,		one,			4.0f, // Side
		 0.5f, -0.5f,  0.5f,	 zero,		one,			4.0f,
		 0.5f,  0.5f,  0.5f,	 zero,		zero,			4.0f,
		 0.5f,  0.5f,  0.5f,	 zero,		zero,			4.0f,
		-0.5f,  0.5f,  0.5f,	 one,		zero,			4.0f,
		-0.5f, -0.5f,  0.5f,	 one,		one,			4.0f,

		-0.5f,  0.5f,  0.5f,	 zero,		zero,			4.0f, // Side
		-0.5f,  0.5f, -0.5f,	 one,		zero,			4.0f,
		-0.5f, -0.5f, -0.5f,	 one,		one,			4.0f,
		-0.5f, -0.5f, -0.5f,	 one,		one,			4.0f,
		-0.5f, -0.5f,  0.5f,	 zero,		one,			4.0f,
		-0.5f,  0.5f,  0.5f,	 zero,		zero,			4.0f,

		 0.5f,  0.5f,  0.5f,	 zero,		zero,			4.0f, // Side
		 0.5f,  0.5f, -0.5f,	 one,		zero,			4.0f,
		 0.5f, -0.5f, -0.5f,	 one,		one,			4.0f,
		 0.5f, -0.5f, -0.5f,	 one,		one,			4.0f,
		 0.5f, -0.5f,  0.5f,	 zero,		one,			4.0f,
		 0.5f,  0.5f,  0.5f,	 zero,		zero,			4.0f,

		-0.5f, -0.5f, -0.5f,	 zero,		zero,			3.0f, // Bottom
		 0.5f, -0.5f, -0.5f,	 one,		zero,			3.0f,
		 0.5f, -0.5f,  0.5f,	 one,		one,			3.0f,
		 0.5f, -0.5f,  0.5f,	 one,		one,			3.0f,
		-0.5f, -0.5f,  0.5f,	 zero,		one,			3.0f,
		-0.5f, -0.5f, -0.5f,	 zero,		zero,			3.0f,

		-0.5f,  0.5f, -0.5f,	 zero,		zero,			2.0f, // Top
		 0.5f,  0.5f, -0.5f,	 one,		zero,			2.0f,
		 0.5f,  0.5f,  0.5f,	 one,		one,			2.0f,
		 0.5f,  0.5f,  0.5f,	 one,		one,			2.0f,
		-0.5f,  0.5f,  0.5f,	 zero,		one,			2.0f,
		-0.5f,  0.5f, -0.5f,	 zero,		zero,			2.0f
	};

	// Setup vertex array object
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Vertex position attribute x, y, z
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Texture coords attribute u, v
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Face id (works just like normal vectors but takes less space)
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glEnableVertexAttribArray(3);	// 3 includes the block's x, y, z, rot
	glEnableVertexAttribArray(4);	// 4 includes the block's different textures on the sides

	// Only go to next attribute on next instance draw
	glVertexAttribDivisor(3, 1);	
	glVertexAttribDivisor(4, 1);

	glBindVertexArray(0);

}

BlockRenderer::~BlockRenderer()
{

	for (auto bufferedChunk : chunkInstanceBuffers)
	{
		glDeleteBuffers(1, &bufferedChunk.second.gfxBuffer);
	}

	glDeleteBuffers(1, &VBO);

	glDeleteVertexArrays(1, &VAO);
	glDeleteTextures(1, &texture);
}

void BlockRenderer::RenderAllBufferedChunks()
{
	glBindVertexArray(VAO);
	for (auto bufferedChunk : chunkInstanceBuffers)
	{
		const int chunkX = bufferedChunk.first.first;
		const int chunkZ = bufferedChunk.first.second;

		if (abs((chunkX*24) - mainCamera.Position.x) < 200.0f && abs((chunkZ*24) - mainCamera.Position.z) < 200.0f)
		{
			glBindBuffer(GL_ARRAY_BUFFER, bufferedChunk.second.gfxBuffer);

			// Change vertex attribute pointers to this instance buffer's data
			glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); // x, y, z, rot
			glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(4 * sizeof(float))); // 4 different texture coordinates
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glDrawArraysInstanced(GL_TRIANGLES, 0, 36, bufferedChunk.second.amount);
		}
	}
}

void BlockRenderer::BufferChunk(int x, int z, const BlockDataVector &blockDataVector)
{
	if (blockDataVector.empty()) {
		return;
	}

	std::unordered_map<std::pair<int, int>, BufferedChunk,
		boost::hash<std::pair<int, int>>>::const_iterator got = chunkInstanceBuffers.find(std::make_pair(x,z));

	// Has this chunk's buffers already been created?
	if (got == chunkInstanceBuffers.end())
	{
		auto inserted = chunkInstanceBuffers.insert(std::make_pair(std::make_pair(x, z), BufferedChunk{ 0, blockDataVector.size() }));
		glGenBuffers(1, &inserted.first->second.gfxBuffer);
	}

	glBindBuffer(GL_ARRAY_BUFFER, chunkInstanceBuffers.at(std::make_pair(x, z)).gfxBuffer);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(BlockData) * blockDataVector.size(), &blockDataVector[0], GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void BlockRenderer::RemoveChunk(int x, int z)
{
	glDeleteBuffers(1, &chunkInstanceBuffers.at(std::make_pair(x, z)).gfxBuffer);
	chunkInstanceBuffers.erase(std::make_pair(x, z));
}