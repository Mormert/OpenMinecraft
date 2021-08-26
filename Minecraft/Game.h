#pragma once

#include "World.h"
#include "BlockRenderer.h"


class Game
{
public:
	Game(BlockRenderer &br);

	void Update(float deltaTime);

private:
	World world;
};