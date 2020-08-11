#pragma once

#include <glm/glm.hpp>
#include "Shader.h"
#include "Camera.h"

#include "BlockRenderer.h"
#include "Skybox.h"

class Renderer
{
public:
	Renderer(int scr_width, int scr_height, const Camera &camera);
	~Renderer();

	void Render();

	void SetPerspective(float FovDegree, float ratio, float nearClip, float farClip);
	void SetAspectRatio(int w, int h);

private:
	glm::mat4 projection;

	const Camera& mainCamera;

	Shader* blockShader;
	Skybox* skybox;
	BlockRenderer* blockRenderer;

	float projRatio;
	float projNearClip;
	float projFarClip;
	float projFovDegree;
};

