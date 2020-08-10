#include "BlockLoader.h"

#include <iostream>
#include <fstream>

std::array<BlockFaceData, 256> BlockLoader::blockFaceDataArray{};

void BlockLoader::LoadBlocksFromFile(const std::string &file)
{
	std::ifstream infile(file);

	unsigned int block_id;
	float face1, face2, face3, face4;

	while (infile >> block_id >> face1 >> face2 >> face3 >> face4)
	{
		// Note that we add 0.1f as a bias so that the shader
		// can floor the float to an int, without risk of flooring
		// to an integer below the one we specify here
		blockFaceDataArray.at(block_id).at(0) = face1 + 0.1f;
		blockFaceDataArray.at(block_id).at(1) = face2 + 0.1f;
		blockFaceDataArray.at(block_id).at(2) = face3 + 0.1f;
		blockFaceDataArray.at(block_id).at(3) = face4 + 0.1f;
	}
}
BlockFaceData BlockLoader::GetBlockFaceData(unsigned int block_id)
{
	return blockFaceDataArray.at(block_id);
}