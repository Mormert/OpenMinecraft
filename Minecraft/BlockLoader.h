#pragma once

#include <string>
#include <array>
#include <cstdint>

using BlockFaceData = std::array<float, 4>;

class BlockLoader
{
public:
	static void LoadBlocksFromFile(const std::string &file);
	static BlockFaceData GetBlockFaceData(unsigned int block_id);
private:
	static std::array<BlockFaceData, 256> blockFaceDataArray;
};