#include "BlockRenderer.h"

#include <glad/glad.h>

#include "stb_image.h"

#include <iostream>

BlockRenderer::BlockRenderer()
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


	// Setup block buffers

	constexpr float vertices[] = {
		// Vertex position,		 Texture coordinates
		-0.5f, -0.5f, -0.5f,	 0 / 16.0f,		0 / 16.0f,
		 0.5f, -0.5f, -0.5f,	 1 / 16.0f,		0 / 16.0f,
		 0.5f,  0.5f, -0.5f,	 1 / 16.0f,		1 / 16.0f,
		 0.5f,  0.5f, -0.5f,	 1 / 16.0f,		1 / 16.0f,
		-0.5f,  0.5f, -0.5f,	 0 / 16.0f,		1 / 16.0f,
		-0.5f, -0.5f, -0.5f,	 0 / 16.0f,		0 / 16.0f,

		-0.5f, -0.5f,  0.5f,	 0 / 16.0f,		0 / 16.0f,
		 0.5f, -0.5f,  0.5f,	 1 / 16.0f,		0 / 16.0f,
		 0.5f,  0.5f,  0.5f,	 1 / 16.0f,		1 / 16.0f,
		 0.5f,  0.5f,  0.5f,	 1 / 16.0f,		1 / 16.0f,
		-0.5f,  0.5f,  0.5f,	 0 / 16.0f,		1 / 16.0f,
		-0.5f, -0.5f,  0.5f,	 0 / 16.0f,		0 / 16.0f,

		-0.5f,  0.5f,  0.5f,	 0 / 16.0f,		0 / 16.0f,
		-0.5f,  0.5f, -0.5f,	 1 / 16.0f,		0 / 16.0f,
		-0.5f, -0.5f, -0.5f,	 1 / 16.0f,		1 / 16.0f,
		-0.5f, -0.5f, -0.5f,	 1 / 16.0f,		1 / 16.0f,
		-0.5f, -0.5f,  0.5f,	 0 / 16.0f,		1 / 16.0f,
		-0.5f,  0.5f,  0.5f,	 0 / 16.0f,		0 / 16.0f,

		 0.5f,  0.5f,  0.5f,	 0 / 16.0f,		0 / 16.0f,
		 0.5f,  0.5f, -0.5f,	 1 / 16.0f,		0 / 16.0f,
		 0.5f, -0.5f, -0.5f,	 1 / 16.0f,		1 / 16.0f,
		 0.5f, -0.5f, -0.5f,	 1 / 16.0f,		1 / 16.0f,
		 0.5f, -0.5f,  0.5f,	 0 / 16.0f,		1 / 16.0f,
		 0.5f,  0.5f,  0.5f,	 0 / 16.0f,		0 / 16.0f,

		-0.5f, -0.5f, -0.5f,	 0 / 16.0f,		0 / 16.0f,
		 0.5f, -0.5f, -0.5f,	 1 / 16.0f,		0 / 16.0f,
		 0.5f, -0.5f,  0.5f,	 1 / 16.0f,		1 / 16.0f,
		 0.5f, -0.5f,  0.5f,	 1 / 16.0f,		1 / 16.0f,
		-0.5f, -0.5f,  0.5f,	 0 / 16.0f,		1 / 16.0f,
		-0.5f, -0.5f, -0.5f,	 0 / 16.0f,		0 / 16.0f,

		-0.5f,  0.5f, -0.5f,	 0 / 16.0f,		0 / 16.0f,
		 0.5f,  0.5f, -0.5f,	 1 / 16.0f,		0 / 16.0f,
		 0.5f,  0.5f,  0.5f,	 1 / 16.0f,		1 / 16.0f,
		 0.5f,  0.5f,  0.5f,	 1 / 16.0f,		1 / 16.0f,
		-0.5f,  0.5f,  0.5f,	 0 / 16.0f,		1 / 16.0f,
		-0.5f,  0.5f, -0.5f,	 0 / 16.0f,		0 / 16.0f
	};

	// Setup instance buffer used for storing the blocks to be rendered
	// in one single draw call
	glGenBuffers(1, &instanceBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, instanceBuffer);
	glBufferData(GL_ARRAY_BUFFER, 0, (void*)0, GL_DYNAMIC_DRAW); // Empty buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	// Setup vertex array object
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Vertex position attribute x, y, z
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Texture coords attribute u, v
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// World space position x, y, z, (and 4th variable holding block's id) w
	// used for instanced rendering. Note that this is using the instance buffer, not the VBO buffer.
	glBindBuffer(GL_ARRAY_BUFFER, instanceBuffer);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glVertexAttribDivisor(2, 1); // Only go to next attribute on next instance draw

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

}

BlockRenderer::~BlockRenderer()
{
	glDeleteBuffers(1, &instanceBuffer);
	glDeleteBuffers(1, &VBO);

	glDeleteVertexArrays(1, &VAO);
	glDeleteTextures(1, &texture);
}

void BlockRenderer::RenderBlocks()
{
	glBindVertexArray(VAO);
	glDrawArraysInstanced(GL_TRIANGLES, 0, 36, blocksCountRender);
}

void BlockRenderer::BufferBlocks(glm::vec4 *vec, unsigned int amount)
{

	amount = 1000000;

	glm::vec4 *instancingData = new glm::vec4[1000000];

	int index = 0;
	float offset = 0.1f;
	for (int y = -100; y < 100; y += 2)
	{
		for (int x = -100; x < 100; x += 2)
		{
			for (int z = -100; z < 100; z += 2)
			{
				glm::vec4 instancingDat;
				instancingDat.x = (float)x + offset;
				instancingDat.y = (float)y + offset;
				instancingDat.z = (float)z + offset;
				instancingDat.w = (rand() % 100) + 1;
				instancingData[index++] = instancingDat;
			}
		}
	}

	glBindBuffer(GL_ARRAY_BUFFER, instanceBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * amount, &instancingData[0], GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	delete[] instancingData;

	blocksCountRender = amount;
}