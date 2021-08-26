#pragma once

#include <array>
#include <vector>

// Array contains:
// x, y, z, rotation, face0_id, face1_id, face2_id, face3_id (faces should range 0 - 255), flower
using BlockData = std::array<float, 8>;			// Defines 1 block
using BlockDataVector = std::vector<BlockData>;	// Defines a bunch of blocks