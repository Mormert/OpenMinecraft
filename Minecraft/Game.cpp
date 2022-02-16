#include "Game.h"

#include <set>
#include <iostream>
#include <future>

Game::Game(BlockRenderer &_blockRenderer) :
	world{ rand(), 12, _blockRenderer}
{

	world.BufferChunksToBlockRenderer();


    std::set<Chunk*> chunksAffected;

    for(int i = 25; i < 30 ; i++)
    {
        for(int j = 25; j < 30; j++)
        {
            for(int k = 3; k < 20; k++)
            {
                auto c = world.SetBlockAtWorldPosition(i, k, j, 3, false);
                chunksAffected.insert(c);
            }
        }
    }

    for(auto&& c : chunksAffected)
    {
        c->GenerateBuffer();
        _blockRenderer.BufferChunk(c->GetChunkX(), c->GetChunkZ(), c->GetBlockDataVector());
    }

}

void Game::Update(float deltaTime)
{
}