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


#include "Chunk.h"

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

	// Testing chunk system:

	Chunk chunk{ 1,0 };
	for (int y = 0; y < 10; y += 1)
	{
		for (int x = 0; x < 10; x += 1)
		{
			for (int z = 0; z < 10; z += 1)
			{
				if (y == 9)
				{
					chunk.SetBlockLocal(x, y, z, 2);
				}
				else {
					chunk.SetBlockLocal(x, y, z, 1);
				}
				
			}
		}
	}
	chunk.GenerateBuffer();
	blockRenderer->BufferChunk(0, 0, chunk.GetBlockDataVector());

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

void Renderer::Render(const Camera &camera)
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	blockShader->Use();
	blockShader->SetMat4("view", camera.GetViewMatrix());

	blockRenderer->RenderAllBufferedChunks();
	
}