#pragma once

#include <glm/glm.hpp>
#include "Shader.h"
#include "Camera.h"

#include "BlockRenderer.h"

class Renderer
{
public:
	Renderer(int scr_width, int scr_height, float camFovDegree);
	~Renderer();

	// Render with camera's view matrix
	void Render(const Camera& camera);

	void SetPerspective(float FovDegree, float ratio, float nearClip, float farClip);
	void SetAspectRatio(int w, int h);

private:
	glm::mat4 projection;

	Shader* blockShader;
	BlockRenderer* blockRenderer;

	float projRatio;
	float projNearClip;
	float projFarClip;
	float projFovDegree;
};

