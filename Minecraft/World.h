#pragma once


#include "BlockRenderer.h"
#include "WorldGenerator.h"
#include "Chunk.h"
#include "Player.h"

#include "PairHash.h"

#include "3rdparty/Moodycamel/readerwriterqueue.h"

#include <unordered_map>
#include <tuple>

class World {
public:
    World(int seed, int initialChunksXY, BlockRenderer &_blockRenderer);

    ~World();

    static inline World *g_world;

    void BufferChunksToBlockRenderer();

    int GetBlockAtWorldPosition(int x, int y, int z);    // 0 is air, -1 is not found

    // Sets a block at a world position if the chunk for that position exists
    // Returns the chunk that was affected, such that the chunk's GFX buffer can be re-generated.
    // Update GFX buffer has huge performance hit if used many times in a tight loop. Appropriate uses
    // are when only 1 block is affected.
    Chunk *SetBlockAtWorldPosition(int x, int y, int z, uint8_t block_id, bool updateGfxBuffer = true,
                                   bool broadcastNetwork = false);

    void SetBlockAtWorldPositionNetworked(int x, int y, int z, uint8_t block_id);

    int localBlockX, localBlockZ, chunkX, chunkZ;

    void UpdatePlayerData(const Player &playerData);

    void RemovePlayer(const std::string &playerID);

    const std::unordered_map<std::string, Player> &GetPlayers();

    void Update();

private:
    std::unordered_map<std::pair<int, int>, Chunk *, pair_hash> worldChunks;
    WorldGenerator worldGenerator;

    // Converts from world coordinates to local chunk coordinates, also return chunk coordinates in chunk space.
    std::tuple<glm::ivec3, std::pair<int, int>> GetLocalChunkCoordinates(int x, int y, int z);

    BlockRenderer &blockRenderer;

    std::unordered_map<std::string, Player> players;

    struct BlockUpdate {
        int x, y, z, block_id;
    };

    // Can only be used in a consumer-producer context, we use the queue
    // to send the main thread (game & render is main) updates on blocks
    // in the world, received from the server.
    moodycamel::ReaderWriterQueue<BlockUpdate> blockUpdateQueue{128};
};