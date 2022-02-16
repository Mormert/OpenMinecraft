#include "Game.h"

#include <set>
#include <iostream>
#include <future>

Game::Game(BlockRenderer &_blockRenderer) :
	world{ 1234, 32, _blockRenderer}
{

	world.BufferChunksToBlockRenderer();


    std::set<Chunk*> chunksAffected;

	for (int i = 0; i < 23; i++)
	{
		auto c = world.SetBlockAtWorldPosition(0, i, 0, 0);
        chunksAffected.insert(c);
	}


    for(int i = 25; i < 30 ; i++)
    {
        for(int j = -20; j < 20; j++)
        {
            for(int k = 0; k < 24; k++)
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




    //world.SetBlockAtWorldPosition(0, 0, 0, 0, true);


	//std::cout << world.GetBlockAtWorldPosition(13371, 7, 5) << std::endl;
}

void Game::Update(float deltaTime)
{
}