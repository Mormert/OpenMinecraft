#ifndef OPENMINECRAFT_PLAYER_H
#define OPENMINECRAFT_PLAYER_H

#include <glm/glm.hpp>

struct Player
{
    unsigned int id;
    glm::vec3 location;
    float rotation, headRotation; // angle in radians
};

#endif //OPENMINECRAFT_PLAYER_H
