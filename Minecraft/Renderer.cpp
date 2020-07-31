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

void Renderer::Init(int width, int height, float fovDegree)
{

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);

	blockShader = new Shader("block.vert", "block.frag");
	blockRenderer = new BlockRenderer();

	projFarClip = 100.0f;
	projNearClip = 0.1f;
	projFovDegree = fovDegree;
	projRatio = static_cast<float>(width) / static_cast<float>(height);
	SetPerspective(projFovDegree, projRatio, projNearClip, projFarClip);

	blockShader->Use();
	blockShader->SetMat4("model", glm::mat4{ 1.0f });
	blockShader->SetMat4("projection", projection);
}

void Renderer::SetPerspective(float FovDegree, float ratio, float nearClip, float farClip)
{
	projection = glm::mat4{ 1.0f };
	projection = glm::perspective(glm::radians(FovDegree), ratio, nearClip, farClip);
	blockShader->SetMat4("projection", projection);
}

void Renderer::SetAspectRatio(int w, int h)
{
	projRatio = static_cast<float>(w) / static_cast<float>(h);
	SetPerspective(projFovDegree, projRatio, projNearClip, projFarClip);
}

double lastProximityBlocksUpdate = 0;
void Renderer::Render(const Camera &camera)
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	blockShader->Use();
	blockShader->SetMat4("view", camera.GetViewMatrix());

	double currentTime = glfwGetTime();
	if ((currentTime - lastProximityBlocksUpdate) > 5.0)
	{
		blockRenderer->BufferBlocks(nullptr, 0);
		lastProximityBlocksUpdate = currentTime;
	}


	blockRenderer->RenderBlocks();
	
}

Renderer::~Renderer()
{
	delete blockRenderer;
	delete blockShader;
}