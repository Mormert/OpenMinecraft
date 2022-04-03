
// Shared code between JS and Native for the Networking class

#include "Networking.h"

#include "World.h"
#include "Renderer.h"

#include <memory>
#include <iostream>
#include <sstream>

void Networking::EmitPlayerPosition(glm::vec3 position, float rotation, float headRotation) {
    std::stringstream s;

    // Note that the server also adds the client's ID as the first data parameter
    s << position.x << '\n' << position.y << '\n' << position.z << '\n' << rotation << '\n' << headRotation << '\n';
    EmitEvent("position", s.str());
}

void Networking::EmitUpdateBlock(int x, int y, int z, int block_id) {
    std::stringstream s;
    s << '\n' << x << '\n' << y << '\n' << z << '\n' << block_id << '\n';
    EmitEvent("block_update", s.str());
}

void Networking::OnPositionEvent(const std::string &data) {
    std::istringstream ss{data};
    Player player;

    ss >> player.id;
    ss >> player.location.x;
    ss >> player.location.y;
    ss >> player.location.z;
    ss >> player.rotation;
    ss >> player.headRotation;

    World::g_world->UpdatePlayerData(player);
}

void Networking::OnBlockEvent(const std::string &data) {
    std::istringstream ss{data};
    int x, y, z, block_id;
    ss >> x >> y >> z >> block_id;

    World::g_world->SetBlockAtWorldPositionNetworked(x, y, z, block_id);
}

void Networking::OnPlayerDisconnectEvent(const std::string &data) {
    World::g_world->RemovePlayer(data);
}

void Networking::OnEnvironmentSettingUpdateEvent(const std::string &data) {
    std::istringstream ss{data};
    float humidity, brightness;
    ss >> humidity >> brightness;

    auto renderer = Renderer::renderer;
    renderer->SetHumidity(humidity);
    renderer->SetBrightness(brightness);
}