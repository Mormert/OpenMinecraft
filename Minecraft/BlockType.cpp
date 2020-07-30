#include "BlockType.h"

#include <glad/glad.h>

#include <iostream>

#include "stb_image.h"

BlockType BlockType::blockTypeList[256] {};
unsigned int BlockType::TextureID{ 0 };

void BlockType::Init(unsigned int id)
{
	int x = id % 16;
	int y = id / 16;

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

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

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

	for (int i = 0; i < 256; i++)
	{
		blockTypeList[i].Init(i);
	}
}