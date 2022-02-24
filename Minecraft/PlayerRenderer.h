#ifndef OPENMINECRAFT_PLAYERRENDERER_H
#define OPENMINECRAFT_PLAYERRENDERER_H

#include "Player.h"
#include "Shader.h"

#include <vector>
#include <memory>

class PlayerRenderer {
public:
    PlayerRenderer();

    void RenderPlayers(const std::vector<Player> &players, glm::mat4 proj);

private:
    std::unique_ptr<Shader> shader;
    unsigned int VAO = 0, VBO = 0;

};


#endif //OPENMINECRAFT_PLAYERRENDERER_H
