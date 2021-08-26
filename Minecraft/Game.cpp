#include "Game.h"

#include <iostream>

Game::Game(BlockRenderer &_blockRenderer) :
	world{ 1234, 8, _blockRenderer}
{
	
	world.BufferChunksToBlockRenderer();

	for (int i = 0; i < 23; i++)
	{
		world.SetBlockAtWorldPosition(60, i, 16, 0);
		world.SetBlockAtWorldPosition(30, i, 16, 0);
		world.SetBlockAtWorldPosition(0, i, 0, 0);
	}



	//std::cout << world.GetBlockAtWorldPosition(13371, 7, 5) << std::endl;
}

void Game::Update(float deltaTime)
{
}