#include "World.h"

#include "Block.h"

#include <cmath>

#include <tuple>

Block World::blocks[10][10][10]{};

void World::GenerateWorld(int seed)
{

}

std::vector<blocktuple> World::GetProximityBlocks(int x, int y, int z)
{
	std::vector<blocktuple> blocktupleVector;

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			for (int k = 0; k < 10; k++)
			{
				if (glm::distance(glm::vec3{i,j,k}, glm::vec3{x,y,z}) < 25.0f)
				{
					blocktupleVector.push_back(std::make_tuple(i, j, k, &blocks[i][j][k]));
				}
			}
		}
	}

	return blocktupleVector;
}