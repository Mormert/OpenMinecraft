#include "Renderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

#include "Block.h"
#include "BlockType.h"

#include "World.h"

#include <iostream>
#include <vector>
#include <tuple>

Block blocks[10][10][10];

void Renderer::Init(int width, int height, float fovDegree)
{

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);

	blockShader = new Shader("block.vert", "block.frag");

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

std::vector<blocktuple> proximityBlocks;
double lastProximityBlocksUpdate = 0;
void Renderer::Render(const Camera &camera)
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	blockShader->Use();
	blockShader->SetMat4("view", camera.GetViewMatrix());

	double currentTime = glfwGetTime();
	if ((currentTime - lastProximityBlocksUpdate) > 1.0)
	{
		proximityBlocks = World::GetProximityBlocks(camera.Position.x, camera.Position.y, camera.Position.z);
		lastProximityBlocksUpdate = currentTime;
	}
	
	// Render blocks in the proximity to the camera
	for (const auto& block : proximityBlocks)
	{
		std::get<3>(block)->Draw(blockShader, std::get<0>(block), std::get<1>(block), std::get<2>(block));
	}
	
}

Renderer::~Renderer()
{

}