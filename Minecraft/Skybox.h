#pragma once

#include "Shader.h"
#include <string>
#include <glm/glm.hpp>

class Skybox
{
public:
	Skybox(const char* vertexShader, const char* fragmentShader);
	~Skybox();

	void Render(const glm::vec3 &cameraDirection, int screenWidth, int screenHeight);

private:
	Shader *shader;
	unsigned int VAO, VBO;
};

