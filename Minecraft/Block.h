#pragma once

#include "Shader.h"

class Block
{
public:
	unsigned int block_id;
	Block(unsigned int id);
	Block();

	void Draw(Shader *shader, int x, int y, int z);
};

