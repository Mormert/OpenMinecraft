#include "Game.h"

#include <set>
#include <iostream>
#include <future>

#include "Camera.h"

Game::Game(BlockRenderer &_blockRenderer) :
        world{rand(), 12, _blockRenderer} {

    world.BufferChunksToBlockRenderer();

    networking.Connect("http://hexablo:314");

    std::set<Chunk *> chunksAffected;

    for (int i = 25; i < 30; i++) {
        for (int j = 25; j < 30; j++) {
            for (int k = 3; k < 20; k++) {
                auto c = world.SetBlockAtWorldPosition(i, k, j, 3, false);
                chunksAffected.insert(c);
            }
        }
    }

    for (auto &&c: chunksAffected) {
        c->GenerateBuffer();
        _blockRenderer.BufferChunk(c->GetChunkX(), c->GetChunkZ(), c->GetBlockDataVector());
    }


}

void Game::Update(float deltaTime) {
    static float netTickTimer = 0.f;
    netTickTimer += deltaTime;

    if (netTickTimer > 0.10f) {
        netTickTimer = 0.f;

        auto &&cam = Camera::GetMainCamera();

        glm::vec3 front = cam->Front;
        front.y = 0.f;
        front = glm::normalize(front);
        if (front.x == 0.f) { front.x = 0.000001f; }
        float bodyAngle = -atan2f(front.z, front.x) - glm::pi<float>();

        float headAngle = (std::acos(cam->Front.y) - glm::pi<float>() * 0.5f);

        networking.EmitPlayerPosition(cam->Position, bodyAngle, headAngle);
    }

    world.Update();
}