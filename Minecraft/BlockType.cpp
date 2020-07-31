#include "BlockType.h"

#include <glad/glad.h>

#include <glm/glm.hpp>

#include <iostream>

#include "stb_image.h"

BlockType BlockType::blockTypeList[256] {};
unsigned int BlockType::TextureID{ 0 };
unsigned int BlockType::BlocksToRender{ 0 };
unsigned int BlockType::InstanceBuffer{ 0 };

void BlockType::Init(unsigned int id)
{
	int x = id % 16;
	int y = id / 16;

	x = 0;
	y = 0;

	float vertices[] = {
		-0.5f, -0.5f, -0.5f, x/16.0f,		y/16.0f,
		 0.5f, -0.5f, -0.5f, (x+1)/16.0f,	y/16.0f,
		 0.5f,  0.5f, -0.5f, (x+1)/16.0f,	(y+1)/16.0f,
		 0.5f,  0.5f, -0.5f, (x+1)/16.0f,	(y+1)/16.0f,
		-0.5f,  0.5f, -0.5f, x/16.0f,		(y+1)/16.0f,
		-0.5f, -0.5f, -0.5f, x/16.0f,		y / 16.0f,

		-0.5f, -0.5f,  0.5f, x / 16.0f,		y / 16.0f,
		 0.5f, -0.5f,  0.5f, (x + 1) / 16.0f,	y / 16.0f,
		 0.5f,  0.5f,  0.5f, (x + 1) / 16.0f,	(y + 1) / 16.0f,
		 0.5f,  0.5f,  0.5f, (x + 1) / 16.0f,	(y + 1) / 16.0f,
		-0.5f,  0.5f,  0.5f, x / 16.0f,		(y + 1) / 16.0f,
		-0.5f, -0.5f,  0.5f, x / 16.0f,		y / 16.0f,

		-0.5f,  0.5f,  0.5f, x / 16.0f,		y / 16.0f,
		-0.5f,  0.5f, -0.5f, (x + 1) / 16.0f,	y / 16.0f,
		-0.5f, -0.5f, -0.5f, (x + 1) / 16.0f,	(y + 1) / 16.0f,
		-0.5f, -0.5f, -0.5f, (x + 1) / 16.0f,	(y + 1) / 16.0f,
		-0.5f, -0.5f,  0.5f, x / 16.0f,		(y + 1) / 16.0f,
		-0.5f,  0.5f,  0.5f, x / 16.0f,		y / 16.0f,

		 0.5f,  0.5f,  0.5f, x / 16.0f,		y / 16.0f,
		 0.5f,  0.5f, -0.5f, (x + 1) / 16.0f,	y / 16.0f,
		 0.5f, -0.5f, -0.5f, (x + 1) / 16.0f,	(y + 1) / 16.0f,
		 0.5f, -0.5f, -0.5f, (x + 1) / 16.0f,	(y + 1) / 16.0f,
		 0.5f, -0.5f,  0.5f, x / 16.0f,		(y + 1) / 16.0f,
		 0.5f,  0.5f,  0.5f, x / 16.0f,		y / 16.0f,

		-0.5f, -0.5f, -0.5f, x / 16.0f,		y / 16.0f,
		 0.5f, -0.5f, -0.5f, (x + 1) / 16.0f,	y / 16.0f,
		 0.5f, -0.5f,  0.5f, (x + 1) / 16.0f,	(y + 1) / 16.0f,
		 0.5f, -0.5f,  0.5f, (x + 1) / 16.0f,	(y + 1) / 16.0f,
		-0.5f, -0.5f,  0.5f, x / 16.0f,		(y + 1) / 16.0f,
		-0.5f, -0.5f, -0.5f, x / 16.0f,		y / 16.0f,

		-0.5f,  0.5f, -0.5f, x / 16.0f,		y / 16.0f,
		 0.5f,  0.5f, -0.5f, (x + 1) / 16.0f,	y / 16.0f,
		 0.5f,  0.5f,  0.5f, (x + 1) / 16.0f,	(y + 1) / 16.0f,
		 0.5f,  0.5f,  0.5f, (x + 1) / 16.0f,	(y + 1) / 16.0f,
		-0.5f,  0.5f,  0.5f, x / 16.0f,		(y + 1) / 16.0f,
		-0.5f,  0.5f, -0.5f, x / 16.0f,		y / 16.0f
	};

	glm::vec4 instancingData[27000];
	int index = 0;
	float offset = 0.1f;
	for (int y = -30; y < 30; y += 2)
	{
		for (int x = -30; x < 30; x += 2)
		{
			for (int z = -30; z < 30; z += 2)
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

	glGenBuffers(1, &InstanceBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, InstanceBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * 27000, &instancingData[0], GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// vertex position attribute x, y, z
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// texture coords attribute u, v
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	// world space position x, y, z, (and 4th variable holding block's id) w
	// used for instanced rendering
	glBindBuffer(GL_ARRAY_BUFFER, InstanceBuffer);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glVertexAttribDivisor(2, 1); // Only go to next attribute on next instance draw

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

}

unsigned int BlockType::GetVAO()
{
	return VAO;
}

BlockType *BlockType::GetBlockType(unsigned int id)
{
	return &blockTypeList[id];
}

void BlockType::InitBlockTypes(const char *texturePath)
{

	glGenTextures(1, &TextureID);
	glBindTexture(GL_TEXTURE_2D, TextureID);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// stbi_set_flip_vertically_on_load(true);

	// load and generate the texture
	int width, height, nrChannels;
	unsigned char *data = stbi_load("terrain.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	
	blockTypeList[0].Init(0);
	
}