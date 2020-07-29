#include "GameManager.h"

#include "BlockType.h"

void GameManager::GameInit()
{
	BlockType::InitBlockTypes("");
	World::GenerateWorld(0);
}