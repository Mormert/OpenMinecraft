#pragma once

#include <glm/glm.hpp>
#include "Shader.h"
#include "Camera.h"

class Renderer
{
public:
	void Init(int width, int height, float fovDegree);

	// Render with camera's view matrix
	void Render(const Camera& camera);

	void SetPerspective(float FovDegree, float ratio, float nearClip, float farClip);
	void SetAspectRatio(int w, int h);

	~Renderer();

private:
	glm::mat4 projection;

	Shader* blockShader;

	float projRatio;
	float projNearClip;
	float projFarClip;
	float projFovDegree;
};

