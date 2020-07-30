#pragma once

#include "Block.h"

#include <vector>
#include <tuple>

// x, y, z, block*
using blocktuple = std::tuple<int, int, int, Block*>;

class World
{
public:
	static void GenerateWorld(int seed);

	static std::vector<blocktuple> GetProximityBlocks(int x, int y, int z);
	

private:
	static Block blocks[100][100][100];
};

