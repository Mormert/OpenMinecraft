#pragma once

#include <glm/glm.hpp>

class BlockRenderer
{
public:
	BlockRenderer();
	~BlockRenderer();

	void RenderBlocks();
	
	void BufferBlocks(glm::vec4 *vec, unsigned int amount);

private:

	unsigned int instanceBuffer, VAO, VBO, texture;
	unsigned int blocksCountRender;

};