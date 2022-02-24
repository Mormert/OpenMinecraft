#include "Renderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

	blockShader->Use();
	blockShader->SetMat4("model", glm::mat4{ 1.0f });
	blockShader->SetMat4("projection", projection);

}

BlockRenderer &Renderer::GetBlockRenderer()
{
	return *blockRenderer;
}

void Renderer::SetPerspective(float FovDegree, float ratio, float nearClip, float farClip)
{
	projection = glm::mat4{ 1.0f };
	projection = glm::perspective(glm::radians(FovDegree), ratio, nearClip, farClip);
	blockShader->SetMat4("projection", projection);
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
	
	skybox->Render(mainCamera.Front, screenW, screenH);

	blockShader->Use();
	blockShader->SetMat4("view", mainCamera.GetViewMatrix());
    blockRenderer->RenderAllBufferedChunks();

    std::vector<Player> players;
    Player p;
    p.location = glm::vec3{10.f,11.5f,3.f};
    p.rotation = glfwGetTime() * 40.f;
    p.headRotation = 5.f;
    players.push_back(p);


    p.location  = glm::vec3{10.f,11.5f,19.f};
    p.headRotation = -17.f;
    players.push_back(p);

    playerRenderer->RenderPlayers(players, projection);
	
}