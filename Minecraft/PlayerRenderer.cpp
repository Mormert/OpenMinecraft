//
// Created by jlind on 2022-02-23.
//

#include "PlayerRenderer.h"

#include "Camera.h"
#include "FrustumCull.h"

PlayerRenderer::PlayerRenderer() : shader{
        std::make_unique<Shader>("data/PlayerRenderer.vert", "data/PlayerRenderer.frag")} {

    // Regular cube
    float vertices[] = {
            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, 0.5f, -0.5f,
            0.5f, 0.5f, -0.5f,
            -0.5f, 0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, 0.5f,
            0.5f, -0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, 0.5f,
            -0.5f, -0.5f, 0.5f,
            -0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, 0.5f,
            -0.5f, 0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,
            0.5f, 0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,
            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, 0.5f,
            0.5f, -0.5f, 0.5f,
            -0.5f, -0.5f, 0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, 0.5f, -0.5f,
            0.5f, 0.5f, -0.5f,
            0.5f, 0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, -0.5f
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
}

void PlayerRenderer::RenderPlayers(const std::vector<Player> &players, glm::mat4 proj) {

    glm::mat4 view = Camera::GetMainCamera()->GetViewMatrix();

    shader->Use();

    shader->SetMat4("projection", proj);
    shader->SetMat4("view", view);

    constexpr glm::vec3 playerScaleConstant = 0.6f * glm::one<glm::vec3>();

    const auto m = proj * view;
    Frustum frustum{m};

    glBindVertexArray(VAO);
    for (auto &&player: players) {

        // TODO: Fix frustum culling
        // if(!frustum.IsBoxVisible(player.location + glm::vec3(2.5f,2.5f,2.5f), player.location + glm::vec3(-2.5f,-2.5f,-2.5f)))
        // {
        //     continue;
        // }

        // Body
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, player.location);
        model = glm::scale(model, playerScaleConstant);
        model = glm::rotate(model, glm::radians(player.rotation), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3{.5f, 2.5f, 1.f});
        shader->SetMat4("model", model);
        shader->SetVec3("color", glm::vec3(0.2, 0.2, 0.8));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Head
        model = glm::mat4(1.0f);
        model = glm::translate(model, player.location);
        model = glm::scale(model, playerScaleConstant);
        model = glm::translate(model, glm::vec3(0.f, 1.45f, 0.f));
        model = glm::rotate(model, glm::radians(player.rotation), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(player.headRotation), glm::vec3(0.f, 0.f, 1.f));
        model = glm::translate(model, glm::vec3(0.f, .25f, 0.f));
        model = glm::scale(model, glm::vec3{.8f, .8f, .8f});
        shader->SetMat4("model", model);
        shader->SetVec3("color", glm::vec3(0.96, 0.75, 0.47));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Arms
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, player.location);
            model = glm::scale(model, playerScaleConstant);
            model = glm::rotate(model, glm::radians(player.rotation), glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::translate(model, glm::vec3(0.f, 0.65f, .725f));
            model = glm::scale(model, glm::vec3{.4f, 1.2f, .4f});
            shader->SetMat4("model", model);
            shader->SetVec3("color", glm::vec3(0.96, 0.75, 0.47));
            glDrawArrays(GL_TRIANGLES, 0, 36);

            model = glm::mat4(1.0f);
            model = glm::translate(model, player.location);
            model = glm::scale(model, playerScaleConstant);
            model = glm::rotate(model, glm::radians(player.rotation), glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::translate(model, glm::vec3(0.f, 0.65f, -0.725f));
            model = glm::scale(model, glm::vec3{.4f, 1.2f, .4f});
            shader->SetMat4("model", model);
            shader->SetVec3("color", glm::vec3(0.96, 0.75, 0.47));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

    }
}