#include "Renderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

#include <iostream>
#include <vector>
#include <tuple>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Renderer::Renderer(int scr_width, int scr_height, const Camera &camera)
		: mainCamera{ camera }, screenW{scr_width}, screenH{scr_height}
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);

	blockShader = new Shader("block.vert", "block.frag");
	skybox = new Skybox("skybox.vert", "skybox.frag");
	blockRenderer = new BlockRenderer(camera);

	projFarClip = 325.0f;
	projNearClip = 0.1f;
	projFovDegree = 70.0f;
	projRatio = static_cast<float>(scr_width) / static_cast<float>(scr_height);

	SetPerspective(projFovDegree, projRatio, projNearClip, projFarClip);

	blockShader->Use();
	blockShader->SetMat4("model", glm::mat4{ 1.0f });
	blockShader->SetMat4("projection", projection);

}

Renderer::~Renderer()
{
	delete blockRenderer;
	delete blockShader;
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
	
}