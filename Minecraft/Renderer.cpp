#include "Renderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "World.h"
#include "Shader.h"

#include <iostream>
#include <vector>
#include <tuple>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#else
#include <glad/glad.h>
#endif
#include <GLFW/glfw3.h>

Renderer::Renderer(int scr_width, int scr_height, const Camera &camera)
		: mainCamera{ camera }, screenW{scr_width}, screenH{scr_height}
{
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_MULTISAMPLE); // Not supported when going ES 3.0

	blockShader = std::make_unique<Shader>("data/block.vert", "data/block.frag");
	skybox = std::make_unique<Skybox>("data/skybox.vert", "data/skybox.frag");
	blockRenderer = std::make_unique<BlockRenderer>(camera);

    playerRenderer = std::make_unique<PlayerRenderer>();

	projFarClip = 375.0f;
	projNearClip = 0.1f;
	projFovDegree = 70.0f;
	projRatio = static_cast<float>(scr_width) / static_cast<float>(scr_height);

	SetPerspective(projFovDegree, projRatio, projNearClip, projFarClip);

    // TODO: Encapsulate block shader into BlockRenderer.
	blockShader->Use();
	blockShader->SetMat4("model", glm::mat4{ 1.0f });

    renderer = this;

}

BlockRenderer &Renderer::GetBlockRenderer()
{
	return *blockRenderer;
}

void Renderer::SetPerspective(float FovDegree, float ratio, float nearClip, float farClip)
{
	projection = glm::mat4{ 1.0f };
	projection = glm::perspective(glm::radians(FovDegree), ratio, nearClip, farClip);
    blockRenderer->SetProjectionMatrix(projection);
}

void Renderer::SetAspectRatio(int w, int h)
{
	screenW = w;
	screenH = h;

	projRatio = static_cast<float>(w) / static_cast<float>(h);
	SetPerspective(projFovDegree, projRatio, projNearClip, projFarClip);
}

void Renderer::Render()
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Environment setting
    float brightnessValue = brightness;
    float humidityValue = humidity;
    skybox->SetBrightness(brightnessValue);
    skybox->SetHumidity(humidityValue);

	skybox->Render(mainCamera.Front, screenW, screenH);

	blockShader->Use();
	blockShader->SetMat4("view", mainCamera.GetViewMatrix());
    blockShader->SetMat4("projection", projection);
    blockShader->SetFloat("humidity", humidityValue * 0.05f);
    blockShader->SetFloat("brightness", brightnessValue);

    blockRenderer->RenderAllBufferedChunks();

    std::vector<Player> players;
    for(auto&& p : World::g_world->GetPlayers())
    {
        players.push_back(p.second);
    }

    playerRenderer->RenderPlayers(players, projection);
	
}

void Renderer::SetHumidity(float h) {
    humidity = glm::clamp(h, 0.f, 1.f);
}

void Renderer::SetBrightness(float dt) {
    brightness = glm::clamp(dt, 0.f, 1.f);
}
