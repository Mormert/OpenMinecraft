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

Renderer::Renderer(int scr_width, int scr_height, float camFovDegree)
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);

	blockShader = new Shader("block.vert", "block.frag");
	blockRenderer = new BlockRenderer();

	projFarClip = 100.0f;
	projNearClip = 0.1f;
	projFovDegree = camFovDegree;
	projRatio = static_cast<float>(scr_width) / static_cast<float>(scr_height);

	SetPerspective(projFovDegree, projRatio, projNearClip, projFarClip);

	blockShader->Use();
	blockShader->SetMat4("model", glm::mat4{ 1.0f });
	blockShader->SetMat4("projection", projection);


	std::vector<BufferBlockData> instanceData;
	//BufferBlockData *instancingData = new BufferBlockData[1000];

	int index = 0;
	for (int y = -5; y < 5; y += 1)
	{
		for (int x = -5; x < 5; x += 1)
		{
			for (int z = -5; z < 5; z += 1)
			{
				glm::vec3 distance{ x,y,z };
				if (glm::length(distance) > 3.8f) {
					BufferBlockData instancingDat;
					instancingDat.data[0] = (float)x;
					instancingDat.data[1] = (float)y;
					instancingDat.data[2] = (float)z;
					instancingDat.data[3] = 0; // 0 rotation
					instancingDat.data[4] = float((rand() % 255)) + 1.1f;
					instancingDat.data[5] = float((rand() % 255)) + 1.1f;
					instancingDat.data[6] = float((rand() % 255)) + 1.1f;
					instancingDat.data[7] = float((rand() % 255)) + 1.1f;

					//instancingData[index++] = instancingDat;
					instanceData.push_back(instancingDat);
				}
				
			}
		}
	}

	//blockRenderer->BufferChunk(0, 0, instancingData, 1000);
	blockRenderer->BufferChunk(0, 0, &instanceData[0], instanceData.size());

	//delete[] instancingData;

}

Renderer::~Renderer()
{
	delete blockRenderer;
	delete blockShader;
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

double lastProximityBlocksUpdate = 0.0;
void Renderer::Render(const Camera &camera)
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	blockShader->Use();
	blockShader->SetMat4("view", camera.GetViewMatrix());

	double currentTime = glfwGetTime();
	if ((currentTime - lastProximityBlocksUpdate) > 2.0)
	{
		//blockRenderer->BufferBlocks(nullptr, 0);
		lastProximityBlocksUpdate = currentTime;
	}


	blockRenderer->RenderAllBufferedChunks();
	
}