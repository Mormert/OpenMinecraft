#ifndef OPENMINECRAFT_PLAYER_H
#define OPENMINECRAFT_PLAYER_H

#include <glm/glm.hpp>

#include <string>

struct Player
{
    std::string id;
    glm::vec3 location;
    float rotation, headRotation = 0.f; // in radians
};

#endif //OPENMINECRAFT_PLAYER_H
