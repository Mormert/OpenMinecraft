#include "World.h"

#include "Block.h"

#include <cmath>

#include <tuple>

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
					//std::cout << i << std::endl;
					blocktupleVector.push_back(std::make_tuple(i, j, k, &blocks[i][j][k]));
				}
			}
		}
	}
	return blocktupleVector;
}