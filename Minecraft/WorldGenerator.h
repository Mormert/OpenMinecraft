#pragma once


#include "FastNoise/FastNoise.h"
#include "Chunk.h"

class WorldGenerator
{
public:
	WorldGenerator(int seed);

	void GenerateChunk(Chunk *chunk);

private:
	FastNoise noise;
};