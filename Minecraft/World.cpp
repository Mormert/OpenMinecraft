#include "World.h"

#include "Block.h"

#include <cmath>

#include <tuple>

#include "BlockType.h"

#include <iostream>

Block World::blocks[100][100][100]{};

void World::GenerateWorld(int seed)
{

}

std::vector<blocktuple> World::GetProximityBlocks(int x, int y, int z)
{

	//std::cout << x << ", " << y << ", " << z << "\n";

	std::vector<blocktuple> blocktupleVector;

	const int distX{ 25 };
	const int distY{ 5 };
	const int distZ{ 25 };

	int count = 0;

	glm::vec4 instancingData[5000];


	for (int i = x- distX; i < x+ distX; i++)
	{
		for (int j = y- distY; j < y+ distY; j++)
		{
			for (int k = z- distZ; k < z+ distZ; k++)
			{
				if (i < 0 | i > 99 | j < 0 | j > 99 | k < 0 | k > 99)
				{}
				else
				{
					instancingData[count++] = glm::vec4{ i,j,k, 0 };
				}
					//std::cout << i << std::endl;
					//blocktupleVector.push_back(std::make_tuple(i, j, k, &blocks[i][j][k]));
				
			}
		}
	}

	

	glBindBuffer(GL_ARRAY_BUFFER, BlockType::InstanceBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * count, &instancingData[0], GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	BlockType::BlocksToRender = count;


	/*glm::vec4 instancingData[27000];
	int index = 0;
	float offset = 0.1f;
	for (int y = -30; y < 30; y += 2)
	{
		for (int x = -30; x < 30; x += 2)
		{
			for (int z = -30; z < 30; z += 2)
			{
				glm::vec4 instancingDat;
				instancingDat.x = (float)x + offset + ((rand() % 100) + 1)/200.0f;
				instancingDat.y = (float)y + offset + ((rand() % 100) + 1) / 200.0f;
				instancingDat.z = (float)z + offset + ((rand() % 100) + 1) / 200.0f;
				instancingDat.w = (rand() % 100) + 1;
				instancingData[index++] = instancingDat;
			}
		}
	}

	glBindBuffer(GL_ARRAY_BUFFER, BlockType::InstanceBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * 27000, &instancingData[0], GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);*/


	return blocktupleVector;
}