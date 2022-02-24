#pragma once

#include <glm/glm.hpp>
#include "Shader.h"
#include "Camera.h"

#include "BlockRenderer.h"
#include "Skybox.h"
#include "PlayerRenderer.h"

class Renderer
{
public:
	Renderer(int scr_width, int scr_height, const Camera &camera);

	void Render();

	void SetPerspective(float FovDegree, float ratio, float nearClip, float farClip);
	void SetAspectRatio(int w, int h);

	BlockRenderer& GetBlockRenderer();

private:
	glm::mat4 projection;

	const Camera& mainCamera;

    std::unique_ptr<Shader> blockShader;
    std::unique_ptr<Skybox> skybox;
    std::unique_ptr<BlockRenderer> blockRenderer;

    std::unique_ptr<PlayerRenderer> playerRenderer;

	float projRatio;
	float projNearClip;
	float projFarClip;
	float projFovDegree;

	int screenW, screenH;
};

